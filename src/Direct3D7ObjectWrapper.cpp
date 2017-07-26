#include "Direct3D7ObjectWrapper.h"
#include "Direct3D7DeviceWrapper.h"
#ifdef LOG_ALLOWED
#include "Logger.h"
#endif

namespace dx7fix
{

Direct3D7ObjectWrapper::Direct3D7ObjectWrapper(LPDIRECT3D7 originalObject)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _originalDirect3D7Object = originalObject;
  _refCount = 1;
}

Direct3D7ObjectWrapper::~Direct3D7ObjectWrapper()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _originalDirect3D7Object->Release();
  _originalDirect3D7Object = nullptr;
}

/*** IUnknown methods ***/
HRESULT Direct3D7ObjectWrapper::QueryInterface(THIS_ REFIID riid, LPVOID FAR *ppvObj)
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
    queryResult = _originalDirect3D7Object->QueryInterface(riid, ppvObj);
  }

  return queryResult;
}

ULONG Direct3D7ObjectWrapper::AddRef(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _refCount++;
  return _refCount;
}

ULONG Direct3D7ObjectWrapper::Release(THIS)
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

/*** IDirect3D7 (reimplemented) ***/
HRESULT Direct3D7ObjectWrapper::CreateDevice(THIS_ REFCLSID rclsid, LPDIRECTDRAWSURFACE7 lpDDS,
                                             LPDIRECT3DDEVICE7* lplpD3DDevice)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  LPDIRECT3DDEVICE7 originalDevice;
  HRESULT result = _originalDirect3D7Object->CreateDevice(rclsid, lpDDS, &originalDevice);

  LPDIRECT3DDEVICE7 wrappedDevice = (LPDIRECT3DDEVICE7)(new Direct3D7DeviceWrapper(originalDevice));
  *lplpD3DDevice = wrappedDevice;

  return result;
}

/*** IDirect3D7 ***/
HRESULT Direct3D7ObjectWrapper::EnumDevices(THIS_ LPD3DENUMDEVICESCALLBACK7 lpEnumDevicesCallback,
                                            LPVOID lpUserArg)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirect3D7Object->EnumDevices(lpEnumDevicesCallback, lpUserArg);
}

HRESULT Direct3D7ObjectWrapper::CreateVertexBuffer(THIS_ LPD3DVERTEXBUFFERDESC lpVBDesc,
                                                   LPDIRECT3DVERTEXBUFFER7* lplpD3DVertexBuffer,
                                                   DWORD dwFlags)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirect3D7Object->CreateVertexBuffer(lpVBDesc, lplpD3DVertexBuffer, dwFlags);
}

HRESULT Direct3D7ObjectWrapper::EnumZBufferFormats(THIS_ REFCLSID riidDevice,
                                                   LPD3DENUMPIXELFORMATSCALLBACK lpEnumCallback,
                                                   LPVOID lpContext)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirect3D7Object->EnumZBufferFormats(riidDevice, lpEnumCallback, lpContext);
}

HRESULT Direct3D7ObjectWrapper::EvictManagedTextures(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirect3D7Object->EvictManagedTextures();
}

} //namespace dx7fix
