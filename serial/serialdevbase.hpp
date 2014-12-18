#ifndef SERIALDEVBASE_HPP
#define SERIALDEVBASE_HPP

#include <list>
#include <string>
#include "./SerialParams.hpp"
#include "./../cmn/DataProvider.hpp"

class SerialDevBase:public DataProvider{
public:
    virtual         std::list<std::string>   getComList()=0;
    virtual         void                                closeDev()=0;
    virtual         void                                setDeviceToWork(std::string strDevName)=0;
    virtual         bool                                setDevParams( int iBaud, int iDataBits, int iStopBits, int iFlow)=0;
    virtual         bool                                setDevParamsGr(SerialParams prm)=0;
    virtual         bool                                setDevParamsByName(std::string strDevName, int iBaud, int iDataBits, int iStopBits, int iFlow)=0;

    virtual         SerialParams                getDevParams()=0;
    virtual         std::list<std::string>   getDevInfo()=0;
};

#endif // SERIALDEVBASE_HPP
