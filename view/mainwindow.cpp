#include "mainwindow.hpp"
#include "serial/serialdevlin.hpp"
#include <QHBoxLayout>
#include <QStringList>
#include <QThread>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    prepareView();
    loadCOMList();
    m_worker=new SerialWorker();
    connect(m_controls,SIGNAL(needToConnect(QString)),this,SLOT(connectToPort(QString)));
    connect(m_console,SIGNAL(sendDataTo(const char*)),this,SLOT(sendData(const char*)));
    connect(m_controls,SIGNAL(needToSend()),this,SLOT(startReading()));
}

void MainWindow::connectToPort(QString strCom) {
    qDebug()<<"trying "<<strCom;
    m_serial->setDeviceToWork(strCom.toStdString());
    m_serial->setDevParams(9600,8,1,0);
    m_worker->stop();
}

void MainWindow::sendData(const char *data){
    m_serial->writeData(data,9);
}

void MainWindow::startReading(){
    QThread *thr=new QThread;
    m_worker=new SerialWorker();
    m_worker->setPort(m_serial);
    m_worker->moveToThread(thr);
    connect(thr,SIGNAL(started()),m_worker,SLOT(process()));
    connect(m_worker,SIGNAL(finished()),thr,SLOT(quit()));
    connect(m_worker,SIGNAL(byteAvailable(char *,int )),m_console,SLOT(putData(char *,int)));
    thr->start();
}

void MainWindow::loadCOMList(){
    QStringList     lst;
     list<string>    lstCOMs;
    lstCOMs =m_serial->getComList();
    for(list<string>::iterator itGo=lstCOMs.begin();itGo!=lstCOMs.end();itGo++){
        lst.append(QString::fromAscii(itGo->c_str()));
    }
    m_controls->loadCOMList(lst);
}

void MainWindow::prepareView(){
    m_lblMain  =  new QLabel();
    m_controls  =  new ControlView();
    m_console   =  new ConsoleView ();
    m_serial      =  new SeialDevLin ();
    QHBoxLayout *ltMain=new QHBoxLayout();
    ltMain->addWidget(m_console);
    ltMain->addWidget(m_controls);
    m_lblMain->setLayout(ltMain);

    setCentralWidget(m_lblMain);
    setMinimumSize(800,520);
}
