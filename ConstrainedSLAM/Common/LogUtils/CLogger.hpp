#ifndef CLOGGER_HPP
#define CLOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <boost/shared_ptr.hpp>

#ifdef ENABLE_LOGGER

#define CVNAR_LOGGER_START(LOGGING_LEVEL)       CLogger::start(LOGGING_LEVEL);
#define CVNAR_LOGGER_STOP()                     CLogger::stop();
#define CVNAR_LOGGER_WRITE(PRIORITY, MESSAGE)   CLogger::log(PRIORITY, MESSAGE);
#define SET_WRITE_MODE(MODE)                    CLogger::setWriteMode(MODE);
#define SET_DETALIZATION_LEVEL(LEVEL)           CLogger::setDetalizationLevel(LEVEL);
#define SET_LOG_PATH(PATH)                      CLogger::setLogFilePath(PATH);

#else

#define CVNAR_LOGGER_START(LOGGING_LEVEL)
#define CVNAR_LOGGER_STOP()
#define CVNAR_LOGGER_WRITE(PRIORITY, MESSAGE)
#define SET_WRITE_MODE(MODE)
#define SET_DETALIZATION_LEVEL(LEVEL)
#define SET_LOG_PATH(PATH)

#endif

enum logLevel
{
   ERROR,
   WARNING,
   DEBUG,
   MSG
};

enum output
{
    TO_CONSOLE,
    TO_FILE
};

class CLogger
{
public:
   static const CLogger & getInstance();
   void setWriteMode(const output mode);
   void setDetalizationLevel(const logLevel level);
   void setLogFilePath(const std::string& path);

   void start(logLevel level);
   void stop();

   void log(const logLevel level, const std::string& message);
   void log(const logLevel level, const int message);
   void log(const logLevel level, const long long message);
   void log(const logLevel level, const float message);
   void log(const logLevel level, const double message);

private:
   CLogger();
   CLogger(CLogger const&);
   void operator = (CLogger const&);

   const std::string toString(logLevel level);

   std::ofstream fileStream;
   std::ostream* logStream;
   std::string pathToLogFile;
   bool active;
   logLevel minLogLevel;
   static CLogger instance;
};

#endif // СLOGGER_HPP
