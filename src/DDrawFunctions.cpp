#include "DDrawFunctions.h"

#include "DDrawStruct.h"
#include "DirectDraw7ObjectWrapper.h"

#ifdef LOG_ALLOWED
#include "Logger.h"
#endif

namespace dx7fix
{

HRESULT STDMETHODCALLTYPE ProxyDirectDrawCreateEx(
  _In_  GUID FAR     *lpGUID,
  _Out_ LPVOID       *lplpDD,
  _In_  REFIID       iid,
  _In_  IUnknown FAR *pUnkOuter
) {
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif

  typedef BOOL(STDMETHODCALLTYPE *DirectDrawCreateExFuncAddress)(GUID FAR *, LPVOID *, REFIID, IUnknown FAR *);
  DirectDrawCreateExFuncAddress originalDirectDrawCreateEx = (DirectDrawCreateExFuncAddress&)original_ddraw.DirectDrawCreateEx;

  LPDIRECTDRAW7 originalDDObject;
  HRESULT creationResult = originalDirectDrawCreateEx(lpGUID, (LPVOID *)&originalDDObject, iid, pUnkOuter);
  LPDIRECTDRAW7 wrappedDDObject = dynamic_cast<LPDIRECTDRAW7>(new DirectDraw7ObjectWrapper(originalDDObject));
  *lplpDD = wrappedDDObject;

  return creationResult;
}

//Following functions only call original ddraw functions
__declspec(naked) void ProxyAcquireDDThreadLock()
{
#ifdef LOG_ALLOWED
  //That function is being called very often, so it's not necessary to write it
  //to the log in common cases.
  Logger::logFunctionCall(__FUNCTION__, Logger::priorityLevel::LOW);
#endif
  _asm { jmp[original_ddraw.AcquireDDThreadLock] }
}

__declspec(naked) void ProxyCompleteCreateSysmemSurface()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.CompleteCreateSysmemSurface] }
}

__declspec(naked) void ProxyD3DParseUnknownCommand()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.D3DParseUnknownCommand] }
}

__declspec(naked) void ProxyDDGetAttachedSurfaceLcl()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DDGetAttachedSurfaceLcl] }
}

__declspec(naked) void ProxyDDInternalLock()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DDInternalLock] }
}

__declspec(naked) void ProxyDDInternalUnlock()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DDInternalUnlock] }
}

__declspec(naked) void ProxyDSoundHelp()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DSoundHelp] }
}

__declspec(naked) void ProxyDirectDrawCreate()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DirectDrawCreate] }
}

__declspec(naked) void ProxyDirectDrawCreateClipper()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DirectDrawCreateClipper] }
}

__declspec(naked) void ProxyDirectDrawEnumerateA()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DirectDrawEnumerateA] }
}

__declspec(naked) void ProxyDirectDrawEnumerateExA()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DirectDrawEnumerateExA] }
}

__declspec(naked) void ProxyDirectDrawEnumerateExW()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DirectDrawEnumerateExW] }
}

__declspec(naked) void ProxyDirectDrawEnumerateW()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DirectDrawEnumerateW] }
}

__declspec(naked) void ProxyDllCanUnloadNow()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DllCanUnloadNow] }
}

__declspec(naked) void ProxyDllGetClassObject()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.DllGetClassObject] }
}

__declspec(naked) void ProxyGetDDSurfaceLocal()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.GetDDSurfaceLocal] }
}

__declspec(naked) void ProxyGetOLEThunkData()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.GetOLEThunkData] }
}

__declspec(naked) void ProxyGetSurfaceFromDC()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.GetSurfaceFromDC] }
}

__declspec(naked) void ProxyRegisterSpecialCase()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.RegisterSpecialCase] }
}

__declspec(naked) void ProxyReleaseDDThreadLock()
{
#ifdef LOG_ALLOWED
  //That function is being called very often, so it's not necessary to write it
  //to the log in common cases.
  Logger::logFunctionCall(__FUNCTION__, Logger::priorityLevel::LOW);
#endif
  _asm { jmp[original_ddraw.ReleaseDDThreadLock] }
}

__declspec(naked) void ProxySetAppCompatData()
{
#ifdef LOG_ALLOWED
  Logger::logFunctionCall(__FUNCTION__);
#endif
  _asm { jmp[original_ddraw.SetAppCompatData] }
}

} //namespace dx7fix
