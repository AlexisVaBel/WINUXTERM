#include "serialworker.hpp"
#include "serialreader.hpp"
#include <QDebug>

SerialWorker::SerialWorker(){

}

void SerialWorker::setPort(SerialDevBase *port){
    m_port=port;
}

void SerialWorker::process(){
    m_bStopProcs=false;
    SerialReader *rdr=new SerialReader(m_port);    
    qDebug()<<"Starting";
    // cycle for process
    while(!m_bStopProcs){
       usleep(40);
       char* chByte;
       if (rdr->readByte(chByte,1))
           emit byteAvailable(chByte,1);
    }
    qDebug()<<"Stopping";
    emit finished();
}

void SerialWorker::stop(){
    m_bStopProcs=true;    
}
