#ifndef DIRECTDRAW_7_OBJECT_WRAPPER_H
#define DIRECTDRAW_7_OBJECT_WRAPPER_H

#include "windows.h"
#include "ddraw.h"
#include "d3d.h"

namespace dx7fix
{

class DirectDraw7ObjectWrapper : public IDirectDraw7
{
public:
  DirectDraw7ObjectWrapper(LPDIRECTDRAW7 originalObject);
  ~DirectDraw7ObjectWrapper();

  /*** IUnknown ***/
  HRESULT STDMETHODCALLTYPE QueryInterface(THIS_ REFIID riid, LPVOID FAR *ppvObj);
  ULONG STDMETHODCALLTYPE AddRef(THIS);
  ULONG STDMETHODCALLTYPE Release(THIS);

  /*** IDirectDraw7 ***/
  HRESULT STDMETHODCALLTYPE Compact();
  HRESULT STDMETHODCALLTYPE CreateClipper(
    _In_  DWORD                   dwFlags,
    _Out_ LPDIRECTDRAWCLIPPER FAR *lplpDDClipper,
    _In_  IUnknown FAR            *pUnkOuter
  );
  HRESULT STDMETHODCALLTYPE CreatePalette(
    _In_  DWORD                   dwFlags,
    _In_  LPPALETTEENTRY          lpDDColorArray,
    _Out_ LPDIRECTDRAWPALETTE FAR *lplpDDPalette,
    _In_  IUnknown FAR            *pUnkOuter
  );
  HRESULT STDMETHODCALLTYPE CreateSurface(
    _In_  LPDDSURFACEDESC2         lpDDSurfaceDesc2,
    _Out_ LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface,
    _In_  IUnknown FAR             *pUnkOuter
  );
  HRESULT STDMETHODCALLTYPE DuplicateSurface(
    _In_  LPDIRECTDRAWSURFACE7     lpDDSurface,
    _Out_ LPDIRECTDRAWSURFACE7 FAR *lplpDupDDSurface
  );
  HRESULT STDMETHODCALLTYPE EnumDisplayModes(
    _In_ DWORD                  dwFlags,
    _In_ LPDDSURFACEDESC2       lpDDSurfaceDesc2,
    _In_ LPVOID                 lpContext,
    _In_ LPDDENUMMODESCALLBACK2 lpEnumModesCallback
  );
  HRESULT STDMETHODCALLTYPE EnumSurfaces(
    _In_ DWORD                     dwFlags,
    _In_ LPDDSURFACEDESC2          lpDDSD2,
    _In_ LPVOID                    lpContext,
    _In_ LPDDENUMSURFACESCALLBACK7 lpEnumSurfacesCallback
  );
  HRESULT STDMETHODCALLTYPE EvaluateMode(
    _In_  DWORD dwFlags,
    _Out_ DWORD *pSecondsUntilTimeout
  );
  HRESULT STDMETHODCALLTYPE FlipToGDISurface();
  HRESULT STDMETHODCALLTYPE GetAvailableVidMem(
    _In_  LPDDSCAPS2 lpDDSCaps2,
    _Out_ LPDWORD    lpdwTotal,
    _Out_ LPDWORD    lpdwFree
  );
  HRESULT STDMETHODCALLTYPE GetCaps(
    _Out_ LPDDCAPS lpDDDriverCaps,
    _Out_ LPDDCAPS lpDDHELCaps
  );
  HRESULT STDMETHODCALLTYPE GetDeviceIdentifier(
    _Out_ LPDDDEVICEIDENTIFIER2 lpdddi,
    _In_  DWORD                 dwFlags
  );
  HRESULT STDMETHODCALLTYPE GetDisplayMode(
    _In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2
  );
  HRESULT STDMETHODCALLTYPE GetFourCCCodes(
    _Inout_ LPDWORD lpNumCodes,
    _Inout_ LPDWORD lpCodes
  );
  HRESULT STDMETHODCALLTYPE GetGDISurface(
    _Out_ LPDIRECTDRAWSURFACE7 FAR *lplpGDIDDSSurface
  );
  HRESULT STDMETHODCALLTYPE GetMonitorFrequency(
    _Out_ LPDWORD lpdwFrequency
  );
  HRESULT STDMETHODCALLTYPE GetScanLine(
    _Out_ LPDWORD lpdwScanLine
  );
  HRESULT STDMETHODCALLTYPE GetSurfaceFromDC(
    _In_  HDC                  hdc,
    _Out_ LPDIRECTDRAWSURFACE7 *lpDDS
  );
  HRESULT STDMETHODCALLTYPE GetVerticalBlankStatus(
    _Out_ LPBOOL lpbIsInVB
  );
  HRESULT STDMETHODCALLTYPE Initialize(
    _In_ GUID FAR *lpGUID
  );
  HRESULT STDMETHODCALLTYPE RestoreAllSurfaces();
  HRESULT STDMETHODCALLTYPE RestoreDisplayMode();
  HRESULT STDMETHODCALLTYPE SetCooperativeLevel(
    _In_ HWND  hWnd,
    _In_ DWORD dwFlags
  );
  HRESULT STDMETHODCALLTYPE SetDisplayMode(
    _In_ DWORD dwWidth,
    _In_ DWORD dwHeight,
    _In_ DWORD dwBPP,
    _In_ DWORD dwRefreshRate,
    _In_ DWORD dwFlags
  );
  HRESULT STDMETHODCALLTYPE StartModeTest(
    _In_ LPSIZE lpModesToTest,
    _In_ DWORD  dwNumEntries,
    _In_ DWORD  dwFlags
  );
  HRESULT STDMETHODCALLTYPE TestCooperativeLevel();
  HRESULT STDMETHODCALLTYPE WaitForVerticalBlank(
    _In_ DWORD  dwFlags,
    _In_ HANDLE hEvent
  );

private:
  LPDIRECTDRAW7 _originalDirectDraw7Object;
  ULONG _refCount;
};

} // namespace dx7fix

#endif // DIRECTDRAW_7_OBJECT_WRAPPER_H
