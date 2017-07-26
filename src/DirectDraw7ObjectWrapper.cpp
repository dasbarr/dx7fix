#include "DirectDraw7ObjectWrapper.h"
#include "Direct3D7ObjectWrapper.h"
#ifdef LOG_ALLOWED
#include "Logger.h"
#endif

namespace dx7fix
{

DirectDraw7ObjectWrapper::DirectDraw7ObjectWrapper(LPDIRECTDRAW7 originalObject)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _originalDirectDraw7Object = originalObject;
  _refCount = 1;
}

DirectDraw7ObjectWrapper::~DirectDraw7ObjectWrapper()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _originalDirectDraw7Object->Release();
  _originalDirectDraw7Object = nullptr;
}

/*** IUnknown methods ***/
HRESULT DirectDraw7ObjectWrapper::QueryInterface(THIS_ REFIID riid, LPVOID FAR *ppvObj)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  HRESULT queryResult = S_OK;

  if (riid == IID_IDirect3D7)
  {
#ifdef LOG_ALLOWED
    Logger::writeToLog("create and return IDirect3D7 wrapper");
#endif

    LPDIRECT3D7 poriginalObject;
    HRESULT creationResult = _originalDirectDraw7Object->QueryInterface(riid, (LPVOID *)&poriginalObject);

    LPDIRECT3D7 pwrappedObject = new Direct3D7ObjectWrapper(poriginalObject);
    *ppvObj = pwrappedObject;
  }
  else if (riid == IID_IUnknown)
  {
    *ppvObj = dynamic_cast<LPUNKNOWN>(this);
    AddRef();
  }
  else
  {
    queryResult = _originalDirectDraw7Object->QueryInterface(riid, ppvObj);
  }

  return queryResult;
}

ULONG DirectDraw7ObjectWrapper::AddRef(THIS)
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  _refCount++;
  return _refCount;
}

ULONG DirectDraw7ObjectWrapper::Release(THIS)
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

/*** IDirectDraw7 methods ***/
HRESULT DirectDraw7ObjectWrapper::Compact(
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->Compact();
}

HRESULT DirectDraw7ObjectWrapper::CreateClipper(
  _In_  DWORD                   dwFlags,
  _Out_ LPDIRECTDRAWCLIPPER FAR *lplpDDClipper,
  _In_  IUnknown FAR            *pUnkOuter
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->CreateClipper(dwFlags, lplpDDClipper, pUnkOuter);
}

HRESULT DirectDraw7ObjectWrapper::CreatePalette(
  _In_  DWORD                   dwFlags,
  _In_  LPPALETTEENTRY          lpDDColorArray,
  _Out_ LPDIRECTDRAWPALETTE FAR *lplpDDPalette,
  _In_  IUnknown FAR            *pUnkOuter
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->CreatePalette(dwFlags, lpDDColorArray,
      lplpDDPalette, pUnkOuter);
}

HRESULT DirectDraw7ObjectWrapper::CreateSurface(
  _In_  LPDDSURFACEDESC2         lpDDSurfaceDesc2,
  _Out_ LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface,
  _In_  IUnknown FAR             *pUnkOuter
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->CreateSurface(lpDDSurfaceDesc2, lplpDDSurface,
      pUnkOuter);
}

HRESULT DirectDraw7ObjectWrapper::DuplicateSurface(
  _In_  LPDIRECTDRAWSURFACE7     lpDDSurface,
  _Out_ LPDIRECTDRAWSURFACE7 FAR *lplpDupDDSurface
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->DuplicateSurface(lpDDSurface, lplpDupDDSurface);
}

HRESULT DirectDraw7ObjectWrapper::EnumDisplayModes(
  _In_ DWORD                  dwFlags,
  _In_ LPDDSURFACEDESC2       lpDDSurfaceDesc2,
  _In_ LPVOID                 lpContext,
  _In_ LPDDENUMMODESCALLBACK2 lpEnumModesCallback
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->EnumDisplayModes(dwFlags, lpDDSurfaceDesc2,
      lpContext, lpEnumModesCallback);
}

HRESULT DirectDraw7ObjectWrapper::EnumSurfaces(
  _In_ DWORD                     dwFlags,
  _In_ LPDDSURFACEDESC2          lpDDSD2,
  _In_ LPVOID                    lpContext,
  _In_ LPDDENUMSURFACESCALLBACK7 lpEnumSurfacesCallback
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->EnumSurfaces(dwFlags, lpDDSD2, lpContext,
      lpEnumSurfacesCallback);
}

