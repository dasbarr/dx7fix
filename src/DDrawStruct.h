#ifndef DDRAW_STRUCT_H
#define DDRAW_STRUCT_H

#include "windows.h"

namespace dx7fix
{

struct ddraw_dll
{
  HMODULE dll;

  FARPROC AcquireDDThreadLock;
  FARPROC CompleteCreateSysmemSurface;
  FARPROC D3DParseUnknownCommand;
  FARPROC DDGetAttachedSurfaceLcl;
  FARPROC DDInternalLock;
  FARPROC DDInternalUnlock;
  FARPROC DSoundHelp;
  FARPROC DirectDrawCreate;
  FARPROC DirectDrawCreateClipper;
  FARPROC DirectDrawCreateEx;
  FARPROC DirectDrawEnumerateA;
  FARPROC DirectDrawEnumerateExA;
  FARPROC DirectDrawEnumerateExW;
  FARPROC DirectDrawEnumerateW;
  FARPROC DllCanUnloadNow;
  FARPROC DllGetClassObject;
  FARPROC GetDDSurfaceLocal;
  FARPROC GetOLEThunkData;
  FARPROC GetSurfaceFromDC;
  FARPROC RegisterSpecialCase;
  FARPROC ReleaseDDThreadLock;
  FARPROC SetAppCompatData;
};

extern ddraw_dll original_ddraw;

} //namespace dx7fix

#endif // DDRAW_STRUCT_H
