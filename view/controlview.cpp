#include "controlview.hpp"
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

ControlView::ControlView(QWidget *parent) :
    QWidget(parent){    
    prepareControls();
    prepareView();    
    connect(m_btnCon,SIGNAL(clicked()),SLOT(connectToPort()));
    connect(m_btnSnd,SIGNAL(clicked()),SLOT(sendToPort()));
    connect(m_btnRcv,SIGNAL(clicked()),SLOT(readFrmPort()));
    connect(m_btnGetCOMs,SIGNAL(clicked()),SLOT(askCOMList()));
}

ControlView::~ControlView(){
    //
}

void ControlView::connectToPort(){
    SerialParams prmSerial;
    prmSerial.iBaudRate=m_cmbSpeed->currentText().toInt(0,10);
    prmSerial.iDataBits  =m_cmbData->currentIndex()+5;
    prmSerial.iFlowCnt  =m_cmbFlow->currentIndex()+1;
    prmSerial.iStopBits  =m_cmbStop->currentIndex()+1;
    emit needToConnect( m_cmbCOM->currentText(),prmSerial);
}

void ControlView::sendToPort(){
    emit needToSend();
}

void ControlView::readFrmPort(){
    emit needToRead();
}

void ControlView::askCOMList(){
    emit needCOMList();
}


void ControlView::loadCOMList(QStringList lst){
    m_cmbCOM->clear();
    m_cmbCOM->addItems(lst);
}

MsgType ControlView::getMsgType(){
    if(m_radioASCII->isChecked())  return typeASCII;
    if(m_radioUTF->isChecked())     return typeUTF;
    if(m_radioHEX->isChecked())    return typeHEX;
    return typeNONE;
}

void ControlView::prepareView(){
    QGroupBox    *gboxCOM       =new QGroupBox();
    QGroupBox    *gboxCRC        =new QGroupBox();
    QGroupBox    *gboxCMD       =new QGroupBox();
    QGroupBox    *gboxPRM       =new QGroupBox();
    QGroupBox    *gbox_SndType=new QGroupBox();

    QVBoxLayout *ltMain =new QVBoxLayout();
    QGridLayout *ltCOM  =new QGridLayout();
    QGridLayout *ltCRC   =new QGridLayout();
    QGridLayout *ltCMD  =new QGridLayout();
    QGridLayout *ltPRM  =new QGridLayout();

    QLabel *lblPRM=new QLabel(QString("Send Params"));
    ltPRM->addWidget(lblPRM ,0 ,0 ,1 ,1);
    ltPRM->addWidget(m_radioASCII ,1 ,0 ,1 ,1);
    ltPRM->addWidget(m_radioUTF ,2 ,0 ,1 ,1);
    ltPRM->addWidget(m_radioHEX,3 ,0 ,1 ,1);

    ltCOM->addWidget(m_cmbFlow,0,0,1,1);
    ltCOM->addWidget(m_cmbData,0,1,1,1);
    ltCOM->addWidget(m_cmbStop,0,2,1,1);
    ltCOM->addWidget(m_cmbSpeed,1,0,1,1);
    ltCOM->addWidget(m_cmbCOM,1,1,1,1);
    ltCOM->addWidget(m_btnGetCOMs,1,2,1,1);

    ltCRC->addWidget(m_chkCRC32     ,0,0,1,1);
    ltCRC->addWidget(m_chkCRC16     ,0,1,1,1);
    ltCRC->addWidget(m_chkCRCMS   ,0,2,1,1);
    ltCRC->addWidget(m_chkCR   ,1,0,1,1);
    ltCRC->addWidget(m_chkLF    ,1,1,1,1);

    ltCMD->addWidget(m_edtCmd  ,0 ,0 ,1 ,4);
    ltCMD->addWidget(m_btnCon   ,1 ,0 ,1 ,1);
    ltCMD->addWidget(m_btnRcv   ,1 ,1 ,1 ,1);
    ltCMD->addWidget(m_btnSnd   ,1 ,3 ,1 ,1);

    gboxPRM->setLayout(ltPRM);
    gboxCOM->setLayout(ltCOM);
    gboxCRC->setLayout(ltCRC);
    gboxCMD->setLayout(ltCMD);

    ltMain->addWidget(gboxPRM);
    ltMain->addWidget(gboxCRC);
    ltMain->addStretch();
    ltMain->addWidget(gboxCOM);
    ltMain->addWidget(gboxCMD);

    setLayout(ltMain);
    setMinimumSize(QSize(240,480));
}

void ControlView::prepareControls(){
    m_edtCmd       =new QTextEdit();
    m_edtCmd->setFixedHeight(36);
    m_cmbFlow     =new QComboBox() ;
    m_cmbData     =new QComboBox() ;
    m_cmbStop     =new QComboBox() ;
    m_cmbSpeed   =new QComboBox() ;
    m_cmbCOM    =new QComboBox() ;
    preparePortParams();

    m_btnCon        =new QPushButton("Connect");
    m_btnSnd        =new QPushButton("Send");
    m_btnRcv        =new QPushButton("Receive");
    m_btnGetCOMs=new QPushButton("Get COM");
    m_btnRcv->setCheckable(true);

    m_chkCRC32  =new QCheckBox("CRC32");
    m_chkCRC16  =new QCheckBox("CRC16");
    m_chkCRCMS=new QCheckBox("CRCMS");
    m_chkCR         =new QCheckBox("____CR");
    m_chkLF         =new QCheckBox("____LF");

    m_radioASCII =new QRadioButton(tr("ASCII"));
    m_radioUTF    =new QRadioButton(tr(" UTF"));
    m_radioHEX  =new QRadioButton(tr(" HEX"));
}

void ControlView::preparePortParams(){
    m_cmbSpeed->addItem("9600");
    m_cmbSpeed->addItem("19200");
    m_cmbSpeed->addItem("38400");
    m_cmbSpeed->addItem("57600");
    m_cmbSpeed->addItem("115200");
    m_cmbStop->addItem("1");
    m_cmbStop->addItem("2");
    m_cmbData->addItem("DATA_5");
    m_cmbData->addItem("DATA_6");
    m_cmbData->addItem("DATA_7");
    m_cmbData->addItem("DATA_8");
    m_cmbFlow->addItem("NONE");
    m_cmbFlow->addItem("EVEN");
    m_cmbFlow->addItem("ODD");
//    m_cmbFlow->addItem("MARK");
//    m_cmbFlow->addItem("SPACE");
    m_cmbCOM->addItem("COM1");
}

void ControlView::disableControls(){
    m_cmbSpeed->setEnabled(false);
    m_cmbStop->setEnabled(false);
    m_cmbData->setEnabled(false);
    m_cmbFlow->setEnabled(false);
    m_cmbCOM->setEnabled(false);
    m_btnGetCOMs->setEnabled(false);
    m_btnCon->setText(tr("disconnect"));
}

void ControlView::enableControls(){
    m_cmbSpeed->setEnabled(true);
    m_cmbStop->setEnabled(true);
    m_cmbData->setEnabled(true);
    m_cmbFlow->setEnabled(true);
    m_cmbCOM->setEnabled(true);
    m_btnGetCOMs->setEnabled(true);
    m_btnCon->setText(tr("connect"));
}

void ControlView::listeningPort(){
    m_btnRcv->setText(tr("Receiving"));
    m_btnRcv->setChecked(true);
}

void ControlView::unListeningPort(){
    m_btnRcv->setText(tr("Receive"));
    m_btnRcv->setChecked(false);
}
