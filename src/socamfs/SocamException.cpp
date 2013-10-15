/* 
 * File:   SocamException.cpp
 * Author: glopez
 * 
 * Created on 26 de septiembre de 2012, 16:06
 */

#include <sstream>
#include <socamfs/SocamLogger.h>
#include <socamfs/SocamException.h>

namespace SOCAM{

/**
 * Socam Signal Handler Method
 * @param signl Signal recived
 */
void SocamException::signal_handler(int signl) {

    void *array[STACK_TRACE_SIZE];
    size_t size;
    char * str_signal=strsignal(signl);
    // get void*'s for all entries on the stack
    size = backtrace(array, STACK_TRACE_SIZE);

    // print out all the frames to stderr
    ostringstream oss;oss<<endl;
    oss<<endl<<"----------- SOCAM PANIC SIGNAL HANDLER ------------"<<endl;
    oss<<"Error Signal ["<<str_signal<<" -- "<<signl<<"]:"<<endl;
    char **buffer=backtrace_symbols(array, size);
    try {
        for (int i=0; i<size; i++)
            oss<<"\t"<<buffer[i]<<endl;
        
        oss<<endl;
    }
    catch(...){
        oss<<"CANNOT DISPALY MORE STACKTRACE!!"<<endl;
    }
    oss<<"\tKILLING SOCAM FILE SYSTEM... "<<endl;
    oss<<"---------------------------------------------------"<<endl;
    LOG_FATAL(oss.str());
    
    //the end.. :'(
    raise(SIGKILL);
}    
    
/**
 * Socam Exeption constructor
 * @param mms main message
 * @param what especific what message
 * @param error Error code
 * @param target Target
 */    
SocamException::SocamException(string mms, string what, int error, string target) throw() {
    this->smsg=mms;
    this->error_code=error;
    this->target=target;
    this->what=what;
    this->backtrace_pointer_=NULL;
    void *array[STACK_TRACE_SIZE];
    // get void*'s for all entries on the stack
    this->backtrace_size = backtrace(array, STACK_TRACE_SIZE);
    this->backtrace_pointer_=backtrace_symbols(array, this->backtrace_size);
}

/**
 * To String format
 * @return 
 */
string SocamException::toString() {
    ostringstream ostr;
    ostr<< "SOCAM EXCEPTION target=["<<target<<"] what=[" << what <<"]: code=["<<this->error_code<<"] "<<this->smsg;
//    ostr<< "\n\tSTACKTRACE:"<<endl<<this->strStackTrace();
    return ostr.str();
}

/**
 * Socam Exception Destructor
 * Release backtrace
 */
SocamException::~SocamException() throw() {
    if (backtrace_pointer_!=NULL) {
        free(backtrace_pointer_);
    }
}

/**
 * Set Error Code
 * @param error_code
 */
void SocamException::setError_code(int error_code) {
    this->error_code = error_code;
}

/**
 * Get Error Code
 * @return 
 */
int SocamException::getError_code() const {
    return error_code;
}

/**
 * Set Main Message
 * @param smsg
 */
void SocamException::setSmsg(string smsg) {
    this->smsg = smsg;
}

/**
 * Get Main Message
 * @return 
 */
string SocamException::getSmsg() const {
    return smsg;
}

/**
 * Set Target
 * @param target
 */
void SocamException::setTarget(string target) {
    this->target = target;
}

/**
 * Get Target
 * @return 
 */
string SocamException::getTarget() const {
    return target;
}

/**
 * Get Stack Trace Buffer (char**)
 * @return 
 */
char ** SocamException::getStackTrace() const {
    return this->backtrace_pointer_;
}

/**
 * Get String Stack Trace Buffer
 * @return 
 */
string SocamException::strStackTrace() const {
    ostringstream oss;
    for (int i=0;i<this->backtrace_size;i++) {
        oss<<"\t"<<backtrace_pointer_[i]<<endl;
    }
    return oss.str();
}




}
