/* 
 * File:   SocamFSSettings.h
 * Author: ramoncin
 *
 * Created on 26 de abril de 2013, 8:31
 */

#ifndef SOCAMFSSETTINGS_H
#define	SOCAMFSSETTINGS_H



#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "SocamPropertyStream.h"

using namespace SOCAM;

#define SOCAM_CONF "/etc/socam/socamfs.conf"

#define SOCAMFS_URL_SERVER              "URL-SERVER"
#define SOCAMFS_USER                    "USER"
#define SOCAMFS_PASSWORD                "PASSWORD"
#define SOCAMFS_PROFILE                 "PROFILE"
#define SOCAMFS_UPDATE_CATALOG_PERIOD   "UPDATE_CATALOG_PERIOD"
#define SOCAMFS_CLEAN_INTERVAL           "CLEAN_INTERVAL"
#define SOCAMFS_MIN_FREE_DISK           "MIN_FREE_DISK_ABORT_CLEAN_UP"
#define SOCAMFS_DEPENDENCY_THRESHOLD    "DEPENDENCY_THRESHOLD"
#define SOCAMFS_MAX_FILES_TO_PREDICT    "MAX_FILES_TO_PREDICT"
#define SOCAMFS_LOG_LEVEL               "LOG_LEVEL"
#define SOCAMFS_FILE_SYSTEM_SIZE        "FILE_SYSTEM_SIZE"



class SocamFSSettings {
    
public:
    SocamFSSettings();
    ~SocamFSSettings();
    
    string getValue(string name);
    void setValue(string name, string value);
    void save();
    
private:
    SocamPropertyStream* properties;
    
};


#endif	/* SOCAMFSSETTINGS_H */

