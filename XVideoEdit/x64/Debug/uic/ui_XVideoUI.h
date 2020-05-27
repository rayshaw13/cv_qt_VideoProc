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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
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
    QLabel *label;
    QLabel *label_2;
    QSpinBox *bright;
    QDoubleSpinBox *contrast;
    QPushButton *setButton;
    XVideoWidget *des;
    QPushButton *exportButton;

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
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(380, 320, 61, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 340, 61, 16));
        bright = new QSpinBox(centralWidget);
        bright->setObjectName(QString::fromUtf8("bright"));
        bright->setGeometry(QRect(450, 310, 42, 22));
        contrast = new QDoubleSpinBox(centralWidget);
        contrast->setObjectName(QString::fromUtf8("contrast"));
        contrast->setGeometry(QRect(450, 340, 62, 22));
        contrast->setMinimum(1.000000000000000);
        contrast->setMaximum(3.000000000000000);
        setButton = new QPushButton(centralWidget);
        setButton->setObjectName(QString::fromUtf8("setButton"));
        setButton->setGeometry(QRect(640, 320, 56, 17));
        des = new XVideoWidget(centralWidget);
        des->setObjectName(QString::fromUtf8("des"));
        des->setGeometry(QRect(380, 10, 360, 260));
        exportButton = new QPushButton(centralWidget);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setGeometry(QRect(470, 280, 75, 23));
        XVideoUIClass->setCentralWidget(centralWidget);

        retranslateUi(XVideoUIClass);
        QObject::connect(closeButton, SIGNAL(clicked()), XVideoUIClass, SLOT(close()));
        QObject::connect(openButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Open()));
        QObject::connect(playSlider, SIGNAL(sliderPressed()), XVideoUIClass, SLOT(SliderPress()));
        QObject::connect(playSlider, SIGNAL(sliderReleased()), XVideoUIClass, SLOT(SliderRelease()));
        QObject::connect(playSlider, SIGNAL(sliderMoved(int)), XVideoUIClass, SLOT(SetPos(int)));
        QObject::connect(setButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Set()));
        QObject::connect(exportButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Export()));

        QMetaObject::connectSlotsByName(XVideoUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *XVideoUIClass)
    {
        XVideoUIClass->setWindowTitle(QCoreApplication::translate("XVideoUIClass", "XVideoUI", nullptr));
        closeButton->setText(QCoreApplication::translate("XVideoUIClass", "X", nullptr));
        openButton->setText(QCoreApplication::translate("XVideoUIClass", "\346\211\223\345\274\200", nullptr));
        label->setText(QCoreApplication::translate("XVideoUIClass", "\344\272\256\345\272\2460-100", nullptr));
        label_2->setText(QCoreApplication::translate("XVideoUIClass", "\345\257\271\346\257\224\345\272\2461.0-3.0", nullptr));
        setButton->setText(QCoreApplication::translate("XVideoUIClass", "\350\256\276\347\275\256", nullptr));
        exportButton->setText(QCoreApplication::translate("XVideoUIClass", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XVideoUIClass: public Ui_XVideoUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XVIDEOUI_H
