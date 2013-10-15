/* 
 * File:   SocamAccelerometerApi.h
 * Author: glopez
 *
 * Created on 21 de enero de 2013, 14:28
 */

#ifndef SOCAMACCELEROMETERAPI_H
#define	SOCAMACCELEROMETERAPI_H

#include <vector>
#include <stdio.h>
#include <map>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include "../SocamProfile.h"

 

#define ACCELEROMETER_FILE "/etc/socam/accelerometer"
 
namespace SOCAMAPI {

typedef enum type_coord_accelerometer {
    COORD_X=0,
    COORD_Y=1,
    COORD_Z=2        
} SocamAccelCoord;


typedef int coord_t;


class SocamAccelerometerApi {
public:
    SocamAccelerometerApi();
    bool isOnline();
    bool refreshCoord();
    coord_t getCoord(SocamAccelCoord coord);

    virtual ~SocamAccelerometerApi();
private:
    bool Online;
    
    coord_t AC_X;
    coord_t AC_Y;
    coord_t AC_Z;
};

}
#endif	/* SOCAMACCELEROMETERAPI_H */

