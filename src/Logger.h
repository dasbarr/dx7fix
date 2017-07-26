#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <ctime>

#include "windows.h"

namespace dx7fix
{

class Logger
{
public:
  enum priorityLevel { LOW, NORMAL, HIGH };

  static void openLog();
  static void closeLog();

  //simple log
  static void writeToLog(const char *message, priorityLevel priority = priorityLevel::NORMAL);
  //log ptr
  static void writeToLog(const char *ptrName, const void *ptr, priorityLevel priority = priorityLevel::NORMAL);
  //log GUID
  static void writeToLog(const char *guidDescription, const GUID& guid, priorityLevel priority = priorityLevel::NORMAL);
  //log DWORD
  static void writeToLog(const char *description, DWORD dword, priorityLevel priority = priorityLevel::NORMAL);
  //log float
  static void writeToLog(const char *description, float value, priorityLevel priority = priorityLevel::NORMAL);
  //log matrix row
  static void writeToLog(float i0, float i1, float i2, float i3, priorityLevel priority = priorityLevel::NORMAL);

  static void logFunctionCall(const char *funcName, priorityLevel priority = priorityLevel::NORMAL);

private:
  static const bool USE_LOG_RECORD_BUTTON;
  static const int LOG_RECORD_BUTTON_ID;
  static const bool PRIORITY_CHECK_NEEDED;

  static const char *_logFileName;
  static FILE *_logFile;
  //min priority level to write to log
  static priorityLevel _minPriorityToLog;

  static void getDateAndTime(char dest[], int destSize);
  static bool writingToLogAllowed(priorityLevel priority);
};

} //namespace dx7fix

#endif // LOGGER_H
