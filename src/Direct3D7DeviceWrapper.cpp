#include "Direct3D7DeviceWrapper.h"
#ifdef LOG_ALLOWED
#include "Logger.h"
#endif

namespace dx7fix
{

Direct3D7DeviceWrapper::Direct3D7DeviceWrapper(LPDIRECT3DDEVICE7 originalDevice)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _originalDevice = originalDevice;
  _refCount++;
}

Direct3D7DeviceWrapper::~Direct3D7DeviceWrapper()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _originalDevice->Release();
  _originalDevice = nullptr;

  if (_numLinearIndices > 0)
  {
    delete[] _linearIndices;
    _linearIndices = nullptr;
  }

  if (_numTriangleFanIndices > 0)
  {
    delete[] _triangleFanIndices;
    _triangleFanIndices = nullptr;
  }

  if (_numLineListIndices > 0)
  {
    delete[] _lineListIndices;
    _lineListIndices = nullptr;
  }
}

/*** IUnknown ***/
HRESULT Direct3D7DeviceWrapper::QueryInterface(THIS_ REFIID riid, LPVOID FAR *ppvObj)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  HRESULT queryResult;

  if (riid == IID_IUnknown)
  {
    *ppvObj = dynamic_cast<LPUNKNOWN>(this);
    AddRef();

    queryResult = S_OK;
  }
  else
  {
    queryResult = _originalDevice->QueryInterface(riid, ppvObj);
  }

  return queryResult;
}

ULONG Direct3D7DeviceWrapper::AddRef(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _refCount++;
  return _refCount;
}

ULONG Direct3D7DeviceWrapper::Release(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _refCount--;
  if (_refCount == 0)
  {
    delete this;
    return 0;
  }

  return _refCount;
}

/*** IDirect3DDevice7 (reimplemented) ***/
//Replace DrawPrimitive call with DrawIndexedPrimitive call for some kinds of primitives.
HRESULT Direct3D7DeviceWrapper::DrawPrimitive(THIS_ D3DPRIMITIVETYPE dptPrimitiveType, 
                                              DWORD dwVertexTypeDesc, LPVOID lpvVertices,
                                              DWORD dwVertexCount, DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  switch (dptPrimitiveType)
  {
    case D3DPT_LINELIST:
    {
      DWORD numIndices = dwVertexCount * 2 - 2;

      //create larger vertex indices array (if necessary)
      if (numIndices > _numLineListIndices)
      {
        if (_numLineListIndices > 0)
          delete[] _lineListIndices;

        _lineListIndices = new WORD[numIndices];

        //Despite that the vertex count is DWORD, the directX wants vertex indices
        //as array of WORD. So it's assumed that dwVertexCount is small enough to
        //fit WORD type.
        WORD vertexCount = static_cast<WORD>(dwVertexCount);
        for (WORD i = 0; i < vertexCount - 1; i++)
        {
          
          _lineListIndices[i * 2] = i;
          _lineListIndices[i * 2 + 1] = i + 1;
        }

        _numLineListIndices = numIndices;
      }

      return _originalDevice->DrawIndexedPrimitive(dptPrimitiveType, dwVertexTypeDesc,
          lpvVertices, dwVertexCount, _lineListIndices, numIndices, dwFlags);
    }

    case D3DPT_LINESTRIP:
    case D3DPT_TRIANGLESTRIP:
    case D3DPT_TRIANGLELIST:
    {
      if (dwVertexCount > _numLinearIndices)
      {
        if (_numLinearIndices > 0)
          delete[] _linearIndices;

        _linearIndices = new WORD[dwVertexCount];

        //Despite that the vertex count is DWORD, the directX wants vertex indices
        //as array of WORD. So it's assumed that dwVertexCount is small enough to
        //fit WORD type.
        WORD vertexCount = static_cast<WORD>(dwVertexCount);
        for (WORD i = 0; i < vertexCount; i++)
        {
          _linearIndices[i] = i;
        }

        _numLinearIndices = dwVertexCount;
      }

      return _originalDevice->DrawIndexedPrimitive(dptPrimitiveType, dwVertexTypeDesc,
          lpvVertices, dwVertexCount, _linearIndices, dwVertexCount, dwFlags);
    }

    case D3DPT_TRIANGLEFAN:
    {
      //Despite that the vertex count is DWORD, the directX wants vertex indices
      //as array of WORD. So it's assumed that dwVertexCount is small enough to
      //fit WORD type.
      WORD numTriangles = static_cast<WORD>(dwVertexCount - 2);
      DWORD numIndices = numTriangles * 3;

      if (numIndices > _numTriangleFanIndices)
      {
        if (_numTriangleFanIndices > 0)
          delete[] _triangleFanIndices;

        _triangleFanIndices = new WORD[numIndices];

        for (WORD i = 0; i < numTriangles; i++)
        {
          _triangleFanIndices[i * 3] = 0;
          _triangleFanIndices[i * 3 + 1] = i + 1;
          _triangleFanIndices[i * 3 + 2] = i + 2;
        }

        _numTriangleFanIndices = numIndices;
      }

      return _originalDevice->DrawIndexedPrimitive(dptPrimitiveType, dwVertexTypeDesc,
          lpvVertices, dwVertexCount, _triangleFanIndices, numIndices, dwFlags);
    }

    default:
      return _originalDevice->DrawPrimitive(dptPrimitiveType, dwVertexTypeDesc,
          lpvVertices, dwVertexCount, dwFlags);
  }
}

