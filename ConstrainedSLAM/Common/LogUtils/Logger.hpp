#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Private/CLogger.hpp"

#define CVNAR_LOGGER_INIT                       CLogger& i = CLogger::getInstance();
#define CVNAR_LOGGER_SET(MODE)                  i.setMode(MODE);
#define CVNAR_LOGGER_OUTPUT(CONF_PARAM)         i.config(CONF_PARAM);
#define CVNAR_LOG_ERROR                         i.setDetalizationLevel(ERROR);
#define CVNAR_LOG_WARNING                       i.setDetalizationLevel(WARNING);
#define CVNAR_LOG_MESSAGE                       i.setDetalizationLevel(MESSAGE);
#define CVNAR_LOG_WRITE(PRIORITY)               if ((PRIORITY > i.getLogLevel()) || (i.getMode() == OFF && PRIORITY != ERROR)) ; \
                                                else i.write(PRIORITY)
#endif // LOGGER_HPP

