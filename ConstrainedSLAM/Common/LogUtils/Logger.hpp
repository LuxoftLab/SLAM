#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "private/CLogger.hpp"

#define CVNAR_LOGGER_INIT                       CLogger& i = CLogger::getInstance();
#define CVNAR_LOGGER_SET(MODE)                  i.setMode(MODE);
#define CVNAR_LOGGER_OUTPUT(CONF_PARAM)         i.config(CONF_PARAM);
#define CVNAR_LOG_ERROR                         i.setDetalizationLevel(ERROR);
#define CVNAR_LOG_WARNING                       i.setDetalizationLevel(WARNING);
#define CVNAR_LOG_MESSAGE                       i.setDetalizationLevel(MESSAGE);
#define CVNAR_LOG(PRIORITY)                     if (PRIORITY < i.getLogLevel() || PRIORITY == ERROR) i.write(PRIORITY)

#endif // LOGGER_HPP

