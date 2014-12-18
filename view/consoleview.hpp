#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include <QString>
#include <QChar>
#include <QPlainTextEdit>
static const int MAX_IN_LINE=20;
enum  ENCODETYPE{
    ENC_HEX=0,
    ENC_ASCII,
    ENC_UTF
};

class ConsoleView : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ConsoleView(QWidget *parent = 0);
    ~ConsoleView();
    void      changeType(ENCODETYPE typeNew);
    void      clearOld();
public slots:
    void      putData(char *data, int iCnt);
signals:
    void      sendDataTo(const char *data);
protected:
    void    mousePressEvent(QMouseEvent *e);
    void    mouseDoubleClickEvent(QMouseEvent *e);
    void    keyPressEvent (QKeyEvent *e);
    void    contextMenuEvent(QContextMenuEvent *e);
private:
    int                       m_iRcvd;
    QChar                m_chSpacer;
    QString              m_strLine;
    ENCODETYPE m_encSetted;
};

#endif // CONSOLEVIEW_HPP
