#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "private/CLogger.hpp"

/*
 * Initializes logger with output to console by default
*/
#define CVNAR_LOGGER_INIT    CLogger& loggerInstance = CLogger::getInstance()

/*
 * Enables logger
*/
#define CVNAR_LOGGER_ON    loggerInstance.setMode(ON)

/*
 * Disables logger
*/
#define CVNAR_LOGGER_OFF    loggerInstance.setMode(OFF)

/*
 * Changes log output
 * parameters: TO_CONSOLE, TO_FILE
*/
#define CVNAR_LOGGER_OUTPUT(CONF_PARAM)    loggerInstance.setOutput(CONF_PARAM)

/*
 * Changes path to log file
 * parameters: const std::string with path
*/
#define CVNAR_LOG_PATH(PATH)    loggerInstance.setLogFilePath(PATH)

/*
 * Setting log level to given
 * (only errors will be written)
*/
#define CVNAR_LOG_LEVEL(LEVEL)    loggerInstance.setDetalizationLevel(LEVEL)

/*
 * Writes log message with given priority to the current output
 * parameters: ERROR, MESSAGE, WARNING
*/
#define CVNAR_LOG(PRIORITY)    loggerInstance.write(PRIORITY)

#endif // LOGGER_HPP

