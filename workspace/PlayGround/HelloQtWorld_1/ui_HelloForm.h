/********************************************************************************
** Form generated from reading UI file 'HelloForm.ui'
**
** Created: Sun Apr 7 22:38:18 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOFORM_H
#define UI_HELLOFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_HelloForm
{
public:
    QLineEdit *nameEdit;
    QLabel *label;
    QLineEdit *helloEdit;

    void setupUi(QDialog *HelloForm)
    {
        if (HelloForm->objectName().isEmpty())
            HelloForm->setObjectName(QString::fromUtf8("HelloForm"));
        HelloForm->resize(402, 142);
        nameEdit = new QLineEdit(HelloForm);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setGeometry(QRect(22, 47, 361, 31));
        label = new QLabel(HelloForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 361, 18));
        helloEdit = new QLineEdit(HelloForm);
        helloEdit->setObjectName(QString::fromUtf8("helloEdit"));
        helloEdit->setEnabled(true);
        helloEdit->setGeometry(QRect(22, 90, 361, 31));
        helloEdit->setFrame(false);
        helloEdit->setReadOnly(true);

        retranslateUi(HelloForm);

        QMetaObject::connectSlotsByName(HelloForm);
    } // setupUi

    void retranslateUi(QDialog *HelloForm)
    {
        HelloForm->setWindowTitle(QApplication::translate("HelloForm", "Hello Qt World", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("HelloForm", "Enter your name below", 0, QApplication::UnicodeUTF8));
        helloEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HelloForm: public Ui_HelloForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOFORM_H
