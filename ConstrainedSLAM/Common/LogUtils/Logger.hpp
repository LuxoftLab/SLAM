#ifndef MAKROS_HPP
#define MAKROS_HPP

#include "private/CLogger.hpp"

#define CVNAR_LOGGER_START                      CLogger& i = CLogger::getInstance();
#define CVNAR_LOGGER_CONF(CONF_PARAM)           i.config(CONF_PARAM);
#define CVNAR_LOG_ERROR                         i.setDetalizationLevel(ERROR);
#define CVNAR_LOG_WARNING                       i.setDetalizationLevel(WARNING);
#define CVNAR_LOG_MESSAGE                       i.setDetalizationLevel(MESSAGE);
#define CVNAR_LOGGER_WRITE(PRIORITY, MESSAGE)   i.log(PRIORITY, MESSAGE);

#endif // MAKROS_HPP

