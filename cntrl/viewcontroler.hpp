#ifndef VIEWCONTROLER_HPP
#define VIEWCONTROLER_HPP

#include <QObject>
#include "./../view/consoleview.hpp"
#include "./../view/controlview.hpp"
#include "../serial/serialdevbase.hpp"
#include "./../cntrl/serialworker.hpp"

class ViewControler : public QObject
{
    Q_OBJECT
public:
    explicit ViewControler(SerialDevBase   *serial, ConsoleView     *viewConsole,  ControlView     *viewControls);

signals:

public slots:
    void                    gotByteFrmPort(char *chBuf,int iCnt);

    void                    gotCmdToConnect(QString strCom, SerialParams prm);
    void                    gotCmdToRead();

    void                    sendToPort(const char *data);
    void                    loadCOMList();

private:
    SerialDevBase   *m_serial;
    SerialWorker    *m_worker;
    ConsoleView     *m_viewConsole;
    ControlView     *m_viewControls;
    bool                    m_bConnected;
    bool                    m_bReading;

    void                    connectToPort(QString strCom, SerialParams prm);
    void                    disconnectFrmPort();
    void                    startReadingPort();
    void                    stopReadingPort();
};

#endif // VIEWCONTROLER_HPP
