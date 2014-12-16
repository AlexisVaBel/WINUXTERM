#include "serialreader.hpp"

SerialReader::SerialReader(SerialDevBase   *port):
m_port(port){

}

bool SerialReader::readByte(char *chBytes,int iCnt){
    return (m_port->readData(chBytes,iCnt));
}
