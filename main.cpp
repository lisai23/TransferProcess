#include "Transfer.h"
#include "Directory.h"
#include <pthread.h>
#include "Common.h"

int main(int argc, char const *argv[])
{
    //system("chcp 65001");
    initcolors();
    if(!exists(sharepath))
    {
        cout << "sharepath: \"" << sharepath << "\" is not exist" << endl;
        return -1;
    }

    Directory share(sharepath);
    //share.ShowContents();

    while(true)
    {
        //cout << "time: " << __TIME__ << endl;
        Sleep(50); 
        if (!Transfer::Instance().getConnectStatue())
        {
            Transfer::Instance().Connect();
            continue;
        }
        

        if(share.change())
        {
            Transfer::Instance().update();
        }
    }

    return 0;
}
