#ifndef SERIALPARAMS_HPP
#define SERIALPARAMS_HPP
struct SerialParams{
    int iBaudRate;
    int iDataBits;
    int iStopBits;
    int iFlowCnt;
};

enum MsgType{typeNONE=0,typeASCII=1,typeUTF=2,typeHEX=3} ;
#endif // SERIALPARAMS_HPP
