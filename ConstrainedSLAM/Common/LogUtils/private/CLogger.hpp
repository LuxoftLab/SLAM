#ifndef CLOGGER_HPP
#define CLOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>

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

enum mode
{
   OFF,
   ON
};

class CLogger
{
public:
   static CLogger& getInstance();
   void config(const unsigned int configParam);
   void setDetalizationLevel(const unsigned int level);
   void setMode(const unsigned int mode);
   int getLogLevel();
   bool getMode();
   std::ostream& write(unsigned int level);
   ~CLogger();

private:
   CLogger();
   CLogger(CLogger const&);
   void operator = (CLogger const&);

   const std::string toString(const unsigned int level);
   std::ostream* logStream;
   unsigned int currentLogLevel;
   std::ofstream fileStream;
   bool isEnabled;

};

#endif // СLOGGER_HPP
