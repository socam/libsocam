/* 
 * File:   SocamException.h
 * Author: glopez
 *
 * Created on 26 de septiembre de 2012, 16:06
 * Copyright (c) 2013 FIDESOL
 */

#ifndef SOCAMEXCEPTION_H
#define	SOCAMEXCEPTION_H

#include <iostream>
#include <ostream>
#include <string>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

namespace SOCAM {

    /*
     MAX DEFAULT STACKTRACE
     */
    #ifndef STACK_TRACE_SIZE
    #define STACK_TRACE_SIZE        32
    #endif    

    /**
     CLASS: SocamException -> std::exception (base)
     */
    class SocamException : std::exception {
    public:
        
        /**
         * Socam Signal Handler Method
         * @param signl Signal recived
         */
        static void signal_handler(int signl);   

        /**
         * Socam Exeption constructor
         * @param mms main message
         * @param what especific what message
         * @param error Error code
         * @param target Target method
         */    
        SocamException(string mms, string what, int error, string target) throw();

        /**
         * To String format
         * @return String exception
         */
        string toString();

        /**
         * Socam Exception Destructor
         * Release backtrace
         */
        ~SocamException() throw();

        /**
         * Set Error Code
         * @param error_code
         */
        void setError_code(int error_code);

        /**
         * Get Error Code
         * @return 
         */
        int getError_code() const;

        /**
         * Set Main Message
         * @param smsg
         */
        void setSmsg(string smsg);

        /**
         * Get Main Message
         * @return 
         */
        string getSmsg() const;

        /**
         * Set Target
         * @param target
         */
        void setTarget(string target);

        /**
         * Get Target
         * @return 
         */
        string getTarget() const;

        /**
         * Get Stack Trace Buffer (char**)
         * @return char** stack trace
         */
        char ** getStackTrace() const;

        /**
         * Get String Stack Trace Buffer
         * @return string stacktrace
         */
        string strStackTrace() const;

    private:
        /*
         Target Method
         */
        string target;
        /*
         Main message
         */
        string smsg;
        /*
         Exception message
         */
        string what;
        /*
         Error code
         */
        int error_code;
        
        /*
         Backtrace size symbols
         */
        size_t backtrace_size;
        /*
         Backtrace array
         */
        char ** backtrace_pointer_;
    };
}
#endif	/* SOCAMEXCEPTION_H */

