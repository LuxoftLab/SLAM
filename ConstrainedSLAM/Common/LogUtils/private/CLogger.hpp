#ifndef CLOGGER_HPP
#define CLOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>

#define OFF 0
#define ON 1

enum logLevel
{
   ERROR,
   WARNING,
   MESSAGE
};

enum output
{
   TO_CONSOLE,
   TO_FILE
};

class CLogger
{
public:
   static CLogger& getInstance();
   void setOutput(const unsigned int configParam);
   void setDetalizationLevel(const unsigned int level);
   void setMode(const unsigned int mode);
   void setLogFilePath(const std::string path);
   int getLogLevel();
   bool getMode();
   std::ostream& write(unsigned int level);
   ~CLogger();

private:
   CLogger();
   CLogger(CLogger const&);
   void operator = (CLogger const&);

   std::ostream fakeStream;
   std::ostream* logStream;
   std::ofstream fileStream;
   std::string filePath;
   const char* toString(const unsigned int level);
   unsigned int currentLogLevel;
   bool isEnabled;

};

#endif // СLOGGER_HPP
