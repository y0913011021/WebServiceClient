#ifndef WEBSERVICECLIENT_H
#define WEBSERVICECLIENT_H

#include <QDialog>
#include <QLineEdit>
#include "qtsoap.h"
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class WebServiceClient;
}

class WebServiceClient : public QDialog
{
    Q_OBJECT

public:
    explicit WebServiceClient(QWidget *parent = 0/*, Qt::WFlags flags = 0*/);
    ~WebServiceClient();
    void AutoReq();
private slots:

    //获取所有成员
    void            GetAllMemberSlot();
    //获取船舶信息
    void            GetShipInfoSlot();
    //获取船舶识别码（包括MMSI、北斗卡号等）
    void            GetIdentifySlot();
    //获取识别码名称及对应编号
    void            GetIdentifyInfoSlot();
    //获取船舶名称及对应编号信息
    void            GetShipIdAndNameInfoSlot();
    //获取县区
    void            GetCountySlot();
    //获取乡镇
    void            GetTownSlot();
    //获取村社
    void            GetVillageSlot();
    //获取基础信息
    void     GetBaseSlot();
    //获取作业方式
    void     GetTaskSlot();
    //获取作业类型
    void     GetTaskTypeSlot();
    //void Get_shipInfoSer_Slot();

    void ResponseSlot(const QtSoapMessage &response);

private:
	void					SubmitMessRes();
    Ui::WebServiceClient	*ui;

    //获取所有成员
    QPushButton				*m_pGetAllMember;

    //获取船舶信息
    QPushButton				*m_pGetShipInfo;
    //获取船舶识别码（包括MMSI、北斗卡号等）
    QPushButton				*m_pGetIdentify;
    //获取识别码名称及对应编号
    QPushButton				*m_pGetIdentifyInfo;

    //获取船舶名称及对应编号信息
    QPushButton				*m_pGetShipIdAndNameInfo;
    //获取县区
    QPushButton				*m_pGetCounty;
    //获取乡镇
    QPushButton				*m_pGetTown;
    //获取村社
    QPushButton				*m_pGetVillage;
    //获取基础信息
    QPushButton				*m_pGetBase;
    //获取作业方式
    QPushButton				*m_pGetTask;
    //获取作业类型
    QPushButton				*m_pGetTaskType;

    QtSoapHttpTransport		*m_pHttp;

    QTextEdit				*m_pShowText;

    QString					m_name;
	
};

#endif // WEBSERVICECLIENT_H
