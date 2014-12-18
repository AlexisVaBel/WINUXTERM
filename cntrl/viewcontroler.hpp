#ifndef VIEWCONTROLER_HPP
#define VIEWCONTROLER_HPP

#include <QObject>
#include "./../view/consoleview.hpp"
#include "./../view/controlview.hpp"
#include "../serial/serialdevbase.hpp"

class ViewControler : public QObject
{
    Q_OBJECT
public:
    explicit ViewControler(SerialDevBase   *serial, ConsoleView     *viewConsole,  ControlView     *viewControls);

signals:

public slots:
    void                    connectToPort(QString strCom, SerialParams prm);
    void                    startReadingPort();
    void                    sendToPort();
    void                    loadCOMList();

private:
    SerialDevBase   *m_serial;
    ConsoleView     *m_viewConsole;
    ControlView     *m_viewControls;
};

#endif // VIEWCONTROLER_HPP
