#include "TCPClient.h"

TCPClient::TCPClient()
    :m_recveDate(new char[64*1024])
    ,m_connectTimes(0)
{
    //初始化WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printf("WSAStartup error !");
		return;
	}

    m_sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(INVALID_SOCKET == m_sclient)
    {
        cout << "TCPClient Socket error " << strerror(errno) << endl;
        return;
    }

    m_serAddr.sin_family = AF_INET;
    m_serAddr.sin_port = htons(6666);
    m_serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    cout << "TCPClient Init Success" << endl;
}

TCPClient::~TCPClient()
{
    delete m_recveDate;
    closesocket(m_sclient);
}

bool TCPClient::Connect()
{
    bool ret = false;
    if (connect(m_sclient, (struct sockaddr *)&(m_serAddr), sizeof(m_serAddr)) != SOCKET_ERROR)
    {
        cout << "connect TCP server success" << endl;
        ret = true;
    }
    else
    {
        //cout << "connect TCP server fail" << endl;
    }
    m_connectTimes++;
    
    return ret;
}

void TCPClient::setConnectAddr(string addr)
{
    m_serAddr.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
}

void TCPClient::sendmsg(string msg)
{
    msg = "客户端发送的消息\n";
	send(m_sclient, msg.c_str(), msg.length(), 0);
}

char *TCPClient::recvmsg()
{
    int ret = recv(m_sclient, m_recveDate, 64*1024, 0);
    if (ret > 0)
    {
        return m_recveDate;
    }
    
    return NULL;	
}

int TCPClient::connectTimes()
{
    return m_connectTimes;
}

