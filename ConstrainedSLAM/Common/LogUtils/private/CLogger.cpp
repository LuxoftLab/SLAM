#include "CLogger.hpp"

CLogger::CLogger():logStream(NULL),
                    currentLogLevel(ERROR)
{
    fileStream.open("CVNAR_LOG.txt");
}

CLogger &CLogger::getInstance()
{
   static CLogger instance;
   return instance;
}

void CLogger::config(const unsigned int configParam)
{
    switch (configParam){
        case OFF:
            this->logStream = NULL;
        break;
        case TO_CONSOLE:
            this->logStream = &std::cout;
        break;
        case TO_FILE:
            this->logStream = &fileStream;
        break;
    }
}

void CLogger::setDetalizationLevel(const unsigned int level)
{
   this->currentLogLevel = level;
}

void CLogger::log(const unsigned int level, const std::string& message)
{
   if (logStream != NULL &&
       level <= currentLogLevel)
   {
      *logStream << "["
                 << toString(level)
                 << "]: "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const unsigned int level, const int message)
{
   if (logStream != NULL &&
       level >= currentLogLevel)
   {
      *logStream << "["
                 << toString(level)
                 << "]: "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const unsigned int level, const long long message)
{
   if (logStream != NULL &&
       level >= currentLogLevel)
   {
      *logStream << "["
                 << toString(level)
                 << "]: "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const unsigned int level, const float message)
{
   if (logStream != NULL &&
       level >= currentLogLevel)
   {
      *logStream << "["
                 << toString(level)
                 << "]: "
                 << message
                 << std::endl;
   }
}

void CLogger::log(const unsigned int level, const double message)
{
   if (logStream != NULL &&
       level >= currentLogLevel)
   {
      *logStream << "["
                 << toString(level)
                 << "]: "
                 << message
                 << std::endl;
   }
}

const std::string CLogger::toString(const unsigned int level)
{
   const char* const buffer[] = {"ERROR", "WARNING","MESSAGE"};
   return buffer[level];
}

CLogger::~CLogger(){
    if (this->fileStream.is_open())
       this->fileStream.close();
}
