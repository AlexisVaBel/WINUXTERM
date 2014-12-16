#include "serialparams.h"
#include "termios.h"

SerialParams::SerialParams(){
    m_iBaudRate=B9600;
    m_iDataBits =CS8;                    // 8 data bits
    m_iStopBits  =CSTOPB;           // 2 stop bits, negate CSTOPB to set 1 stop bit
    m_iFlow        =PARENB;         // parity enable
}

SerialParams::~SerialParams(){

}
