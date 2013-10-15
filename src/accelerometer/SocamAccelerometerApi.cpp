/* 
 * File:   SocamAccelerometerApi.cpp
 * Author: glopez
 * 
 * Created on 21 de enero de 2013, 14:28
 */

#include <accelerometer/SocamAccelerometerApi.h>


using namespace std;

namespace SOCAMAPI {

SocamAccelerometerApi::SocamAccelerometerApi() {
    cout << "SocamAccelerometerApi init()" << endl;
    this->AC_X=0;
    this->AC_Y=0;
    this->AC_Z=0;

#if PROFILE==SMART_PHONE
    FILE *fd;
    if (!(fd = fopen(ACCELEROMETER_FILE, "r"))) {
            cerr << "\t FAILED" << endl;
    } else {
        this->Online=true;
        this->refreshCoord();
    }

    cout << "SocamAccelerometerApi init() OK" << endl;
#else
    cout << "NO SMART_PHONE PROFILE >> ACCELEROMETER IS NOT SUPPORTED!"<<endl;
#endif
}


SocamAccelerometerApi::~SocamAccelerometerApi() {
    //do nothing
}

bool SocamAccelerometerApi::refreshCoord() {

#if PROFILE==SMART_PHONE
	int tmp[3] = {0, 0, 0};
        FILE *fd;
        printf(">>>Opening accelerometer port: %s..",ACCELEROMETER_FILE);
        if (!(fd = fopen(ACCELEROMETER_FILE, "r"))) {
            printf("\t FAILED\n");
            this->Online=false;
            return false;
        }
        printf("\tOK\n");
        
        printf(">>>Scaning coordinates (X,Y,Z)..");
        if (fscanf(fd, "(%d,%d,%d)", tmp, tmp+1, tmp+2) != 3) {
            this->Online=false;
            printf("\t FAILED\n");
            return false;
        }
        printf("\t OK [%d,%d,%d]\n",tmp[0],tmp[1],tmp[2]);
 
        this->AC_X = tmp[0];
        this->AC_Y = tmp[1];
        this->AC_Z = tmp[2];
        
        //printf(">>>Closing driver..");
        if (fclose(fd) == EOF) {
            //printf("\tFAILED\n");
            this->Online=false;
            return false;
        }
        //printf("\tOK\n");
 
        this->Online=true;
        return true;
#else
	this->Online=false;
	return false;
#endif
}


bool SocamAccelerometerApi::isOnline() {
    return this->Online;
}
    
int SocamAccelerometerApi::getCoord(SocamAccelCoord coord) 
{
    switch (coord) {
        case COORD_X: return this->AC_X;
        case COORD_Y: return this->AC_Y;
        case COORD_Z: return this->AC_Z;
    }
    return 0;
}

}



