#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <list>
#include <string>
#include <QMainWindow>
#include "consoleview.hpp"
#include "controlview.hpp"

#include "./../cmn/DataProvider.hpp"
#include "../serial/serialdevbase.hpp"
#include "./../cntrl/serialworker.hpp"

#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void                    connectToPort(QString strCom);
    void                    sendData(const char *data);
    void                    startReading();
public:
    void                    loadCOMList();
private:    
    ConsoleView     *m_console;
    ControlView     *m_controls;
    SerialDevBase  *m_serial;    
    SerialWorker    *m_worker;
    QLabel              *m_lblMain;
    void                    prepareView();
};

#endif // MAINWINDOW_HPP
