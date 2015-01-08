#ifndef SEIALDEVLIN_HPP
#define SEIALDEVLIN_HPP

#include "serialdevbase.hpp"
#ifdef Q_OS_WIN
#endif
//#ifdef Q_OS_LINUX
#include <dirent.h>
#include <unistd.h>                 // unix standard definitions
#include <sys/termios.h>        // POSIX terminal control definitions
#include <sys/fcntl.h>             // File control definitions
#include <sys/errno.h>           // Error number definitions
#include <sys/stropts.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/serial.h>
//#endif

using namespace std;

static  string STR_DEV_DIR="/dev";

class SeialDevLin: public SerialDevBase
{
public:
    SeialDevLin();
    ~SeialDevLin();
    void              closeDev();
    int                 setDeviceToWork(string strDevName);
    bool              setDevParams( int iBaud, int iDataBits, int iStopBits, int iFlow);
    bool              setDevParamsGr(SerialParams prm);
    bool              setDevParamsByName(string strDevName, int iBaud, int iDataBits, int iStopBits, int iFlow);

    list<string>    getComList();
    SerialParams getDevParams();
    list<string>    getDevInfo();

    bool              writeData(const char * chBuf, int iLng);
    bool              readData(char *chBytes, int iCnt);
private:
    string           m_strDev;
    int                 m_iFD;
    int                 openDev();
    bool              isItCOMPort(string strFileName);
};

#endif // SEIALDEVLIN_HPP