//Replace DrawPrimitiveVB call with DrawIndexedPrimitiveVB call for some kinds of primitives.
HRESULT Direct3D7DeviceWrapper::DrawPrimitiveVB(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                                LPDIRECT3DVERTEXBUFFER7 lpd3dVertexBuffer,
                                                DWORD dwStartVertex, DWORD dwNumVertices,
                                                DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  if (d3dptPrimitiveType == D3DPT_TRIANGLELIST)
  {
    if (dwNumVertices > _numLinearIndices)
    {
      if (_numLinearIndices > 0)
        delete[] _linearIndices;

      _linearIndices = new WORD[dwNumVertices];

      //Despite that the vertex count is DWORD, the directX wants vertex indices
      //as array of WORD. So it's assumed that dwVertexCount is small enough to
      //fit WORD type.
      WORD numVertices = static_cast<WORD>(dwNumVertices);
      for (WORD i = 0; i < numVertices; i++)
      {
        _linearIndices[i] = i;
      }

      _numLinearIndices = dwNumVertices;
    }

    return _originalDevice->DrawIndexedPrimitiveVB(d3dptPrimitiveType, lpd3dVertexBuffer,
        dwStartVertex, dwNumVertices, _linearIndices, dwNumVertices, dwFlags);
  }
  else
  {
    return _originalDevice->DrawPrimitiveVB(d3dptPrimitiveType, lpd3dVertexBuffer,
        dwStartVertex, dwNumVertices, dwFlags);
  }
}

/*** IDirect3DDevice7 ***/
HRESULT Direct3D7DeviceWrapper::GetCaps(THIS_ LPD3DDEVICEDESC7 lpD3DDevDesc)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetCaps(lpD3DDevDesc);
}

HRESULT Direct3D7DeviceWrapper::EnumTextureFormats(THIS_ LPD3DENUMPIXELFORMATSCALLBACK lpd3dEnumPixelProc,
                                                   LPVOID lpArg)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->EnumTextureFormats(lpd3dEnumPixelProc, lpArg);
}

HRESULT Direct3D7DeviceWrapper::BeginScene(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->BeginScene();
}

HRESULT Direct3D7DeviceWrapper::EndScene(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->EndScene();
}

HRESULT Direct3D7DeviceWrapper::GetDirect3D(THIS_ LPDIRECT3D7* lplpD3D)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetDirect3D(lplpD3D);
}

HRESULT Direct3D7DeviceWrapper::SetRenderTarget(THIS_ LPDIRECTDRAWSURFACE7 lpNewRenderTarget,
                                                DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetRenderTarget(lpNewRenderTarget, dwFlags);
}

HRESULT Direct3D7DeviceWrapper::GetRenderTarget(THIS_ LPDIRECTDRAWSURFACE7* lplpRenderTarget)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetRenderTarget(lplpRenderTarget);
}

HRESULT Direct3D7DeviceWrapper::Clear(THIS_ DWORD dwCount, LPD3DRECT lpRects, DWORD dwFlags,
                                      D3DCOLOR dwColor, D3DVALUE dvZ, DWORD dwStencil)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->Clear(dwCount, lpRects, dwFlags, dwColor, dvZ, dwStencil);
}

HRESULT Direct3D7DeviceWrapper::SetTransform(THIS_ D3DTRANSFORMSTATETYPE dtstTransformStateType,
                                             LPD3DMATRIX lpD3DMatrix)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetTransform(dtstTransformStateType, lpD3DMatrix);
}

