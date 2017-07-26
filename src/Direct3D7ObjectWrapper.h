#ifndef DIRECT3D7_OBJECT_WRAPPER_H
#define DIRECT3D7_OBJECT_WRAPPER_H

#include "d3d.h"

namespace dx7fix
{

class Direct3D7ObjectWrapper : public IDirect3D7
{
public:
  Direct3D7ObjectWrapper(LPDIRECT3D7 originalObject);
  ~Direct3D7ObjectWrapper();

  /*** IUnknown ***/
  HRESULT STDMETHODCALLTYPE QueryInterface(THIS_ REFIID riid, LPVOID FAR *ppvObj);
  ULONG STDMETHODCALLTYPE AddRef(THIS);
  ULONG STDMETHODCALLTYPE Release(THIS);

  /*** IDirect3D7 (reimplemented) ***/
  HRESULT STDMETHODCALLTYPE CreateDevice(THIS_ REFCLSID rclsid, LPDIRECTDRAWSURFACE7 lpDDS,
                                         LPDIRECT3DDEVICE7* lplpD3DDevice);

  /*** IDirect3D7 ***/
  HRESULT STDMETHODCALLTYPE EnumDevices(THIS_ LPD3DENUMDEVICESCALLBACK7 lpEnumDevicesCallback,
                                        LPVOID lpUserArg);
  HRESULT STDMETHODCALLTYPE CreateVertexBuffer(THIS_ LPD3DVERTEXBUFFERDESC lpVBDesc,
                                               LPDIRECT3DVERTEXBUFFER7* lplpD3DVertexBuffer,
                                               DWORD dwFlags);
  HRESULT STDMETHODCALLTYPE EnumZBufferFormats(THIS_ REFCLSID riidDevice,
                                               LPD3DENUMPIXELFORMATSCALLBACK lpEnumCallback,
                                               LPVOID lpContext);
  HRESULT STDMETHODCALLTYPE EvictManagedTextures(THIS);

private:
  LPDIRECT3D7 _originalDirect3D7Object;
  ULONG _refCount;
};

} //namespace dx7fix

#endif // DIRECT3D7_OBJECT_WRAPPER_H
