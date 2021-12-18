
#include <QCoreApplication>
#include<iostream>
//#include "request.h"
#include "socket.h"
#include <QTextStream>
#include <QTcpSocket>
#include <QTcpServer>
#ifdef __linux__
#include <netinet/in.h>
#include <sys/socket.h>
#elif _WIN32
#include <WinSock.h>
#else

#endif
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>



using namespace std;


extern QString Boxname, Boxip;
extern int maxup, maxdown,curup,curdown;


 void readresult(QTcpSocket *socke, QByteArray *result)
 {
     if(result->length() > 0)
         result->clear();
     while(socke->waitForReadyRead())
     {
         result->append(socke->readAll());
     }
 }


 int getupdown()
 {
      QTcpSocket *socke;
      socke = new QTcpSocket;
      header myhead ;
      char buffer[256];
      QByteArray *result;
      result =new QByteArray;
      int soff1 =0 ,soff2 =0 ,len =0;
      myhead.host.append(Boxip.toStdString());
      myhead.host.append(":4900\n");


      socke->connectToHost(Boxip,49000);
      if(!socke->waitForConnected(3000))
      {
              return 1;
      }

      socke->write("POST /igdupnp/control/WANCommonIFC1 HTTP/1.1\n");
      socke->write(myhead.host.data());
      //qDebug() << myhead.host.data();
      socke->write(myhead.uagent.data());
      //qDebug() << myhead.uagent.data();
      socke->write(myhead.acc.data());
      socke->write(myhead.conn.data());
      socke->write(myhead.cotype.data());
      myhead.soa.append("WANCommonInterfaceConfig:1#GetAddonInfos\n");
      socke->write(myhead.soa.data());
      socke->write(myhead.clen.data());
      socke->write("\n\n");
      socke->flush();

      socke->write(SOAP);

      socke->flush();



      readresult(socke,result);

      soff1=result->indexOf("<NewByteSendRate>") + strlen("<NewByteSendRate>");
      soff2=result->indexOf("</NewByteSendRate>");
      if(soff1 == -1 || soff2 == -1)
      {
          return 1;
      }
      len= soff2 -soff1;

      memset(buffer,0,255);
      strncpy(buffer,result->data()+soff1,len);
      curup =atol(buffer);
      soff1=result->indexOf("<NewByteReceiveRate>") + strlen("<NewByteReceiveRate>");
      soff2=result->indexOf("</NewByteReceiveRate>");
      if(soff1 == -1 || soff2 == -1)
      {
          return 1;
      }

      memset(buffer,0,255);
      len= soff2 -soff1;

      strncpy(buffer,result->data()+soff1,len);

      curdown = atoi(buffer);


     return 0;
 }


int getboxinfo()
{
    QTcpSocket *socke;
    header myhead ;
    int soff1 =0 ,soff2 =0 ,len =0;
    QByteArray *result;
    char bname[256],buffer[256];

    socke = new QTcpSocket;
    result =new QByteArray;




    myhead.host.append(Boxip.toStdString());
    myhead.host.append(":4900\n");


    socke->connectToHost(Boxip,49000);
    if(!socke->waitForConnected(3000))
    {
            return 1;
    }
    socke->write("GET /tr64desc.xml HTTP/1.0\n");

    socke->write(myhead.host.data());
    //qDebug() << myhead.host.data();
    socke->write(myhead.uagent.data());
    socke->write(myhead.acc.data());
    socke->write(myhead.conn.data());
    socke->write(myhead.cotype.data());
    //socke->write(myhead.soa.data());   //select soap first *werk*
//    socke->write(myhead.clen.data());


    socke->write("\n\n");
    socke->flush();
    readresult(socke,result);
    //qDebug()  << "A:" << result->length() << "|"  << result->data() << endl;

    soff1=result->indexOf("<friendlyName>") + strlen("<friendlyName>");
    soff2=result->indexOf("</friendlyName>");
    if(soff1 == -1 || soff2 == -1)
    {
        return 1;
    }

    len= soff2 -soff1;
    strncpy(bname,result->data()+soff1,len);
    qDebug() << "BOXNAME:" << bname;
    Boxname =bname;
    socke->disconnectFromHost();
    socke->close();

    /// get up/down
    socke->connectToHost(Boxip,49000);
    if(!socke->waitForConnected(3000))
    {
            return 1;
    }


    socke->write("POST /igdupnp/control/WANCommonIFC1 HTTP/1.1\n");
    socke->write(myhead.host.data());
    socke->write(myhead.uagent.data());
    socke->write(myhead.acc.data());
    socke->write(myhead.conn.data());
    socke->write(myhead.cotype.data());
    myhead.soa.append("WANCommonInterfaceConfig:1#GetCommonLinkProperties\n");
    socke->write(myhead.soa.data());
    socke->write(myhead.clen.data());


    socke->write("\n\n");
    socke->flush();

    socke->write(SOAP);

    socke->flush();



    readresult(socke,result);

    //qDebug() << "A:" << result->length() << "|"  << result->data() << endl;

    soff1=result->indexOf("<NewLayer1UpstreamMaxBitRate>") + strlen("<NewLayer1UpstreamMaxBitRate>");
    soff2=result->indexOf("</NewLayer1UpstreamMaxBitRate>");
    len= soff2 -soff1;
    if(soff1 == -1 || soff2 == -1)
    {
        return 1;
    }

    memset(buffer,0,255);
    strncpy(buffer,result->data()+soff1,len);
    maxup =atol(buffer);
    soff1=result->indexOf("<NewLayer1DownstreamMaxBitRate>") + strlen("<NewLayer1DownstreamMaxBitRate>");
    soff2=result->indexOf("</NewLayer1DownstreamMaxBitRate>");
    if(soff1 == -1 || soff2 == -1)
    {
        return 1;
    }

    memset(buffer,0,255);
    len= soff2 -soff1;
    strncpy(buffer,result->data()+soff1,len);

    maxdown = atoi(buffer);
    qDebug() << "maxup:   " << maxup  <<endl << "maxdown: " << maxdown  ;
    socke->disconnectFromHost();
    socke->close();
    return 0;
}