HRESULT DirectDraw7ObjectWrapper::EvaluateMode(
  _In_  DWORD dwFlags,
  _Out_ DWORD *pSecondsUntilTimeout
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->EvaluateMode(dwFlags, pSecondsUntilTimeout);
}

HRESULT DirectDraw7ObjectWrapper::FlipToGDISurface(
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->FlipToGDISurface();
}

HRESULT DirectDraw7ObjectWrapper::GetAvailableVidMem(
  _In_  LPDDSCAPS2 lpDDSCaps2,
  _Out_ LPDWORD    lpdwTotal,
  _Out_ LPDWORD    lpdwFree
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetAvailableVidMem(lpDDSCaps2, lpdwTotal, lpdwFree);
}

HRESULT DirectDraw7ObjectWrapper::GetCaps(
  _Out_ LPDDCAPS lpDDDriverCaps,
  _Out_ LPDDCAPS lpDDHELCaps
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetCaps(lpDDDriverCaps, lpDDHELCaps);
}

HRESULT DirectDraw7ObjectWrapper::GetDeviceIdentifier(
  _Out_ LPDDDEVICEIDENTIFIER2 lpdddi,
  _In_  DWORD                 dwFlags
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetDeviceIdentifier(lpdddi, dwFlags);
}

HRESULT DirectDraw7ObjectWrapper::GetDisplayMode(
  _In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetDisplayMode(lpDDSurfaceDesc2);
}

HRESULT DirectDraw7ObjectWrapper::GetFourCCCodes(
  _Inout_ LPDWORD lpNumCodes,
  _Inout_ LPDWORD lpCodes
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetFourCCCodes(lpNumCodes, lpCodes);
}

HRESULT DirectDraw7ObjectWrapper::GetGDISurface(
  _Out_ LPDIRECTDRAWSURFACE7 FAR *lplpGDIDDSSurface
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetGDISurface(lplpGDIDDSSurface);
}

HRESULT DirectDraw7ObjectWrapper::GetMonitorFrequency(
  _Out_ LPDWORD lpdwFrequency
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetMonitorFrequency(lpdwFrequency);
}

HRESULT DirectDraw7ObjectWrapper::GetScanLine(
  _Out_ LPDWORD lpdwScanLine
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetScanLine(lpdwScanLine);
}

HRESULT DirectDraw7ObjectWrapper::GetSurfaceFromDC(
  _In_  HDC                  hdc,
  _Out_ LPDIRECTDRAWSURFACE7 *lpDDS
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetSurfaceFromDC(hdc, lpDDS);
}

HRESULT DirectDraw7ObjectWrapper::GetVerticalBlankStatus(
  _Out_ LPBOOL lpbIsInVB
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->GetVerticalBlankStatus(lpbIsInVB);
}

HRESULT DirectDraw7ObjectWrapper::Initialize(
  _In_ GUID FAR *lpGUID
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->Initialize(lpGUID);
}

HRESULT DirectDraw7ObjectWrapper::RestoreAllSurfaces(
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->RestoreAllSurfaces();
}

HRESULT DirectDraw7ObjectWrapper::RestoreDisplayMode(
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->RestoreDisplayMode();
}

HRESULT DirectDraw7ObjectWrapper::SetCooperativeLevel(
  _In_ HWND  hWnd,
  _In_ DWORD dwFlags
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->SetCooperativeLevel(hWnd, dwFlags);
}

HRESULT DirectDraw7ObjectWrapper::SetDisplayMode(
  _In_ DWORD dwWidth,
  _In_ DWORD dwHeight,
  _In_ DWORD dwBPP,
  _In_ DWORD dwRefreshRate,
  _In_ DWORD dwFlags
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->SetDisplayMode(dwWidth, dwHeight, dwBPP,
      dwRefreshRate, dwFlags);
}

HRESULT DirectDraw7ObjectWrapper::StartModeTest(
  _In_ LPSIZE lpModesToTest,
  _In_ DWORD  dwNumEntries,
  _In_ DWORD  dwFlags
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->StartModeTest(lpModesToTest, dwNumEntries, dwFlags);
}

HRESULT DirectDraw7ObjectWrapper::TestCooperativeLevel(
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->TestCooperativeLevel();
}

HRESULT DirectDraw7ObjectWrapper::WaitForVerticalBlank(
  _In_ DWORD  dwFlags,
  _In_ HANDLE hEvent
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  return _originalDirectDraw7Object->WaitForVerticalBlank(dwFlags, hEvent);
}

} //namespace dx7fix
