
/*************************************************************************
 * Copyright 2021 Ralph Spitzner (rasp@spitzner.org)
 *
 * This file is part of Qfrittr - Qt FRitzbox traffic monitot.
 *
 * Qfrittr is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Qfrittr  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Qfrittr.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

#ifndef SOCKET_H
#define SOCKET_H
//#include <QString>
#include <iostream>
#include <string>
#include <QTcpSocket>
#include <QObject>
#include <QString>
 using namespace std ;

#define SOAP "<?xml version=\"1.0\" encoding=\"utf-8\" ?>    <s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">        <s:Body>            <u:GetCommonLinkProperties xmlns:u=\"urn:schemas-upnp-org:service:WANCommonInterfaceConfig:1\" />        </s:Body>    </s:Envelope>\n"

// GET 49000/tr64desc.xml ---> look for <modelName>FRITZ!Box 7490</modelName> in resp


//sactio maxspeed urlhttp://10.0.68.254:49000/igdupnp/control/WANCommonIFC1"
//sactio  ""   action     WANCommonInterfaceConfig:1#GetCommonLinkProperties
// saction curspeed       WANCommonInterfaceConfig:1#GetAddonInfos
typedef struct head {
string host    { "Host: " };
string uagent  { "User-Agent: Rallereq0.0\n"}; //finalstring
string acc     { "Accept: */* \n"};
string conn    { "Connection: Close\n"};       //ditto
string cotype  { "Content-Type: text/xml; charset=utf-8\n"};
string soa {"SoapAction:urn:schemas-upnp-org:service:"};
string clen {"Content-Length: 324 \n"};  //324 len of SOAP
} header;

int getboxinfo(QString ip);
int getupdown();

#define MAXS "WANCommonInterfaceConfig:1#GetCommonLinkProperties"
#define CURS "WANCommonInterfaceConfig:1#GetAddonInfos"




#endif // SOCKET_H
