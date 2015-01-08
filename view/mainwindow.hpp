#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include <QMainWindow>
#include "consoleview.hpp"
#include "controlview.hpp"

#include "./../cmn/DataProvider.hpp"
#include "../serial/serialdevbase.hpp"
#include "./../cntrl/serialworker.hpp"
#include "./../cntrl/viewcontroler.hpp"

#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:    
private:    
    ConsoleView     *m_console;
    ControlView     *m_controls;
    ViewControler *m_viewControl;
    SerialDevBase  *m_serial;        
    QLabel              *m_lblMain;
    void                    prepareView();
    void                    prepareElements();
};

#endif // MAINWINDOW_HPP
