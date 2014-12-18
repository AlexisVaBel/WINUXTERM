#include "viewcontroler.hpp"

#include <QDebug>

ViewControler::ViewControler(SerialDevBase *serial, ConsoleView *viewConsole, ControlView *viewControls) {
    m_serial=serial;
    m_viewConsole=viewConsole;
    m_viewControls=viewControls;
}

void ViewControler::connectToPort(QString strCom, SerialParams prm){
    m_serial->setDeviceToWork(strCom.toStdString());
    m_serial->setDevParamsGr(prm);
}

void ViewControler::startReadingPort(){

}

void ViewControler::sendToPort(){

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
