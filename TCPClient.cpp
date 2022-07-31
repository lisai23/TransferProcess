#include "TCPClient.h"
#include "Message.pb.h"
#include "Common.h"
#include <thread>

void HeartBeat(SOCKET tcpserver)
{
    while (true)
    {
        Sleep(2000);
        protocol::DataInfo datainfo;
        datainfo.set_msgid(protocol::DataType::HeartBeat);
        protocol::File file;
        file.set_filename("HMI.png");
        file.set_size(2048);
        file.set_relativepath("/bin/cluster_HMI/截图");
        file.set_crcvalue(369);
        string info;
        file.SerializeToString(&info);
        datainfo.set_info(info.c_str());
        string msg;
        datainfo.SerializeToString(&msg);
        send(tcpserver, msg.c_str(), strlen(msg.c_str()), 0);
    }
}

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
        thread heart(HeartBeat,m_sclient);
        heart.detach();
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

