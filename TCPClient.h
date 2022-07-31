#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#include <STDIO.H>
#include <iostream>
#include <iostream>

using namespace std;

class TCPClient
{
public:
    TCPClient(/* args */);
    ~TCPClient();
    bool Connect();
    void setConnectAddr(string addr);
    void sendmsg(string msg);
    char *recvmsg();
    int connectTimes();
private:
    SOCKET m_sclient;
    struct sockaddr_in m_serAddr;
    char *m_recveDate;
    int m_connectTimes;
};


