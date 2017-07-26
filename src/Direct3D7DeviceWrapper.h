#ifndef DIRECT3D7_DEVICE_WRAPPER
#define DIRECT3D7_DEVICE_WRAPPER

#include "d3d.h"
#include "d3dtypes.h"
#include "math.h"

namespace dx7fix
{

class Direct3D7DeviceWrapper : public IDirect3DDevice7
{
public:
  Direct3D7DeviceWrapper(LPDIRECT3DDEVICE7 originalDevice);
  ~Direct3D7DeviceWrapper();

  /*** IUnknown methods ***/
  HRESULT STDMETHODCALLTYPE QueryInterface(THIS_ REFIID riid, LPVOID FAR *ppvObj);
  ULONG STDMETHODCALLTYPE AddRef(THIS);
  ULONG STDMETHODCALLTYPE Release(THIS);

  /*** IDirect3DDevice7 (reimplemented) ***/
  HRESULT STDMETHODCALLTYPE DrawPrimitive(THIS_ D3DPRIMITIVETYPE dptPrimitiveType,
                                          DWORD dwVertexTypeDesc, LPVOID lpvVertices,
                                          DWORD dwVertexCount, DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE DrawPrimitiveVB(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                            LPDIRECT3DVERTEXBUFFER7 lpd3dVertexBuffer,
                                            DWORD dwStartVertex, DWORD dwNumVertices,
                                            DWORD dwFlags);

  /*** IDirect3DDevice7 ***/
  HRESULT STDMETHODCALLTYPE GetCaps(THIS_ LPD3DDEVICEDESC7 lpD3DDevDesc);
  HRESULT STDMETHODCALLTYPE EnumTextureFormats(THIS_ LPD3DENUMPIXELFORMATSCALLBACK lpd3dEnumPixelProc,
                                               LPVOID lpArg);
  HRESULT STDMETHODCALLTYPE BeginScene(THIS);
  HRESULT STDMETHODCALLTYPE EndScene(THIS);
  HRESULT STDMETHODCALLTYPE GetDirect3D(THIS_ LPDIRECT3D7 *lplpD3D);
  HRESULT STDMETHODCALLTYPE SetRenderTarget(THIS_ LPDIRECTDRAWSURFACE7 lpNewRenderTarget,
                                            DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE GetRenderTarget(THIS_ LPDIRECTDRAWSURFACE7 *lplpRenderTarget);
  HRESULT STDMETHODCALLTYPE Clear(THIS_ DWORD dwCount, LPD3DRECT lpRects, DWORD dwFlags,
                                  D3DCOLOR dwColor, D3DVALUE dvZ, DWORD dwStencil);
  HRESULT STDMETHODCALLTYPE SetTransform(THIS_ D3DTRANSFORMSTATETYPE dtstTransformStateType,
                                         LPD3DMATRIX lpD3DMatrix);
  HRESULT STDMETHODCALLTYPE GetTransform(THIS_ D3DTRANSFORMSTATETYPE dtstTransformStateType,
                                         LPD3DMATRIX lpD3DMatrix);
  HRESULT STDMETHODCALLTYPE SetViewport(THIS_ LPD3DVIEWPORT7 lpViewport);
  HRESULT STDMETHODCALLTYPE MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE dtstTransformStateType,
                                              LPD3DMATRIX lpD3DMatrix);
  HRESULT STDMETHODCALLTYPE GetViewport(THIS_ LPD3DVIEWPORT7 lpViewport);
  HRESULT STDMETHODCALLTYPE SetMaterial(THIS_ LPD3DMATERIAL7 lpMaterial);
  HRESULT STDMETHODCALLTYPE GetMaterial(THIS_ LPD3DMATERIAL7 lpMaterial);
  HRESULT STDMETHODCALLTYPE SetLight(THIS_ DWORD dwLightIndex, LPD3DLIGHT7 lpLight);
  HRESULT STDMETHODCALLTYPE GetLight(THIS_ DWORD dwLightIndex, LPD3DLIGHT7 lpLight);
  HRESULT STDMETHODCALLTYPE SetRenderState(THIS_ D3DRENDERSTATETYPE dwRenderStateType,
                                           DWORD dwRenderState);
  HRESULT STDMETHODCALLTYPE GetRenderState(THIS_ D3DRENDERSTATETYPE dwRenderStateType,
                                           LPDWORD lpdwRenderState);
  HRESULT STDMETHODCALLTYPE BeginStateBlock(THIS);
  HRESULT STDMETHODCALLTYPE EndStateBlock(THIS_ LPDWORD lpdwBlockHandle);
  HRESULT STDMETHODCALLTYPE PreLoad(THIS_ LPDIRECTDRAWSURFACE7 lpddsTexture);
  HRESULT STDMETHODCALLTYPE DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                                 DWORD dwVertexTypeDesc, LPVOID lpvVertices,
                                                 DWORD dwVertexCount, LPWORD lpwIndices,
                                                 DWORD dwIndexCount, DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE DrawPrimitiveStrided(THIS_ D3DPRIMITIVETYPE dptPrimitiveType,
                                                 DWORD dwVertexTypeDesc,
                                                 LPD3DDRAWPRIMITIVESTRIDEDDATA lpVertexArray,
                                                 DWORD dwVertexCount, DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE DrawIndexedPrimitiveStrided(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                                        DWORD dwVertexTypeDesc,
                                                        LPD3DDRAWPRIMITIVESTRIDEDDATA lpVertexArray,
                                                        DWORD dwVertexCount, LPWORD lpwIndices,
                                                        DWORD dwIndexCount, DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE DrawIndexedPrimitiveVB(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,
                                                   LPDIRECT3DVERTEXBUFFER7 lpd3dVertexBuffer,
                                                   DWORD dwStartVertex, DWORD dwNumVertices,
                                                   LPWORD lpwIndices, DWORD dwIndexCount,
                                                   DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE SetClipStatus(THIS_ LPD3DCLIPSTATUS lpD3DClipStatus);
  HRESULT STDMETHODCALLTYPE GetClipStatus(THIS_ LPD3DCLIPSTATUS lpD3DClipStatus);
  HRESULT STDMETHODCALLTYPE ComputeSphereVisibility(THIS_ LPD3DVECTOR lpCenters, LPD3DVALUE lpRadii,
                                                    DWORD dwNumSpheres, DWORD dwFlags,
                                                    LPDWORD lpdwReturnValues);
  HRESULT STDMETHODCALLTYPE GetTexture(THIS_ DWORD dwStage, LPDIRECTDRAWSURFACE7 *lplpTexture);
  HRESULT STDMETHODCALLTYPE SetTexture(THIS_ DWORD dwStage, LPDIRECTDRAWSURFACE7 lpTexture);
  HRESULT STDMETHODCALLTYPE GetTextureStageState(THIS_ DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState,
                                                 LPDWORD lpdwValue);
  HRESULT STDMETHODCALLTYPE SetTextureStageState(THIS_ DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState,
                                                 DWORD dwValue);
  HRESULT STDMETHODCALLTYPE ValidateDevice(THIS_ LPDWORD lpdwPasses);
  HRESULT STDMETHODCALLTYPE ApplyStateBlock(THIS_ DWORD dwBlockHandle);
  HRESULT STDMETHODCALLTYPE CaptureStateBlock(THIS_ DWORD dwBlockHandle);
  HRESULT STDMETHODCALLTYPE DeleteStateBlock(THIS_ DWORD dwBlockHandle);
  HRESULT STDMETHODCALLTYPE CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE d3dsbType,
                                             LPDWORD lpdwBlockHandle);
  HRESULT STDMETHODCALLTYPE Load(THIS_ LPDIRECTDRAWSURFACE7 lpDestTex, LPPOINT lpDestPoint,
                                 LPDIRECTDRAWSURFACE7 lpSrcTex, LPRECT lprcSrcRect,
                                 DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE LightEnable(THIS_ DWORD dwLightIndex, BOOL bEnable);
  HRESULT STDMETHODCALLTYPE GetLightEnable(THIS_ DWORD dwLightIndex, BOOL *pbEnable);
  HRESULT STDMETHODCALLTYPE SetClipPlane(THIS_ DWORD dwIndex, D3DVALUE *pPlaneEquation);
  HRESULT STDMETHODCALLTYPE GetClipPlane(THIS_ DWORD dwIndex, D3DVALUE *pPlaneEquation);
  HRESULT STDMETHODCALLTYPE GetInfo(THIS_ DWORD dwDevInfoID, LPVOID pDevInfoStruct,
                                    DWORD dwSize);

private:
  LPDIRECT3DDEVICE7 _originalDevice;
  ULONG _refCount;

  //indices sequence like that: {0, 1, 2, 3, ...}
  WORD *_linearIndices;
  DWORD _numLinearIndices = 0;

  //indices for triangle fan like that: {0, 1, 2, 0, 2, 3, ...}
  WORD *_triangleFanIndices;
  DWORD _numTriangleFanIndices = 0;

  //indices for line list like this: {0, 1, 1, 2, 2, 3, ...}
  WORD *_lineListIndices;
  DWORD _numLineListIndices = 0;
};

} //namespace dx7fix

#endif // DIRECT3D7_DEVICE_WRAPPER
