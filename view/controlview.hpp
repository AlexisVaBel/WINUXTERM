#ifndef CONTROLVIEW_HPP
#define CONTROLVIEW_HPP

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QStringList>

class ControlView : public QWidget
{
    Q_OBJECT
public:
    explicit ControlView(QWidget *parent = 0);
    ~ControlView();
signals:
    void              needToConnect(QString strCom);
    void              needToSend();
    void              needToRead();
public slots:
    void               connectToPort();
    void               sendToPort();
    void               readFrmPort();
public:
    void                loadCOMList(QStringList lst);
private:
    QTextEdit      *m_edtCmd;

    QPushButton *m_btnMBUS;
    QPushButton *m_btnCon;
    QPushButton *m_btnSnd;
    QPushButton *m_btnRcv;

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

    void                  prepareView();
    void                  prepareControls();
};

#endif // CONTROLVIEW_HPP
