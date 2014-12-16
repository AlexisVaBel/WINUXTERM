#include "controlview.hpp"
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
}

ControlView::~ControlView(){
    //
}

void ControlView::connectToPort(){
    emit needToConnect( m_cmbCOM->currentText());
}

void ControlView::sendToPort(){
    emit needToSend();
}

void ControlView::readFrmPort(){
    emit needToRead();
}

void ControlView::loadCOMList(QStringList lst){
    m_cmbCOM->clear();
    m_cmbCOM->addItems(lst);
}

void ControlView::prepareView(){
    QGroupBox    *gboxCOM=new QGroupBox();
    QGroupBox    *gboxCRC =new QGroupBox();
    QGroupBox    *gboxCMD=new QGroupBox();
    QGroupBox    *gboxPRM=new QGroupBox();

    QVBoxLayout *ltMain =new QVBoxLayout();
    QGridLayout *ltCOM  =new QGridLayout();
    QGridLayout *ltCRC   =new QGridLayout();
    QGridLayout *ltCMD  =new QGridLayout();
    QGridLayout *ltPRM  =new QGridLayout();

    ltPRM->addWidget(m_btnMBUS   ,0 ,0 ,1 ,1);

    ltCOM->addWidget(m_cmbFlow,0,0,1,1);
    ltCOM->addWidget(m_cmbData,0,1,1,1);
    ltCOM->addWidget(m_cmbStop,0,2,1,1);
    ltCOM->addWidget(m_cmbSpeed,1,1,1,1);
    ltCOM->addWidget(m_cmbCOM,1,2,1,1);

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

    ltMain->addStretch();
    ltMain->addWidget(gboxPRM);
    ltMain->addWidget(gboxCOM);
    ltMain->addWidget(gboxCRC);
    ltMain->addWidget(gboxCMD);
//    ltMain->addLayout(ltCOM);
//    ltMain->addLayout(ltCRC);
//    ltMain->addLayout(ltCMD);
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

    m_cmbSpeed->addItem("9600");
    m_cmbStop->addItem("2");
    m_cmbData->addItem("DATA_8");
    m_cmbFlow->addItem("NONE");
    m_cmbCOM->addItem("COM1");

    m_btnMBUS    =new QPushButton("btn_MBUS");
    m_btnCon        =new QPushButton("btn_Con");
    m_btnSnd        =new QPushButton("btn_Snd");
    m_btnRcv        =new QPushButton("btn_Rcv");

    m_chkCRC32  =new QCheckBox("CRC32");
    m_chkCRC16  =new QCheckBox("CRC16");
    m_chkCRCMS=new QCheckBox("CRCMS");
    m_chkCR         =new QCheckBox("____CR");
    m_chkLF         =new QCheckBox("____LF");
}