HRESULT Direct3D7DeviceWrapper::GetTransform(THIS_ D3DTRANSFORMSTATETYPE dtstTransformStateType,
                                             LPD3DMATRIX lpD3DMatrix)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetTransform(dtstTransformStateType, lpD3DMatrix);
}

HRESULT Direct3D7DeviceWrapper::SetViewport(THIS_ LPD3DVIEWPORT7 lpViewport)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetViewport(lpViewport);
}

HRESULT Direct3D7DeviceWrapper::MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE dtstTransformStateType,
                                                  LPD3DMATRIX lpD3DMatrix)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->MultiplyTransform(dtstTransformStateType, lpD3DMatrix);
}

HRESULT Direct3D7DeviceWrapper::GetViewport(THIS_ LPD3DVIEWPORT7 lpViewport)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetViewport(lpViewport);
}

HRESULT Direct3D7DeviceWrapper::SetMaterial(THIS_ LPD3DMATERIAL7 lpMaterial)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetMaterial(lpMaterial);
}

HRESULT Direct3D7DeviceWrapper::GetMaterial(THIS_ LPD3DMATERIAL7 lpMaterial)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetMaterial(lpMaterial);
}

HRESULT Direct3D7DeviceWrapper::SetLight(THIS_ DWORD dwLightIndex, LPD3DLIGHT7 lpLight)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetLight(dwLightIndex, lpLight);
}

HRESULT Direct3D7DeviceWrapper::GetLight(THIS_ DWORD dwLightIndex, LPD3DLIGHT7 lpLight)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetLight(dwLightIndex, lpLight);
}

HRESULT Direct3D7DeviceWrapper::SetRenderState(THIS_ D3DRENDERSTATETYPE dwRenderStateType,
                                               DWORD dwRenderState)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetRenderState(dwRenderStateType, dwRenderState);
}

HRESULT Direct3D7DeviceWrapper::GetRenderState(THIS_ D3DRENDERSTATETYPE dwRenderStateType,
                                               LPDWORD lpdwRenderState)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetRenderState(dwRenderStateType, lpdwRenderState);
}

HRESULT Direct3D7DeviceWrapper::BeginStateBlock(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->BeginStateBlock();
}

HRESULT Direct3D7DeviceWrapper::EndStateBlock(THIS_ LPDWORD lpdwBlockHandle)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->EndStateBlock(lpdwBlockHandle);
}

HRESULT Direct3D7DeviceWrapper::PreLoad(THIS_ LPDIRECTDRAWSURFACE7 lpddsTexture)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->PreLoad(lpddsTexture);
}

HRESULT Direct3D7DeviceWrapper::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                                     DWORD dwVertexTypeDesc, LPVOID lpvVertices,
                                                     DWORD dwVertexCount, LPWORD lpwIndices,
                                                     DWORD dwIndexCount, DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->DrawIndexedPrimitive(d3dptPrimitiveType, dwVertexTypeDesc,
      lpvVertices, dwVertexCount, lpwIndices, dwIndexCount, dwFlags);
}

HRESULT Direct3D7DeviceWrapper::DrawPrimitiveStrided(THIS_ D3DPRIMITIVETYPE dptPrimitiveType,
                                                     DWORD dwVertexTypeDesc,
                                                     LPD3DDRAWPRIMITIVESTRIDEDDATA lpVertexArray,
                                                     DWORD dwVertexCount, DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->DrawPrimitiveStrided(dptPrimitiveType, dwVertexTypeDesc,
      lpVertexArray, dwVertexCount, dwFlags);
}

HRESULT Direct3D7DeviceWrapper::DrawIndexedPrimitiveStrided(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                                            DWORD dwVertexTypeDesc,
                                                            LPD3DDRAWPRIMITIVESTRIDEDDATA lpVertexArray,
                                                            DWORD dwVertexCount, LPWORD lpwIndices,
                                                            DWORD dwIndexCount, DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->DrawIndexedPrimitiveStrided(d3dptPrimitiveType, dwVertexTypeDesc,
      lpVertexArray, dwVertexCount, lpwIndices, dwIndexCount, dwFlags);
}

