#include "project.h"

QString Boxip, Boxname;
bool configsaved=false;
extern int maxup, maxdown;
extern QSettings *settings;
Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    string gw;
    GetDefaultGw(gw);
    if(Boxip.isEmpty())
    {
        if(!gw.empty())
        {
            Boxip =gw.data();
        }
    }
    /*     QMessageBox msgBox;
     msgBox.setText(gw.data());
     msgBox.exec();*/
    ui->setupUi(this);
    if(!Boxip.isEmpty())
    {
            ui->IPedit->setText(Boxip);
    }
    if(!Boxname.isEmpty())
    {
        ui->Boxname_label->setText(Boxname);
    }
    if(maxup!=0)
    {
        QString maxupstr;
        maxupstr.number(maxup);
        ui->Maxupedit->setText(maxupstr);
    }
    if(maxdown !=0)
    {
        QString maxdownstr;
        maxdownstr.number(maxdown);
        ui->maxdownedit->setText(maxdownstr);
    }
}

void Config::accept()
{

   QString addr = ui->IPedit->text();
    QHostAddress address(addr);
    if (QAbstractSocket::IPv4Protocol == address.protocol())
    {
       qDebug("Valid IPv4 address.");
       Boxip = addr;
       if(configsaved== false)
       {
           QMessageBox::StandardButton reply;
             reply = QMessageBox::question(this, "Config", "Values not saved, Quit?",
                                           QMessageBox::Yes|QMessageBox::No);
             if (reply == QMessageBox::Yes)
             {
               qDebug() << "Yes was clicked";
               this->close();
             }
             else
             {
               qDebug() << "Yes was *not* clicked";
             }
        }
       else
       {
         this->close();
       }

    }

    else
    {
        QMessageBox msgBox;
     msgBox.setText("Invalid Ip Address !");
        qDebug("Unknown or invalid address.");
    msgBox.exec();
    }

}



Config::~Config()
{
    delete ui;
}




void Config::on_button_test_clicked()
{
if(getboxinfo())
    {
    QMessageBox msgBox;
    msgBox.setText("getboxinfo failed !");
    qDebug("getboxinfo failed !");
    msgBox.exec();
    return;
    }
ui->Boxname_label->setText(Boxname);
ui->Maxupedit->setText(QString::number(maxup));
ui->maxdownedit->setText(QString::number(maxdown));
}



void Config::on_buttonsave_clicked()
{

settings->setValue("Boxip", ui->IPedit->text());
settings->setValue("Boxname",Boxname);
settings->setValue("maxup",ui->Maxupedit->text().toInt());
settings->setValue("maxdown",ui->maxdownedit->text().toInt());
configsaved = true;
}

