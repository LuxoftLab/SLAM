#ifndef C_PROFILE_MANAGER_H
#define C_PROFILE_MANAGER_H

#include <map>
#include <string>

#include <boost/chrono.hpp>

class CProfileManager {
public:
   typedef boost::chrono::microseconds tTimeAccuracy;
   typedef tTimeAccuracy::rep tTime;

private:
   struct Info {
      const std::string mFunction;
      tTime mCallsNum;
      tTime mAverageTime;
      tTime mMaxTime;
      tTime mMinTime;

      Info(const std::string & function, const tTime time);
   };

   std::map<const std::string, Info> mProfiles;

   CProfileManager();
   CProfileManager(const CProfileManager & copy);
   ~CProfileManager();
   const CProfileManager & operator=(const CProfileManager & op);

public:
   static CProfileManager & getInstance();

   void addResult(const std::string & id, const std::string & function,
                  const tTime time);
};

#endif
