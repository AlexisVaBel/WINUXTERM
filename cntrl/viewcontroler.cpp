#include "viewcontroler.hpp"
#include <QThread>

#include <QDebug>

ViewControler::ViewControler(SerialDevBase *serial, ConsoleView *viewConsole, ControlView *viewControls) {
    m_serial=serial;
    m_bConnected=false;
    m_bReading      =false;
    m_viewConsole=viewConsole;
    m_viewControls=viewControls;
    connect(m_viewConsole,SIGNAL(sendDataTo(const char*)),this,SLOT(sendToPort(const char*)));
    connect(m_viewControls,SIGNAL(needCOMList()),this,SLOT(loadCOMList()));
    connect(m_viewControls,SIGNAL(needToConnect(QString,SerialParams)),this,SLOT(gotCmdToConnect(QString,SerialParams)));
    connect(m_viewControls,SIGNAL(needToRead()),this,SLOT(gotCmdToRead()));
}

void ViewControler::gotByteFrmPort(char *chBuf, int iCnt){
    m_viewConsole->putData(chBuf,iCnt);
}

void ViewControler::gotCmdToConnect(QString strCom, SerialParams prm){
    if(m_bConnected){
        disconnectFrmPort();
        return;
    }
    connectToPort(strCom,prm);
}

void ViewControler::connectToPort(QString strCom, SerialParams prm){
    qDebug()<<"trying to connect from cntrl "<<strCom;    
    if(m_serial->setDeviceToWork(strCom.toStdString())!=-1)m_bConnected=true;
    else return;
    m_serial->setDevParamsGr(prm);
    m_viewControls->disableControls();
}

void ViewControler::disconnectFrmPort(){
    qDebug()<<"trying to disconnect from cntrl ";
    m_bConnected=false;
    m_serial->closeDev();
    m_viewControls->enableControls();
}

void ViewControler::gotCmdToRead(){
    if((!m_bReading)&&(m_bConnected)) startReadingPort();
    else
    stopReadingPort();
}

void ViewControler::startReadingPort(){    
    m_bReading=true;
    m_viewControls->listeningPort();
    QThread *thr=new QThread;
    m_worker=new SerialWorker();
    m_worker->setPort(m_serial);
    m_worker->moveToThread(thr);
    connect(thr,SIGNAL(started()),m_worker,SLOT(process()));
    connect(m_worker,SIGNAL(finished()),thr,SLOT(quit()));
//    connect(m_worker,SIGNAL(byteAvailable(char *,int )),m_viewConsole,SLOT(putData(char *,int)));
    connect(m_worker,SIGNAL(byteAvailable(char *,int )),this,SLOT(gotByteFrmPort(char*,int)));
    thr->start();
}

void ViewControler::stopReadingPort(){
    m_viewControls->unListeningPort();
    if(m_bReading) m_worker->stop();
    m_bReading=false;
}

void ViewControler::sendToPort(const char *data){
    if(m_bConnected) m_serial->writeData(data,9);
}

void ViewControler::loadCOMList(){
    QStringList     lst;
     std::list<std::string>    lstCOMs;
    lstCOMs =m_serial->getComList();
    for(std::list<std::string>::iterator itGo=lstCOMs.begin();itGo!=lstCOMs.end();itGo++){
        lst.append(QString::fromAscii(itGo->c_str()));
    }
    m_viewControls->loadCOMList(lst);
}
