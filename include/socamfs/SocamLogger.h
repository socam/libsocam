/* 
 * File:   Logger.h
 * Author: Guillermo López González
 *
 * Created on 27 de septiembre de 2012
 * Copyright (c) 2013 FIDESOL
 */

#ifndef LOGGER_H
#define	LOGGER_H



#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

//If use SMARTPHONE COMPILATION VERSION MAKE USE_LOG4CXX = 0
#define USE_LOG4CXX            0 //Defines 1 if you want to use LOG4CXX Apache


//Apache includers
#if USE_LOG4CXX == 1 
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
using namespace log4cxx;
using namespace log4cxx::helpers;
#endif


using namespace std;


namespace SOCAM {

//Log error types
//------------------------------------------------------------------------------
#define LOGGER_OK       (int)0
#define LOGGER_FAILED   (int)-1
//------------------------------------------------------------------------------

//LOGGER LEVELS
//------------------------------------------------------------------------------    
#define L_TRACE         1
#define L_DEBUG         2    
#define L_INFO          3              
#define L_WARN          4  
#define L_ERROR         5 
#define L_FATAL         6  
//------------------------------------------------------------------------------



//Log name and log file config (for apache logger)
#define LOG_NAME        "SOCAM"
#define LOG_CONF        "/etc/socam/log.conf"


//STATIC CLASS: Socam Logger
class SocamLogger {
    public:
#if USE_LOG4CXX == 1
        //Singleton instance of logger (log4cxx apache)
        static log4cxx::LoggerPtr logger;
#endif
        /**
         Auxiliary log level
         */
        static int COUT_LOG_LEVEL;
        
        /**
        * Initialize the SocamLogger
        * @param name Logger name
        * @param pathConfig path of the configuration log file
        * @return 0
        */
        static int init_logger(string name, string pathConfig);
    
       
        /**
         * This dumps all the information in a struct stat.
         * @param level Level of log action
         * @param si
         */
        static void log_stat(int level,struct stat *si);
        /**
         * This dumps all the information in a struct statvfs.
         * @param level Level of log action
         * @param sv
         */
        static void log_statvfs(int level,struct statvfs *sv);
        /**
         * This dumps all the information in a struct utimbuf.
         * @param level Level of log action
         * @param buf
         */
        static void log_utime(int level,struct utimbuf *buf);

        
    private:
        /**
         * Destructor (empty)
         */
        virtual ~SocamLogger();
};


extern "C" {
#endif

/**
 * Get local time string
 * @return 
 */
char * gettime ();


#ifdef	__cplusplus
}


//SOCAM LOGGER MAIN MACROS
//-------------------------------------------------------------------------------------------------------
#if USE_LOG4CXX == 1
#define LOG_TRACE(expression) {LOG4CXX_TRACE(SocamLogger::logger, expression);}
#define LOG_DEBUG(expression) {LOG4CXX_DEBUG(SocamLogger::logger, expression);}
#define LOG_INFO(expression) {LOG4CXX_INFO(SocamLogger::logger, expression);}
#define LOG_WARN(expression) {LOG4CXX_WARN(SocamLogger::logger, expression);}
#define LOG_ERROR(expression) {LOG4CXX_ERROR(SocamLogger::logger, expression);}
#define LOG_FATAL(expression) {LOG4CXX_FATAL(SocamLogger::logger, expression);}
#else
#define LOG_TRACE(expression) {if (SocamLogger::COUT_LOG_LEVEL<=L_TRACE) cout << ">> TRACE -- " << expression <<endl;}
#define LOG_DEBUG(expression) {if (SocamLogger::COUT_LOG_LEVEL<=L_DEBUG) cout << ">> DEBUG -- " << expression <<endl;}
#define LOG_INFO(expression)  {if (SocamLogger::COUT_LOG_LEVEL<=L_INFO) cout << ">> INFO -- " << expression <<endl;}
#define LOG_WARN(expression)  {if (SocamLogger::COUT_LOG_LEVEL<=L_WARN) cout << ">> WARN -- " << expression <<endl;}
#define LOG_ERROR(expression) {if (SocamLogger::COUT_LOG_LEVEL<=L_ERROR) cout << ">> ERROR -- " << expression <<endl;}
#define LOG_FATAL(expression) {if (SocamLogger::COUT_LOG_LEVEL<=L_FATAL) cout << ">> FATAL -- " << expression <<endl;}
#endif
//--------------------------------------------------------------------------------------------------------
}

#endif	/* LOGGER_H */