HRESULT Direct3D7DeviceWrapper::DrawIndexedPrimitiveVB(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                                       LPDIRECT3DVERTEXBUFFER7 lpd3dVertexBuffer,
                                                       DWORD dwStartVertex, DWORD dwNumVertices, 
                                                       LPWORD lpwIndices, DWORD dwIndexCount,
                                                       DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->DrawIndexedPrimitiveVB(d3dptPrimitiveType, lpd3dVertexBuffer,
      dwStartVertex, dwNumVertices, lpwIndices, dwIndexCount, dwFlags);
}

HRESULT Direct3D7DeviceWrapper::SetClipStatus(THIS_ LPD3DCLIPSTATUS lpD3DClipStatus)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetClipStatus(lpD3DClipStatus);
}

HRESULT Direct3D7DeviceWrapper::GetClipStatus(THIS_ LPD3DCLIPSTATUS lpD3DClipStatus)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetClipStatus(lpD3DClipStatus);
}

HRESULT Direct3D7DeviceWrapper::ComputeSphereVisibility(THIS_ LPD3DVECTOR lpCenters,
                                                        LPD3DVALUE lpRadii, DWORD dwNumSpheres,
                                                        DWORD dwFlags, LPDWORD lpdwReturnValues)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->ComputeSphereVisibility(lpCenters, lpRadii, dwNumSpheres,
      dwFlags, lpdwReturnValues);
}

HRESULT Direct3D7DeviceWrapper::GetTexture(THIS_ DWORD dwStage, LPDIRECTDRAWSURFACE7 *lplpTexture)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetTexture(dwStage, lplpTexture);
}

HRESULT Direct3D7DeviceWrapper::SetTexture(THIS_ DWORD dwStage, LPDIRECTDRAWSURFACE7 lpTexture)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetTexture(dwStage, lpTexture);
}

HRESULT Direct3D7DeviceWrapper::GetTextureStageState(THIS_ DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState,
                                                     LPDWORD lpdwValue)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetTextureStageState(dwStage, dwState, lpdwValue);
}

HRESULT Direct3D7DeviceWrapper::SetTextureStageState(THIS_ DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState,
                                                     DWORD dwValue)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetTextureStageState(dwStage, dwState, dwValue);
}

HRESULT Direct3D7DeviceWrapper::ValidateDevice(THIS_ LPDWORD lpdwPasses)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->ValidateDevice(lpdwPasses);
}

HRESULT Direct3D7DeviceWrapper::ApplyStateBlock(THIS_ DWORD dwBlockHandle)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->ApplyStateBlock(dwBlockHandle);
}

HRESULT Direct3D7DeviceWrapper::CaptureStateBlock(THIS_ DWORD dwBlockHandle)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->CaptureStateBlock(dwBlockHandle);
}

HRESULT Direct3D7DeviceWrapper::DeleteStateBlock(THIS_ DWORD dwBlockHandle)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->DeleteStateBlock(dwBlockHandle);
}

HRESULT Direct3D7DeviceWrapper::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE d3dsbType,
                                                 LPDWORD lpdwBlockHandle)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->CreateStateBlock(d3dsbType, lpdwBlockHandle);
}

HRESULT Direct3D7DeviceWrapper::Load(THIS_ LPDIRECTDRAWSURFACE7 lpDestTex, LPPOINT lpDestPoint,
                                     LPDIRECTDRAWSURFACE7 lpSrcTex, LPRECT lprcSrcRect,
  DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->Load(lpDestTex, lpDestPoint, lpSrcTex, lprcSrcRect, dwFlags);
}

HRESULT Direct3D7DeviceWrapper::LightEnable(THIS_ DWORD dwLightIndex, BOOL bEnable)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->LightEnable(dwLightIndex, bEnable);
}

HRESULT Direct3D7DeviceWrapper::GetLightEnable(THIS_ DWORD dwLightIndex, BOOL *pbEnable)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetLightEnable(dwLightIndex, pbEnable);
}

HRESULT Direct3D7DeviceWrapper::SetClipPlane(THIS_ DWORD dwIndex, D3DVALUE *pPlaneEquation)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->SetClipPlane(dwIndex, pPlaneEquation);
}

HRESULT Direct3D7DeviceWrapper::GetClipPlane(THIS_ DWORD dwIndex, D3DVALUE *pPlaneEquation)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetClipPlane(dwIndex, pPlaneEquation);
}

HRESULT Direct3D7DeviceWrapper::GetInfo(THIS_ DWORD dwDevInfoID, LPVOID pDevInfoStruct, 
                                        DWORD dwSize)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDevice->GetInfo(dwDevInfoID, pDevInfoStruct, dwSize);
}

} //namespace dx7fix
