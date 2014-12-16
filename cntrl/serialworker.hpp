#ifndef SERIALWORKER_HPP
#define SERIALWORKER_HPP
#include <QObject>
#include "serial/serialdevbase.hpp"

class SerialWorker:public QObject
{
Q_OBJECT
public:
    SerialWorker();    
    void    setPort(SerialDevBase   *port);
signals:
    void    finished();
    void    byteAvailable(char *ch,int iCnt);
public slots:
    void    process();
    void    stop();
private:
    bool                     m_bStopProcs;
    SerialDevBase   *m_port;
};

#endif // SERIALWORKER_HPP
