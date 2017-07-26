#include "Logger.h"

#include <string>

namespace dx7fix
{

const bool Logger::USE_LOG_RECORD_BUTTON = true;
const int Logger::LOG_RECORD_BUTTON_ID = VK_F12;
const bool Logger::PRIORITY_CHECK_NEEDED = true;

const char *Logger::_logFileName = "dx7FixLog.txt";
FILE *Logger::_logFile = nullptr;
Logger::priorityLevel Logger::_minPriorityToLog = Logger::priorityLevel::NORMAL;

void Logger::getDateAndTime(char dest[], int destSize)
{
  time_t now = time(0);
  struct tm tstruct;
  localtime_s(&tstruct, &now);

  strftime(dest, destSize, "%Y-%m-%d, %X", &tstruct);
}

bool Logger::writingToLogAllowed(priorityLevel priority)
{
  //check if log file exists
  if (_logFile == nullptr)
    return false;

  //check log record button usage
  if (USE_LOG_RECORD_BUTTON)
  {
    SHORT recordKeyState = GetKeyState(LOG_RECORD_BUTTON_ID);
    if (recordKeyState != 1)
      return false;
  }

  //check priority
  if (PRIORITY_CHECK_NEEDED && priority < _minPriorityToLog)
    return false;

  return true;
}

void Logger::openLog()
{
  if (_logFile == nullptr)
  {
    //delete old file
    remove(_logFileName);

    errno_t openingResult = fopen_s(&_logFile, _logFileName, "w");
    if (openingResult != 0)
      _logFile = nullptr;
  }
}

void Logger::closeLog()
{
  if (_logFile != nullptr)
  {
    fclose(_logFile);
    _logFile = nullptr;
  }
}

//simple log
void Logger::writeToLog(const char *message, priorityLevel priority)
{
  if (writingToLogAllowed(priority))
  {
    char dateAndTime[80];
    getDateAndTime(dateAndTime, 80);
    fprintf(_logFile, "[%s] > %s\n", dateAndTime, message);
  }
}

//log ptr
void Logger::writeToLog(const char *ptrName, const void *ptr, priorityLevel priority)
{
  if (writingToLogAllowed(priority))
  {
    char dateAndTime[80];
    getDateAndTime(dateAndTime, 80);
    fprintf(_logFile, "[%s] > Pointer to '%s' is %p\n", dateAndTime, ptrName, ptr);
  }
}

//log GUID
void Logger::writeToLog(const char *guidDescription, const GUID &guid, priorityLevel priority)
{
  if (writingToLogAllowed(priority))
  {
    char dateAndTime[80];
    getDateAndTime(dateAndTime, 80);
    fprintf(_logFile, "[%s] > '%s', {0x%X-%d-%d-%0d%0d%0d%0d%0d%0d%0d%0d}\n", dateAndTime, guidDescription,
      guid.Data1, guid.Data2, guid.Data3,
      guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
  }
}

//log DWORD
void Logger::writeToLog(const char *description, DWORD dword, priorityLevel priority)
{
  if (writingToLogAllowed(priority))
  {
    char dateAndTime[80];
    getDateAndTime(dateAndTime, 80);
    fprintf(_logFile, "[%s] > '%s': %u\n", dateAndTime, description, dword);
  }
}

//log float
void Logger::writeToLog(const char *description, float value, priorityLevel priority)
{
  if (writingToLogAllowed(priority))
  {
    char dateAndTime[80];
    getDateAndTime(dateAndTime, 80);
    fprintf(_logFile, "[%s] > '%s': %f\n", dateAndTime, description, value);
  }
}

//log matrix row
void Logger::writeToLog(float i0, float i1, float i2, float i3, priorityLevel priority)
{
  if (writingToLogAllowed(priority))
  {
    char dateAndTime[80];
    getDateAndTime(dateAndTime, 80);
    fprintf(_logFile, "[%s] >    %f %f %f %f\n", dateAndTime, i0, i1, i2, i3);
  }
}

void Logger::logFunctionCall(const char *funcName, priorityLevel priority)
{
  if (writingToLogAllowed(priority))
  {
    char dateAndTime[80];
    getDateAndTime(dateAndTime, 80);
    fprintf(_logFile, "[%s] > %s called\n", dateAndTime, funcName);
  }
}

} //namespace dx7fix
