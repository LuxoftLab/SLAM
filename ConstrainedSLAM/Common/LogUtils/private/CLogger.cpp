#include "CLogger.hpp"

CLogger::CLogger():logStream(NULL),
                   currentLogLevel(ERROR),
                   isEnabled(0)
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
   configParam ? this->logStream = &fileStream : this->logStream = &std::cout;
}

void CLogger::setDetalizationLevel(const unsigned int level)
{
   this->currentLogLevel = level;
}

void CLogger::setMode(const unsigned int mode)
{
   this->isEnabled = mode;
}

int CLogger::getLogLevel()
{
   return this->currentLogLevel;
}

bool CLogger::getMode()
{
   return this ->isEnabled;
}

CLogger::~CLogger(){
   if (this->fileStream.is_open())
      this->fileStream.close();
}

std::ostream& CLogger::write(unsigned int level)
{
   if(logStream != NULL)
      if (level == ERROR ||
          (level <= currentLogLevel &&
           isEnabled))
      {
         *logStream << "["
                    << toString(level)
                    << "]: ";

      }
   return *logStream;
}

const std::string CLogger::toString(const unsigned int level)
{
   static const char* const buffer[] = {"ERROR", "WARNING","MESSAGE"};
   return buffer[level];
}
