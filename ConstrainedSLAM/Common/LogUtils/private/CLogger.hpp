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
    OFF,
    TO_CONSOLE,
    TO_FILE
};

class CLogger
{
public:
   static CLogger& getInstance();
   void config(const unsigned int configParam);
   void setDetalizationLevel(const unsigned int level);
   void log(const unsigned int level, const std::string& message);
   void log(const unsigned int level, const int message);
   void log(const unsigned int level, const long long message);
   void log(const unsigned int level, const float message);
   void log(const unsigned int level, const double message);
   ~CLogger();

private:
   CLogger();
   CLogger(CLogger const&);
   void operator = (CLogger const&);

   std::ostream* logStream;
   std::ofstream fileStream;
   unsigned int currentLogLevel;
   const std::string toString(const unsigned int level);

};

#endif // СLOGGER_HPP
