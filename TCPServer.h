#include "Common.h"
#include "Directory.h"

class TCPServer
{
public:
    TCPServer(/* args */);
    ~TCPServer();
    //void HnadleMsg();
    void Init();
    bool start();
    SOCKET &getClient();
    char *getRecveDate();
    void InitData();
private:
    SOCKET m_slisten;
    char *m_recveDate;
    bool m_start;
    SOCKET m_sClient;
    Directory m_share;
};