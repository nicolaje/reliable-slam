/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 7. Jan 20:01:36 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *ButtonStart;
    QDoubleSpinBox *EpsilonSpinBox;
    QLabel *label_Epsilon;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(659, 516);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ButtonStart = new QPushButton(centralWidget);
        ButtonStart->setObjectName(QString::fromUtf8("ButtonStart"));
        ButtonStart->setGeometry(QRect(400, 10, 75, 23));
        EpsilonSpinBox = new QDoubleSpinBox(centralWidget);
        EpsilonSpinBox->setObjectName(QString::fromUtf8("EpsilonSpinBox"));
        EpsilonSpinBox->setGeometry(QRect(220, 10, 71, 22));
        EpsilonSpinBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        EpsilonSpinBox->setDecimals(4);
        EpsilonSpinBox->setMinimum(0.01);
        EpsilonSpinBox->setMaximum(1);
        EpsilonSpinBox->setSingleStep(0.1);
        EpsilonSpinBox->setValue(0.1);
        label_Epsilon = new QLabel(centralWidget);
        label_Epsilon->setObjectName(QString::fromUtf8("label_Epsilon"));
        label_Epsilon->setGeometry(QRect(160, 10, 61, 21));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(140, 50, 400, 400));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 659, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        ButtonStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_Epsilon->setText(QApplication::translate("MainWindow", "Accuracy", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
