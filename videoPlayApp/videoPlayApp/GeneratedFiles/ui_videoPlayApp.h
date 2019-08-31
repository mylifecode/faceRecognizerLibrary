/********************************************************************************
** Form generated from reading UI file 'videoPlayApp.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYAPP_H
#define UI_VIDEOPLAYAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_videoPlayAppClass
{
public:

    void setupUi(QWidget *videoPlayAppClass)
    {
        if (videoPlayAppClass->objectName().isEmpty())
            videoPlayAppClass->setObjectName(QStringLiteral("videoPlayAppClass"));
        videoPlayAppClass->resize(600, 400);

        retranslateUi(videoPlayAppClass);

        QMetaObject::connectSlotsByName(videoPlayAppClass);
    } // setupUi

    void retranslateUi(QWidget *videoPlayAppClass)
    {
        videoPlayAppClass->setWindowTitle(QApplication::translate("videoPlayAppClass", "videoPlayApp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class videoPlayAppClass: public Ui_videoPlayAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYAPP_H
