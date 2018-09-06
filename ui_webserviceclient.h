/********************************************************************************
** Form generated from reading UI file 'webserviceclient.ui'
**
** Created: Thu Sep 6 09:11:27 2018
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBSERVICECLIENT_H
#define UI_WEBSERVICECLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_WebServiceClient
{
public:

    void setupUi(QDialog *WebServiceClient)
    {
        if (WebServiceClient->objectName().isEmpty())
            WebServiceClient->setObjectName(QString::fromUtf8("WebServiceClient"));
        WebServiceClient->resize(400, 300);

        retranslateUi(WebServiceClient);

        QMetaObject::connectSlotsByName(WebServiceClient);
    } // setupUi

    void retranslateUi(QDialog *WebServiceClient)
    {
        WebServiceClient->setWindowTitle(QApplication::translate("WebServiceClient", "WebServiceClient", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WebServiceClient: public Ui_WebServiceClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBSERVICECLIENT_H
