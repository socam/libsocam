/* 
 * File:   SocamLogger.cpp
 * Author: glopez
 * 
 * Created on 5 de octubre de 2012, 14:34
 */

#include <fstream>

#include <socamfs/SocamLogger.h>
#if USE_LOG4CXX == 1
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/helpers/exception.h"

#define CONFIG_FILE     "socam-log.properties"
#endif

#ifdef	__cplusplus
extern "C" {
#endif


//#include "params.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef	__cplusplus
}
#endif
    


namespace SOCAM {

    //MAX LOG POSIX BUFFER DATA PER CALL
    #define MAX_LOG_BUFFER_DATA     4096

#if USE_LOG4CXX == 1
    /**
     A LOG4CXX GLOBAL POINTER
     */
    log4cxx::LoggerPtr  SocamLogger::logger=0;
#endif
    
    int SocamLogger::COUT_LOG_LEVEL=L_INFO;
    
    
    /**
     * Destructor
     */
    SocamLogger::~SocamLogger() { 
    }
    
    
    /**
     * Initialize the SocamLogger
     * @param name Logger name
     * @param pathConfig path of the configuration log file
     * @return 0
     */
    int SocamLogger::init_logger(std::string name, std::string pathConfig){
#if USE_LOG4CXX == 1
        PropertyConfigurator::configure(pathConfig.c_str());
        SocamLogger::logger = LoggerPtr(log4cxx::Logger::getLogger(name.c_str()));
        if (SocamLogger::logger==0)
            return LOGGER_FAILED;
        
        LOG_TRACE("******************************************************************")
        LOG_TRACE("       >>>>>>>>>>>>>> A NEW LOGGER INSTANCE <<<<<<<<<<<<<<<       ")
        LOG_TRACE("******************************************************************")  
#else
        cout << "******************************************************************"<<endl;
        cout << "       >>>>>>>>>>>>>> A NEW LOGGER INSTANCE <<<<<<<<<<<<<<<       "<<endl;
        cout << "******************************************************************"<<endl;
#endif
        return LOGGER_OK;
    }
 
    
    
}

char * gettime ()
{
    time_t rawtime;

    time ( &rawtime );
    return ctime (&rawtime);
}
