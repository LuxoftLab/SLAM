#include <Common/LogUtils/CLogger.hpp>

CLogger CLogger::instance;

CLogger::CLogger():active(false),
                   logStream(NULL),
                   pathToLogFile("../CVNAR_LOG.txt"){}

const CLogger& CLogger::getInstance()
{
   return instance;
}

void CLogger::setWriteMode(const output mode)
{
   logStream = mode ? &instance.fileStream : &std::cout;
}

void CLogger::setDetalizationLevel(const logLevel level)
{
   instance.minLogLevel = level;
}

void CLogger::setLogFilePath(const std::string& path)
{
   instance.pathToLogFile = path;
}

const std::string CLogger::toString(logLevel level)
{
   static const char* const buffer[] = {"ERROR", "WARNING", "DEBUG", "MSG"};
   return buffer[level];
}

void CLogger::start(logLevel level = ERROR)
{
   instance.active = true;
   instance.minLogLevel = level;
   instance.fileStream.open(pathToLogFile);
}

void CLogger::stop()
{
   instance.active = false;
   if (instance.fileStream.is_open())
      instance.fileStream.close();
}

void CLogger::log(const logLevel level, const std::string& message)
{
   if (instance.active &&
       logStream != NULL &&
       level >= instance.minLogLevel)
   {
      *logStream << toString(level)
                 << ": "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const logLevel level, const int message)
{
   if (instance.active &&
       logStream != NULL &&
       level >= instance.minLogLevel)
   {
      *logStream << toString(level)
                 << ": "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const logLevel level, const long long message)
{
   if (instance.active &&
       logStream != NULL &&
       level >= instance.minLogLevel)
   {
      *logStream << toString(level)
                 << ": "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const logLevel level, const float message)
{
   if (instance.active &&
       logStream != NULL &&
       level >= instance.minLogLevel)
   {
      *logStream << toString(level)
                 << ": "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const logLevel level, const double message)
{
   if (instance.active &&
       logStream != NULL &&
       level >= instance.minLogLevel)
   {
      *logStream << toString(level)
                 << ": "
                 << message
                 << std::endl;
   }
}
