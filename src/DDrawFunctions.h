#ifndef DDRAW_FUNCTIONS_H
#define DDRAW_FUNCTIONS_H

#include "windows.h"

namespace dx7fix
{

HRESULT STDMETHODCALLTYPE ProxyDirectDrawCreateEx(
  _In_  GUID FAR     *lpGUID,
  _Out_ LPVOID       *lplpDD,
  _In_  REFIID       iid,
  _In_  IUnknown FAR *pUnkOuter
);

//Following functions only call original ddraw functions
void ProxyAcquireDDThreadLock();
void ProxyCompleteCreateSysmemSurface();
void ProxyD3DParseUnknownCommand();
void ProxyDDGetAttachedSurfaceLcl();
void ProxyDDInternalLock();
void ProxyDDInternalUnlock();
void ProxyDSoundHelp();
void ProxyDirectDrawCreate();
void ProxyDirectDrawCreateClipper();
void ProxyDirectDrawEnumerateA();
void ProxyDirectDrawEnumerateExA();
void ProxyDirectDrawEnumerateExW();
void ProxyDirectDrawEnumerateW();
void ProxyDllCanUnloadNow();
void ProxyDllGetClassObject();
void ProxyGetDDSurfaceLocal();
void ProxyGetOLEThunkData();
void ProxyGetSurfaceFromDC();
void ProxyRegisterSpecialCase();
void ProxyReleaseDDThreadLock();
void ProxySetAppCompatData();

} //namespace dx7fix

#endif // DDRAW_FUNCTIONS_H
