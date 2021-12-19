#include "project.h"
#include "getgw.h"
#include "ipaddress.h"
QString Boxip, Boxname;
bool configsaved=false;
string logfilename;
FILE *logfile;
bool wantlog;
extern int maxup, maxdown;
extern QSettings *settings;

Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
/*IPAddress *ipaddress =new IPAddress();
ipaddress->setFixedHeight(23);
ipaddress->setFixedWidth(113);
ipaddress->setGeometry(40,30,113,23);
ipaddress->topLevelWidget();
ipaddress->show();
*/



    string gw;
      GetDefaultGw(gw);
      if(Boxip.isEmpty())
      {
          if(!gw.empty())
          {
              Boxip =gw.data();
              qDebug() << "boxipnow:" << Boxip;
          }
      }
      /*     QMessageBox msgBox;
       msgBox.setText(gw.data());
       msgBox.exec();*/


    ui->setupUi(this);



    if(!Boxip.isEmpty())
    {
        ui->ipaddress->setIP(Boxip);
            //ui->IPedit->setText(Boxip);
    }
    if(!Boxname.isEmpty())
    {
        ui->Boxname_label->setText(Boxname);
    }
    if(maxup!=0)
    {
        ui->Maxupedit->setText(QString::number(maxup));
    }
    if(maxdown !=0)
    {
        ui->maxdownedit->setText(QString::number(maxdown));
    }
    if(wantlog == true)
    {
        ui->logcheck->setChecked(true);
        ui->logfilename->setText(logfilename.data());
    }

}

void Config::accept()
{
    QString addr = ui->ipaddress->getIP(); ///ui->IPedit->text();
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
               on_buttonsave_clicked();
               QMessageBox msgBox;
               msgBox.setText("values saved anyway  :-) ");
               msgBox.exec();
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
           qDebug("IPaddress invalid !");

           QMessageBox msgBox;
           msgBox.setText("IPaddress invalid !");
           msgBox.exec();
         this->close();
    }

}


Config::~Config()
{
    delete ui;
}




void Config::on_button_test_clicked()
{

      QString addr = ui->ipaddress->getIP();
       QHostAddress address(addr);
       if (QAbstractSocket::IPv4Protocol == address.protocol())
       {
          qDebug("Valid IPv4 address.");
       }
       else
       {
              qDebug("ipaddress invalid !");

              QMessageBox msgBox;
              msgBox.setText("Not a valid IP Address!");
              msgBox.exec();
            //this->close();
       }


if(getboxinfo(addr))
    {
    QMessageBox msgBox;
    msgBox.setText("getboxinfo failed !");
    qDebug("getboxinfo failed !");
    msgBox.exec();
    return;
    }
else
    {
    Boxip = addr;
    ui->Boxname_label->setText(Boxname);
    ui->Maxupedit->setText(QString::number(maxup));
    ui->maxdownedit->setText(QString::number(maxdown));
    }
}


void Config::on_buttonsave_clicked()
{
QString addr;
addr = ui->ipaddress->getIP();

if(getboxinfo(addr))
    {
    qDebug("no valid response from Box !");

    QMessageBox msgBox;
    msgBox.setText("no valid response from Box !");
    msgBox.exec();
    return;
    }
else
    {
    Boxip = addr;
    settings->setValue("Boxip", addr);
    settings->setValue("Boxname",Boxname);
    settings->setValue("maxup",ui->Maxupedit->text().toInt());
    settings->setValue("maxdown",ui->maxdownedit->text().toInt());
    if(ui->logcheck->checkState() == Qt::Checked)
        {
        logfilename = ui->logfilename->text().toStdString();
        if(logfile != NULL)
            {
            fclose(logfile);
            }
    if((logfile = fopen(logfilename.data(),"a+")) == NULL)
        {
        QMessageBox msgBox;
        string msg = "cannot open ";
        msg.append(logfilename);
        msgBox.setText(msg.data());
        qDebug("logfilename.");
        msgBox.exec();
        }
    else
        {
        wantlog = false;
        settings->setValue("wantlog",wantlog);
        settings->setValue("logfilename",logfilename.data());
        }
}

}


configsaved = true;
}


void Config::on_logcheck_toggled(bool checked)
{
    return;

}

