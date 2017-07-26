#include "windows.h"
#include <tchar.h>

#include "DDrawStruct.h"
#ifdef LOG_ALLOWED
#include "Logger.h"
#endif

namespace dx7fix
{

ddraw_dll original_ddraw;
void initOriginalDdraw();

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
  switch (ul_reason_for_call)
  {
    case DLL_PROCESS_ATTACH:
#ifdef LOG_ALLOWED
      Logger::openLog();
#endif
      initOriginalDdraw();
      break;

    case DLL_PROCESS_DETACH:
#ifdef LOG_ALLOWED
      Logger::closeLog();
#endif
      FreeLibrary(original_ddraw.dll);
      break;
  }

  return TRUE;
}

void initOriginalDdraw()
{
  TCHAR systemPath[MAX_PATH];
  GetSystemDirectory(systemPath, MAX_PATH);
  _tcscat_s(systemPath, _T("\\ddraw.dll"));

  original_ddraw.dll = LoadLibrary(systemPath);
  if (original_ddraw.dll == NULL)
  {
    MessageBox(0, "Cannot load original ddraw.dll", NULL, MB_ICONERROR | MB_OK);
    ExitProcess(1);
  }

  //get all original proc addresses
  original_ddraw.DirectDrawCreateEx = GetProcAddress(original_ddraw.dll, "DirectDrawCreateEx");
  original_ddraw.AcquireDDThreadLock = GetProcAddress(original_ddraw.dll, "AcquireDDThreadLock");
  original_ddraw.CompleteCreateSysmemSurface = GetProcAddress(original_ddraw.dll, "CompleteCreateSysmemSurface");
  original_ddraw.D3DParseUnknownCommand = GetProcAddress(original_ddraw.dll, "D3DParseUnknownCommand");
  original_ddraw.DDGetAttachedSurfaceLcl = GetProcAddress(original_ddraw.dll, "DDGetAttachedSurfaceLcl");
  original_ddraw.DDInternalLock = GetProcAddress(original_ddraw.dll, "DDInternalLock");
  original_ddraw.DDInternalUnlock = GetProcAddress(original_ddraw.dll, "DDInternalUnlock");
  original_ddraw.DSoundHelp = GetProcAddress(original_ddraw.dll, "DSoundHelp");
  original_ddraw.DirectDrawCreate = GetProcAddress(original_ddraw.dll, "DirectDrawCreate");
  original_ddraw.DirectDrawCreateClipper = GetProcAddress(original_ddraw.dll, "DirectDrawCreateClipper");
  original_ddraw.DirectDrawEnumerateA = GetProcAddress(original_ddraw.dll, "DirectDrawEnumerateA");
  original_ddraw.DirectDrawEnumerateExA = GetProcAddress(original_ddraw.dll, "DirectDrawEnumerateExA");
  original_ddraw.DirectDrawEnumerateExW = GetProcAddress(original_ddraw.dll, "DirectDrawEnumerateExW");
  original_ddraw.DirectDrawEnumerateW = GetProcAddress(original_ddraw.dll, "DirectDrawEnumerateW");
  original_ddraw.DllCanUnloadNow = GetProcAddress(original_ddraw.dll, "DllCanUnloadNow");
  original_ddraw.DllGetClassObject = GetProcAddress(original_ddraw.dll, "DllGetClassObject");
  original_ddraw.GetDDSurfaceLocal = GetProcAddress(original_ddraw.dll, "GetDDSurfaceLocal");
  original_ddraw.GetOLEThunkData = GetProcAddress(original_ddraw.dll, "GetOLEThunkData");
  original_ddraw.GetSurfaceFromDC = GetProcAddress(original_ddraw.dll, "GetSurfaceFromDC");
  original_ddraw.RegisterSpecialCase = GetProcAddress(original_ddraw.dll, "RegisterSpecialCase");
  original_ddraw.ReleaseDDThreadLock = GetProcAddress(original_ddraw.dll, "ReleaseDDThreadLock");
  original_ddraw.SetAppCompatData = GetProcAddress(original_ddraw.dll, "SetAppCompatData");
}

} //namespace dx7fix
