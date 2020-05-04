/********************************************************************************
** Form generated from reading UI file 'XVideoUI.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XVIDEOUI_H
#define UI_XVIDEOUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "xvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_XVideoUIClass
{
public:
    QWidget *centralWidget;
    QPushButton *closeButton;
    XVideoWidget *src1video;
    QPushButton *openButton;
    QSlider *playSlider;

    void setupUi(QMainWindow *XVideoUIClass)
    {
        if (XVideoUIClass->objectName().isEmpty())
            XVideoUIClass->setObjectName(QString::fromUtf8("XVideoUIClass"));
        XVideoUIClass->resize(800, 600);
        XVideoUIClass->setStyleSheet(QString::fromUtf8("#XVideoUIClass\n"
"{\n"
"    background-color: rgb(60, 60, 60);\n"
"}\n"
"#closeButton\n"
"{\n"
"    font: 75 11pt \"\347\255\211\347\272\277\";\n"
"	color: rgb(255, 255, 255);\n"
"\n"
"\n"
"}"));
        centralWidget = new QWidget(XVideoUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(770, 0, 21, 23));
        closeButton->setStyleSheet(QString::fromUtf8(""));
        closeButton->setFlat(true);
        src1video = new XVideoWidget(centralWidget);
        src1video->setObjectName(QString::fromUtf8("src1video"));
        src1video->setGeometry(QRect(10, 10, 360, 260));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(380, 280, 75, 23));
        playSlider = new QSlider(centralWidget);
        playSlider->setObjectName(QString::fromUtf8("playSlider"));
        playSlider->setGeometry(QRect(10, 280, 361, 16));
        playSlider->setMaximum(999);
        playSlider->setOrientation(Qt::Horizontal);
        XVideoUIClass->setCentralWidget(centralWidget);

        retranslateUi(XVideoUIClass);
        QObject::connect(closeButton, SIGNAL(clicked()), XVideoUIClass, SLOT(close()));
        QObject::connect(openButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Open()));

        QMetaObject::connectSlotsByName(XVideoUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *XVideoUIClass)
    {
        XVideoUIClass->setWindowTitle(QCoreApplication::translate("XVideoUIClass", "XVideoUI", nullptr));
        closeButton->setText(QCoreApplication::translate("XVideoUIClass", "X", nullptr));
        openButton->setText(QCoreApplication::translate("XVideoUIClass", "\346\211\223\345\274\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XVideoUIClass: public Ui_XVideoUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XVIDEOUI_H
