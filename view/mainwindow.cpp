#include "mainwindow.hpp"
#include "serial/serialdevlin.hpp"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    prepareElements();
    prepareView();
    m_viewControl=new ViewControler(m_serial,m_console,m_controls);
}

void MainWindow::prepareView(){
    m_lblMain  =  new QLabel();
    QHBoxLayout *ltMain=new QHBoxLayout();
    ltMain->addWidget(m_console);
    ltMain->addWidget(m_controls);
    m_lblMain->setLayout(ltMain);
    setCentralWidget(m_lblMain);
    setMinimumSize(800,520);
}

void MainWindow::prepareElements(){
    m_controls        =  new ControlView();
    m_console         =  new ConsoleView ();
    m_serial            =  new SeialDevLin ();
}
