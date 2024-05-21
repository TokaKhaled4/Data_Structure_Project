/********************************************************************************
** Form generated from reading UI file 'demoqt.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOQT_H
#define UI_DEMOQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_demoqtClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *demoqtClass)
    {
        if (demoqtClass->objectName().isEmpty())
            demoqtClass->setObjectName("demoqtClass");
        demoqtClass->resize(1280, 698);
        demoqtClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(demoqtClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(650, 120, 49, 16));
        demoqtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(demoqtClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1280, 33));
        demoqtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(demoqtClass);
        mainToolBar->setObjectName("mainToolBar");
        demoqtClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(demoqtClass);
        statusBar->setObjectName("statusBar");
        demoqtClass->setStatusBar(statusBar);

        retranslateUi(demoqtClass);

        QMetaObject::connectSlotsByName(demoqtClass);
    } // setupUi

    void retranslateUi(QMainWindow *demoqtClass)
    {
        demoqtClass->setWindowTitle(QCoreApplication::translate("demoqtClass", "demoqt", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class demoqtClass: public Ui_demoqtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOQT_H
