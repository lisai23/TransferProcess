#include "TCPServer.h"
#include <thread>
//#include <mingw.thread.h>
#include <thread>

TCPServer::TCPServer(/* args */)
    :m_recveDate(new char[64*1024])
	,m_start(false)
{
    
}

TCPServer::~TCPServer()
{
    closesocket(m_slisten);
    closesocket(m_sClient);
    delete m_recveDate;
}

void TCPServer::Init()
{
	cout << "line: " << __LINE__ << " TCPServer Start Init" << endl;
	//初始化WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printf("WSAStartup error !");
		return;
	}

    //创建套接字
	m_slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return;
	}

    //绑定IP和端口
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(m_slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

    //开始监听
	if (listen(m_slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return;
	}
	//cout << "TCPServer Init Success" << endl;

    struct sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	m_sClient = accept(m_slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);

	cout << "line: " << __LINE__ << " TCPServer Init Success" << endl;
}

bool TCPServer::start()
{
	return m_start;
}

SOCKET &TCPServer::getClient()
{
	return m_sClient;
}

char *TCPServer::getRecveDate()
{
	return m_recveDate;
}

void TCPServer::InitData()
{
	m_share = Directory(sharepath);
}
