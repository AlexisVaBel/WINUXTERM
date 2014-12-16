#include "serialdevlin.hpp"
#include <cstdlib>

#include <linux/usbdevice_fs.h>
#include <linux/serial.h>

#include <QDebug>

SeialDevLin::SeialDevLin(){

}

SeialDevLin::~SeialDevLin(){

}

int SeialDevLin::openDev(){
    closeDev();
    int fd=open(m_strDev.c_str(),O_RDWR|O_NOCTTY|O_NDELAY);
    m_iFD=fd;
    fd=isatty(fd);
    if(fd!=1){
        close(m_iFD);
        return -1;
    }
    return m_iFD;
}

void SeialDevLin::closeDev(){
    close(m_iFD);
}

void SeialDevLin::setDeviceToWork(string strDevName){
    m_strDev="/dev/"+strDevName;
    openDev();
    tcflush(m_iFD, TCIOFLUSH);
}

bool SeialDevLin::setDevParams(int iBaud, int iDataBits, int iStopBits, int iFlow){
    int iSucs=0;
    struct termios config;
    tcgetattr(m_iFD, &config);
    // clear old conf
    // used constants BXXX are in octadecimal view
    config.c_cflag&=~(CS5|CS6|CS7|CS8);
    config.c_cflag  |=  (CS8);
    config.c_cflag&=~(PARENB|PARODD);
    config.c_cflag&=~CSTOPB;
    // setting read write paramters
    config.c_lflag &=~OPOST;          // - не выполнять обработку вывода
    config.c_lflag  |=  CLOCAL;       // игнорировать строки состояния модема
    config.c_lflag  |=  CREAD;          //  разрешить прием
    config.c_lflag &=~ECHO;           // - запретить эхо-вывод введенных символов
    config.c_lflag &=~ECHOE;        //  запретить стирание последнего символа в строке
    // (Если разрешить и включен канонический режим, то производится стирание посл. символа)
    config.c_lflag &=~ISIG;              // - запретить генерацию сигналов, при приеме символов.
    config.c_lflag &=~ICANON;      // - октлючить канонический режим (теперь читаем по-символьно)
    config.c_cc[VMIN]=1;                // читаем минимум по 1 байту
    config.c_cc[VTIME]=1;             // время ожидания, после приема 1-го байта, если поставить 0 - то время ожидания неограниченно
    // clear old conf
    switch(iBaud){
    case 0:
    cfsetispeed(&config,B0);
    cfsetospeed(&config,B0);
    break;
    case 1200:
    cfsetispeed(&config,B1200);
    cfsetospeed(&config,B1200);
    break;
    case 1800:
    cfsetispeed(&config,B1800);
    cfsetospeed(&config,B1800);
    break;
    case 2400:
    cfsetispeed(&config,B2400);
    cfsetospeed(&config,B2400);
    break;
    case 4800:
    cfsetispeed(&config,B4800);
    cfsetospeed(&config,B4800);
    break;
    case 9600:
    cfsetispeed(&config,B9600);
    cfsetospeed(&config,B9600);
    break;
    case 19200:
    cfsetispeed(&config,B19200);
    cfsetospeed(&config,B19200);
    break;
    case 38400:
    cfsetispeed(&config,B38400);
    cfsetospeed(&config,B38400);
    break;
    case 57600:
    cfsetispeed(&config,B57600);
    cfsetospeed(&config,B57600);
    break;
    case 115200:
    cfsetispeed(&config,B115200);
    cfsetospeed(&config,B115200);
    break;
    }
    switch(iDataBits){
    case 5: config.c_cflag|=CS5; break;
    case 6: config.c_cflag|=CS6; break;
    case 7: config.c_cflag|=CS7; break;
    case 8: config.c_cflag|=CS8; break;
    };
    switch(iStopBits){
    case 2: config.c_cflag  |=  CSTOPB; break;
    }
    switch(iFlow){
    case 2:
        config.c_cflag  |=      PARENB;
        config.c_cflag  &=~  PARODD     ;break;    // even flow
    case 3: config.c_cflag  |=  PARODD|PARENB     ;break;    // odd flow
    }
    iSucs=tcsetattr(m_iFD,TCSANOW,&config);           // установка сейчас
    return (iSucs==0);
}

bool SeialDevLin::setDevParamsByName(string strDevName,int iBaud,int iDataBits,int iStopBits, int iFlow){
    setDeviceToWork(strDevName);
    if(openDev()==-1)return false;
    return setDevParams(iBaud, iDataBits, iStopBits,  iFlow);
}

SerialParams SeialDevLin::getDevParams(){
    SerialParams prm;
    prm.iBaudRate=9600;
    prm.iDataBits=8;
    prm.iStopBits=1;
    prm.iFlowCnt=0;
    return prm;
}

bool SeialDevLin::writeData(const char *chBuf, int iLng){
    tcflush(m_iFD, TCIOFLUSH);
//    qDebug()<<"Write "<<chBuf;
    int iRes=write(m_iFD,chBuf,iLng);
    return iRes>0;
}

bool SeialDevLin::readData(char *chBytes, int iCnt){
    int iRes=read(m_iFD,chBytes,iCnt);
//    qDebug()<<"Read "<<chBytes;
    return iRes>0;
}

bool SeialDevLin::isItCOMPort(string strFileName){
    bool bTerminal=false;
    int fd=open(strFileName.c_str(),O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd==-1){
        return bTerminal;
    }
    if(isatty(fd)){
        bTerminal=true;
    }
    close(fd);
    return bTerminal;
}

list<string> SeialDevLin::getComList(){
    list<string> lstComs;
//    termios getPortSettings, setPortSettings;
#ifdef Q_OS_LINUX
    qDebug()<<"Linux";
#endif
    char * chFileName;
    DIR *dirp=opendir(STR_DEV_DIR.c_str());
    struct dirent *dp;
    while ((dp=readdir(dirp))!=NULL){
        chFileName=dp->d_name;
        if(sizeof(chFileName)>3){
            if((chFileName[0]=='t')&&(chFileName[1]=='t')&&(chFileName[2]=='y')){
               if(isItCOMPort(STR_DEV_DIR+'/'+chFileName))
                lstComs.push_front(chFileName);
            }
        }
    }
    closedir(dirp);    
    return lstComs;
}


std::list<string> SeialDevLin::getDevInfo()
{
}
