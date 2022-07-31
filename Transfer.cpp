#include "Transfer.h"
#include <memory.h>
//#include<pthread.h>

pthread_mutex_t g_mutex;

void ServerManager(TCPServer *server)
{
    pthread_mutex_lock(&g_mutex);
    cout << "servermanager start" << endl;
    server->InitData();
    server->Init();
    cout << "client connect success" << endl;
    SOCKET sClient = server->getClient();
    char *recveData = server->getRecveDate();

    while(true)
    {
        memset(recveData,0,64*1024);
        //接收数据
		int ret = recv(sClient, recveData, 64*1024, 0);
        if (ret > 0)
        {
            cout << "TCPSerer recevied: " << recveData << endl;
        }
        
    }
    cout << "servermanager end" << endl;
    pthread_mutex_unlock(&g_mutex);
}

Transfer::Transfer()
    :m_connect(false)
    ,m_client(new TCPClient)
    ,m_server(new TCPServer)
    ,m_thread(NULL)
{
    pthread_mutex_init(&g_mutex,NULL);
}

Transfer::~Transfer()
{
    delete m_client;
    delete m_thread;
    pthread_mutex_unlock(&g_mutex);
    pthread_mutex_destroy(&g_mutex);
}

void Transfer::update()
{
    
}

void Transfer::Connect()
{
    if(m_connect)
    {
        return;
    }
    if(NULL != m_client)
    {
        m_connect = m_client->Connect();
    }

     if(NULL != m_client && m_client->connectTimes() >= 0)
     {
        delete m_client;
        m_client = NULL;
        m_thread = new thread(ServerManager,m_server); 
        m_thread->detach();

        m_connect = true;

     }
}