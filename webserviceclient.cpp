#include "webserviceclient.h"
#include "ui_webserviceclient.h"
#include "qtsoap.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTime>

extern QString g_sMinTime,g_sMaxTime;

//QString MyMemthod[] = {"getIdentify","getIdentifyInfo","getShipIdAndNameInfo","getCounty","getTown","getVillage","getBase","getTask","getTaskType","getAllMember","getShipInfo"};
QString MyMemthod[] = {"getIdentify","getIdentifyInfo","getShipIdAndNameInfo","getCounty","getTown","getVillage","getBase","getTask","getTaskType","getShipInfo"};

void MySleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

WebServiceClient::WebServiceClient(QWidget *parent/*, Qt::WFlags flags*/) :
    QDialog(parent/*, flags*/),ui(new Ui::WebServiceClient),m_name("")
{
    //获取所有成员
    m_pGetAllMember = new QPushButton(tr("getAllMember"),this);
    connect(m_pGetAllMember,SIGNAL(clicked()),this,SLOT(GetAllMemberSlot()));
	m_pGetAllMember->setEnabled(false);
    //获取船舶信息
    m_pGetShipInfo = new QPushButton(tr("getShipInfo"),this);
    connect(m_pGetShipInfo,SIGNAL(clicked()),this,SLOT(GetShipInfoSlot()));
	m_pGetShipInfo->setEnabled(false);

    //获取船舶识别码（包括MMSI、北斗卡号等）
    m_pGetIdentify = new QPushButton(tr("getIdentify"),this);
    connect(m_pGetIdentify,SIGNAL(clicked()),this,SLOT(GetIdentifySlot()));
	m_pGetIdentify->setEnabled(false);

    //获取识别码名称及对应编号
    m_pGetIdentifyInfo = new QPushButton(tr("getIdentifyInfo"),this);
    connect(m_pGetIdentifyInfo,SIGNAL(clicked()),this,SLOT(GetIdentifyInfoSlot()));
	m_pGetIdentifyInfo->setEnabled(false);

    //获取船舶名称及对应编号信息
    m_pGetShipIdAndNameInfo = new QPushButton(tr("getShipIdAndNameInfo"),this);
    connect(m_pGetShipIdAndNameInfo,SIGNAL(clicked()),this,SLOT(GetShipIdAndNameInfoSlot()));
	m_pGetShipIdAndNameInfo->setEnabled(false);

    //获取县区
    //getCounty()
    m_pGetCounty = new QPushButton(tr("getCounty"),this);
    connect(m_pGetCounty,SIGNAL(clicked()),this,SLOT(GetCountySlot()));
	m_pGetCounty->setEnabled(false);
    //获取乡镇
    //getTown()
    m_pGetTown = new QPushButton(tr("getTown"),this);
    connect(m_pGetTown,SIGNAL(clicked()),this,SLOT(GetTownSlot()));
	m_pGetTown->setEnabled(false);

    //获取村社
    m_pGetVillage = new QPushButton(tr("getVillage"),this);
    connect(m_pGetVillage,SIGNAL(clicked()),this,SLOT(GetVillageSlot()));
	m_pGetVillage->setEnabled(false);

    //获取基础信息
    m_pGetBase = new QPushButton(tr("getBase"),this);
    connect(m_pGetBase,SIGNAL(clicked()),this,SLOT(GetBaseSlot()));
	m_pGetBase->setEnabled(false);

    //获取作业方式
    m_pGetTask = new QPushButton(tr("getTask"),this);
    connect(m_pGetTask,SIGNAL(clicked()),this,SLOT(GetTaskSlot()));
	m_pGetTask->setEnabled(false);

    //获取作业类型
    m_pGetTaskType = new QPushButton(tr("getTaskType"),this);
    connect(m_pGetTaskType,SIGNAL(clicked()),this,SLOT(GetTaskTypeSlot()));
	m_pGetTaskType->setEnabled(false);

    m_pHttp = new QtSoapHttpTransport;
    connect(m_pHttp,SIGNAL(responseReady( const QtSoapMessage & )),this,SLOT(ResponseSlot(const QtSoapMessage &)));
    
    m_pShowText = new QTextEdit;
    m_pShowText->setReadOnly(true);

    //Button控件布局
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addStretch();
    vlayout->addWidget(m_pGetAllMember);
    vlayout->addWidget(m_pGetShipInfo);
    vlayout->addWidget(m_pGetIdentify);
    vlayout->addWidget(m_pGetIdentifyInfo);
    vlayout->addWidget(m_pGetShipIdAndNameInfo);
    vlayout->addWidget(m_pGetCounty);
    vlayout->addWidget(m_pGetTown);
    vlayout->addWidget(m_pGetVillage);
    vlayout->addWidget(m_pGetBase);
    vlayout->addWidget(m_pGetTask);
    vlayout->addWidget(m_pGetTaskType);
    vlayout->addStretch();
    vlayout->setSpacing(10);

    //---3个控件整体布局
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addLayout(vlayout);
    hLayout->addWidget(m_pShowText);
    hLayout->setSpacing(10);
    hLayout->setContentsMargins(10, 2, 10, 2);

    //--显示布局
    setLayout(hLayout);

    this->setFixedSize(QSize(600,600));

	qDebug()<<"min Time"<<g_sMinTime.toInt()<<"max Time"<<g_sMaxTime.toInt();
    ui->setupUi(this);
}

