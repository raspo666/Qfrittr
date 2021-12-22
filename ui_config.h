/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <ipaddress.h>

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *Maxupedit;
    QLineEdit *maxdownedit;
    QLabel *Boxname_label;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *buttonsave;
    QPushButton *button_test;
    QLineEdit *logfilename;
    QLabel *label_2;
    QCheckBox *logcheck;
    IPAddress *ipaddress;

    void setupUi(QDialog *Config)
    {
        if (Config->objectName().isEmpty())
            Config->setObjectName(QString::fromUtf8("Config"));
        Config->resize(294, 193);
        Config->setModal(true);
        buttonBox = new QDialogButtonBox(Config);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-270, 140, 491, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(Config);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 141, 16));
        Maxupedit = new QLineEdit(Config);
        Maxupedit->setObjectName(QString::fromUtf8("Maxupedit"));
        Maxupedit->setGeometry(QRect(180, 50, 71, 23));
        maxdownedit = new QLineEdit(Config);
        maxdownedit->setObjectName(QString::fromUtf8("maxdownedit"));
        maxdownedit->setGeometry(QRect(180, 90, 71, 23));
        Boxname_label = new QLabel(Config);
        Boxname_label->setObjectName(QString::fromUtf8("Boxname_label"));
        Boxname_label->setGeometry(QRect(180, 10, 111, 16));
        label_3 = new QLabel(Config);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(180, 30, 56, 15));
        label_4 = new QLabel(Config);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 70, 71, 21));
        buttonsave = new QPushButton(Config);
        buttonsave->setObjectName(QString::fromUtf8("buttonsave"));
        buttonsave->setGeometry(QRect(50, 90, 80, 23));
        button_test = new QPushButton(Config);
        button_test->setObjectName(QString::fromUtf8("button_test"));
        button_test->setGeometry(QRect(50, 60, 80, 23));
        logfilename = new QLineEdit(Config);
        logfilename->setObjectName(QString::fromUtf8("logfilename"));
        logfilename->setGeometry(QRect(147, 120, 141, 23));
        label_2 = new QLabel(Config);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(75, 121, 74, 20));
        logcheck = new QCheckBox(Config);
        logcheck->setObjectName(QString::fromUtf8("logcheck"));
        logcheck->setGeometry(QRect(10, 121, 85, 21));
        ipaddress = new IPAddress(Config);
        ipaddress->setObjectName(QString::fromUtf8("ipaddress"));
        ipaddress->setGeometry(QRect(21, 30, 141, 23));
        ipaddress->setCursor(QCursor(Qt::IBeamCursor));

        retranslateUi(Config);
        QObject::connect(buttonBox, SIGNAL(accepted()), Config, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Config, SLOT(reject()));

        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QDialog *Config)
    {
        Config->setWindowTitle(QCoreApplication::translate("Config", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Config", "FritzBox! IP Address", nullptr));
        Maxupedit->setPlaceholderText(QCoreApplication::translate("Config", "00000000", nullptr));
        maxdownedit->setPlaceholderText(QCoreApplication::translate("Config", "000000000", nullptr));
        Boxname_label->setText(QCoreApplication::translate("Config", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("Config", "MaxUp:", nullptr));
        label_4->setText(QCoreApplication::translate("Config", "MaxDown:", nullptr));
        buttonsave->setText(QCoreApplication::translate("Config", "Save values", nullptr));
        button_test->setText(QCoreApplication::translate("Config", "Test", nullptr));
        label_2->setText(QCoreApplication::translate("Config", "Logfilename", nullptr));
        logcheck->setText(QCoreApplication::translate("Config", "Logfile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
