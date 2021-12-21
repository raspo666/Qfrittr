/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2021 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 29.03.21                                             **
**          Version: 2.1.0                                                **
****************************************************************************/

#include "project.h"


using namespace std;

extern QString Boxip,Boxname;
QString dyntitle;
QString newtitle("Qfritter - ");

int maxup,maxdown,curup,curdown;
int scalemax;  //average downloadrate fort y scale

void
MainWindow::doconfig()
{
Config *getip = new Config;
getip->exec();
/*QMessageBox msgBox;
msgBox.setText("config done");
msgBox.exec();*/
}
void
MainWindow::doquit()
{
}




QSettings *settings;



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  mPlot(0),
  mTag1(0),
  mTag2(0)
{
  ui->setupUi(this);
#ifdef __linux__

  const char *homedir;

  if ((homedir = getenv("HOME")) == NULL) {
      homedir = getpwuid(getuid())->pw_dir;
  }
  QString configfile(homedir);
  configfile.append("/.config/Qfrittr.ini");
settings = new QSettings(configfile, QSettings::IniFormat);
#elif _WIN32
settings = new QSettings("RCS-S", "Qfrittr");
#else

#endif




//settings = new QSettings(configfile, QSettings::IniFormat);
settings->setValue("author", "Ralph Spitzner");
settings->setValue("web", "Spitzner.org");
settings->setValue("email","info@spitzner.org");
maxup = settings->value("maxup").toInt();
maxdown =settings->value("maxdown").toInt();
Boxname= settings->value("Boxname").toString();
scalemax= settings->value("scalemax").toInt();
Boxip =settings->value("Boxip").toString();
logfilename = settings->value("logfilename").toString().toStdString();
wantlog=settings->value("wantlog").toBool();
qDebug() << maxup <<"---" << maxdown;

if (scalemax ==0)
{
    scalemax=1000;
}
qDebug() << "scalemax" << scalemax ;

if(Boxip.isEmpty())
{
    doconfig();
}
newtitle.append(Boxname);
this->setWindowTitle(newtitle);
qDebug() << Boxip;
qDebug() << settings->fileName();




  mPlot = new QCustomPlot(this);
  setCentralWidget(mPlot);
  connect(ui->actionconfig,SIGNAL(triggered()),this,SLOT(doconfig()));
  connect(ui->actionconfig,SIGNAL(triggered()),this,SLOT(doquit()));
  // configure plot to have two right axes:
  mPlot->yAxis->setTickLabels(false);
  //connect(mPlot->yAxis2, SIGNAL(rangeChanged(QCPRange)), mPlot->yAxis, SLOT(setRange( 0.0,200.0)));//QCPRange))); // left axis only mirrors inner right axis
  mPlot->yAxis2->setVisible(true);
  mPlot->axisRect()->addAxis(QCPAxis::atRight);
  mPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
  mPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags
  mPlot->axisRect()->axis(QCPAxis::atRight,0)->setRange(0.0,scalemax/1000);
  mPlot->axisRect()->axis(QCPAxis::atRight,1)->setRange(0.0,scalemax/1000);
  // create graphs:
  mGraph1 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 0));
  mGraph2 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 1));
  mGraph1->setPen(QPen(QColor(10, 190, 60)));
  mGraph2->setPen(QPen(QColor(250, 30, 0)));
  mbrush1.setColor(QColor(0, 180, 60));
  mbrush2.setColor(QColor(250, 30, 0));

  mbrush1.setStyle((Qt::BrushStyle)5);
  mbrush2.setStyle((Qt::BrushStyle)5);


  mGraph1->setBrush(mbrush1);
  mGraph2->setBrush(mbrush2);
  // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
  mTag1 = new AxisTag(mGraph1->valueAxis());
  mTag1->setPen(mGraph1->pen());
  mTag2 = new AxisTag(mGraph2->valueAxis());
  mTag2->setPen(mGraph2->pen());

  connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
  mDataTimer.start(3000);
  if(wantlog == true)
    {
      if(logfile ==NULL)
      {
          if((logfile = fopen(logfilename.data(),"a+")) == NULL)
          {
          QMessageBox msgBox;
          string msg = "cannot open ";
          msg.append(logfilename);
          msgBox.setText(msg.data());
          qDebug("logfilename.");
          msgBox.exec();
          }
      }
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::timerSlot()
{
    char buffer[256];
    string suffup,suffdown,suffk="kbps",suffm="mbps";
    double dup,ddown;

    if(getupdown())
    {
        qDebug() << "getupdownfailed" ;

    }
  //qDebug() << "curup:" << curup << "curdown:" << curdown ;
  if (wantlog)
    {
      this->logline(curup,curdown);
    }
 dup = curup/(double)1000;
 suffup = suffdown = suffk;
 if(dup >1000.0)
 {
     dup = dup/100.0;
     suffup = suffm;
 }
 ddown = curdown/(double)1000;
 if(ddown >1000.0)
 {
     ddown = ddown/100.0;
     suffdown = suffm;
 }
sprintf(buffer," - up:%.3f %s down:%.3f %s",dup,suffup.data(),ddown,suffdown.data());
qDebug() << buffer;
dyntitle = newtitle;
dyntitle.append(buffer);
this->setWindowTitle(dyntitle);
if (curdown >=scalemax)
{
    scalemax =curdown;
}
// "rescale"
  mPlot->axisRect()->axis(QCPAxis::atRight,0)->setRange(0.0,scalemax/1000);
  mPlot->axisRect()->axis(QCPAxis::atRight,1)->setRange(0.0,scalemax/1000);


  // calculate and add a new data point to each graph:

  mGraph1->addData(mGraph1->dataCount(),curdown/(double)1000);
  mGraph1->setName("kbps");
//  mGraph1->addData(mGraph1->dataCount(), qSin(mGraph1->dataCount()/50.0)+qSin(mGraph1->dataCount()/50.0/0.3843)*0.25);
  mGraph2->addData(mGraph2->dataCount(),curup/(double)1000);

  //  mGraph2->addData(mGraph2->dataCount(), qCos(mGraph2->dataCount()/50.0)+qSin(mGraph2->dataCount()/50.0/0.4364)*0.15);

  // make key axis range scroll with the data:
  mPlot->xAxis->rescale();
  mGraph1->rescaleValueAxis(true, false);
  //mGraph2->rescaleValueAxis(true, false);
  mPlot->xAxis->setRange(mPlot->xAxis->range().upper, 400, Qt::AlignRight);
  
  // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
  double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
  double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
  mTag1->updatePosition(graph1Value);
  mTag2->updatePosition(graph2Value);
  mTag1->setText(QString::number(graph1Value, 'f', 2));
  mTag2->setText(QString::number(graph2Value, 'f', 2));
  
  mPlot->replot();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings->setValue("scalemax",scalemax);
    settings->setValue(Boxip,Boxip);
    settings->setValue(Boxname,Boxname);
    settings->setValue("maxup",maxup);
    settings->setValue("maxdown",maxdown);
    settings->setValue("logfilename",logfilename.data());
    settings->setValue("wantlog",wantlog);
    //settings->setValue("exit","yes");
    settings->sync();

}




void
MainWindow::logline(int up, int down)
{
    string date;
    QDateTime dtim ;
    uint tim;
    tim = time(0);
    date =  QDateTime::fromTime_t(tim).toString().toStdString();
    fprintf(logfile,"%s,%d,%d\n",date.data(),up,down);
    fflush(logfile);
}
