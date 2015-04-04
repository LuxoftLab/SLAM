#include "CLogger.hpp"

CLogger::CLogger():logStream(&std::cout),
                   currentLogLevel(ERROR),
                   isEnabled(0),
                   fakeStream(0)
{
   fileStream.open("CVNAR_LOG.txt");
}

CLogger &CLogger::getInstance()
{
   static CLogger instance;
   return instance;
}

void CLogger::setOutput(const unsigned int configParam)
{
   if(configParam == TO_FILE)
      this->logStream = &fileStream;
   else
      this->logStream = &std::cout;
}

void CLogger::setLogFilePath(const std::string path){
   if(this->fileStream.is_open())
      this->fileStream.close();
   fileStream.open(path);
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
   return this->isEnabled;
}

CLogger::~CLogger(){
   if(this->fileStream.is_open())
      this->fileStream.close();
}

std::ostream& CLogger::write(unsigned int level)
{
   if((isEnabled == ON &&
       level >= currentLogLevel) ||
       level == ERROR)
   {

      *logStream << "["
                 << toString(level)
                 << "]: ";

      return *logStream;
   }
   return fakeStream;
}

const char* CLogger::toString(const unsigned int level)
{
   static const char* const buffer[] = {"ERROR", "WARNING","MESSAGE"};
   return buffer[level];
}
