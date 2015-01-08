#ifndef CONTROLVIEW_HPP
#define CONTROLVIEW_HPP

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QStringList>
#include "./../serial/SerialParams.hpp"

class ControlView : public QWidget
{
    Q_OBJECT
public:
    explicit ControlView(QWidget *parent = 0);
    ~ControlView();
signals:
    void              needToConnect(QString strCom, SerialParams prm);
    void              needToSend();
    void              needToRead();
    void              needCOMList();
public slots:
    void               connectToPort();
    void               sendToPort();
    void               readFrmPort();
    void               askCOMList();
    void               disableControls();
    void               enableControls();
    void               listeningPort();
    void               unListeningPort();
public:
    void                loadCOMList(QStringList lst);
    MsgType        getMsgType();
private:
    QTextEdit      *m_edtCmd;

    QPushButton *m_btnCon;
    QPushButton *m_btnSnd;
    QPushButton *m_btnRcv;
    QPushButton *m_btnGetCOMs;

    QComboBox *m_cmbFlow;
    QComboBox *m_cmbData;
    QComboBox *m_cmbStop;
    QComboBox *m_cmbSpeed;
    QComboBox *m_cmbCOM;

    QCheckBox   *m_chkCRC32;
    QCheckBox   *m_chkCRC16;
    QCheckBox   *m_chkCRCMS;
    QCheckBox   *m_chkCR;
    QCheckBox   *m_chkLF;

    QRadioButton *m_radioASCII;
    QRadioButton *m_radioUTF;
    QRadioButton *m_radioHEX;

    void                  prepareView();
    void                  prepareControls();
    void                  preparePortParams();

};

#endif // CONTROLVIEW_HPP
