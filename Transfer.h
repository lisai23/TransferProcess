#ifndef _TRANSFER_H
#define _TRANSFER_H

#include "Common.h"
#include "TCPClient.h"
#include "TCPServer.h"
#include <thread>
#include "Message.pb.h"

class Transfer
{
public:
    ~Transfer();
    static Transfer& Instance(){static Transfer obj; return obj;}

    bool getConnectStatue(){return m_connect;}
    void update();
    void Connect();
private:
    Transfer();
    bool m_connect;
    TCPClient *m_client;
    TCPServer *m_server;
    thread *m_thread;
};

#endif