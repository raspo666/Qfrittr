#ifndef PROJECT_H
#define PROJECT_H
#include "config.h"
#include "ui_config.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QHostAddress>
#include <QDialog>
#include <string>
#include "getgw.h"
#include <QSettings>
#include <QString>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#ifdef __linux__
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pwd.h>
#elif _WIN32
#include <winsock.h>
#include <iphlpapi.h>
#else

#endif

#include <cstring>
#include <QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include<QMessageBox>
#include <string>
#include "getgw.h"
#include <QSettings>
#include <QTcpSocket>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <io.h>
#else

#endif

#include <sys/types.h>
//#include <pwd.h>
#include "socket.h"
extern string logfilename;
extern bool wantlog;
extern FILE *logfile;





using namespace std;
#endif // PROJECT_H