WebServiceClient::~WebServiceClient()
{
    delete ui;
}

void WebServiceClient::ResponseSlot( const QtSoapMessage & response )
{
	/*
	if (!QString::compare(m_name,"getAllMember"))
	{
		return;
	}
    const QString FileName = m_name + ".xml";
    QFile filexml(FileName);
    if(!filexml.open(QFile::WriteOnly|QFile::Truncate))
    {
        qWarning("error:ParserXml ->writeXmlOPerator->file.open\n");
        return;
    }
    QTextStream ts(&filexml);
    ts.reset();
    ts.setCodec("UTF-8");
    QString xml = response.toXmlString();
	QString xmlStreamStr = response.toXmlStreamStr();
    QDomDocument doc;
    doc.setContent(xml);
    const QString sTagName = m_name + "Result";
    QDomNodeList nodeList =doc.elementsByTagName(sTagName);
    qDebug()<<"nodeList size:"<<nodeList.size();
    //QDomNodeList nodeList =doc.elementsByTagName("getTownResult");
    if(nodeList.size())
    {
        m_pShowText->clear();
        QDomNode resultNode =nodeList.at(0);
        QString result =resultNode.toElement().text();
        m_pShowText->append(result);
        doc.setContent(result);
        doc.save(ts,2,QDomNode::EncodingFromTextStream);
        //QMessageBox::information(NULL, "Title", "保存XML文件成功", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        const QString strTip = "保存" + FileName +"文件成功";
        QMessageBox::information(NULL, tr("提示信息"), strTip);
    }
    filexml.close();*/
	return;
}

 //获取所有成员
void WebServiceClient::GetAllMemberSlot()
{
    m_name = m_pGetAllMember->text();
    this->SubmitMessRes();
    return;
}

//获取船舶信息
void WebServiceClient::GetShipInfoSlot()
{
    m_name = m_pGetShipInfo->text();
    this->SubmitMessRes();
    return;
}

//获取船舶识别码（包括MMSI、北斗卡号等）
void WebServiceClient::GetIdentifySlot()
{
    m_name = m_pGetIdentify->text();
    this->SubmitMessRes();
    return;
}

//获取识别码名称及对应编号
void WebServiceClient::GetIdentifyInfoSlot()
{
    m_name = m_pGetIdentifyInfo->text();
    this->SubmitMessRes();
    return;
}

//获取船舶名称及对应编号信息
void  WebServiceClient::GetShipIdAndNameInfoSlot()
{
    m_name = m_pGetShipIdAndNameInfo->text();
    this->SubmitMessRes();
    return;
}

void WebServiceClient::GetTownSlot()
{
    m_name = m_pGetTown->text();
    this->SubmitMessRes();
    return;
}

void WebServiceClient::GetCountySlot()
{
    m_name = m_pGetCounty->text();
    this->SubmitMessRes();
    return;
}
//获取村社
void WebServiceClient::GetVillageSlot()
{
    m_name = m_pGetVillage->text();
    this->SubmitMessRes();
    return;
}

//获取基础信息
void WebServiceClient::GetBaseSlot()
{
    m_name = m_pGetBase->text();
    this->SubmitMessRes();
    return;
}

//获取作业方式
void WebServiceClient::GetTaskSlot()
{
    m_name = m_pGetTask->text();
    this->SubmitMessRes();
    return;
}

//获取作业类型
void WebServiceClient::GetTaskTypeSlot()
{
    m_name = m_pGetTaskType->text();
    this->SubmitMessRes();
    return;
}

void WebServiceClient::SubmitMessRes()
{
	QtSoapMessage message;
	message.setMethod(m_name,"http://tempuri.org/");
	const QString sAction = "http://tempuri.org/" + m_name;
	m_pHttp->setName(m_name);
	m_pHttp->setAction(sAction);
	m_pHttp->setHost("10.74.9.170",8089);
	QString xml = message.toXmlString();
	m_pHttp->submitRequest(message,"/ship/interface/shipInfoService.asmx");
	return;
}


void WebServiceClient::AutoReq()
{
    for(int i=0;i<sizeof(MyMemthod)/sizeof(MyMemthod[0]);i++)
    {
        m_name = MyMemthod[i];
        this->SubmitMessRes();
		if(!QString::compare(m_name,"getAllMember")|| !QString::compare(m_name,"getShipInfo"))
		{
			MySleep(g_sMaxTime.toInt()*1000);
		}
		else MySleep((g_sMinTime.toInt())*1000);
    }
	QMessageBox::information(NULL, "Title", "Download Completion!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
