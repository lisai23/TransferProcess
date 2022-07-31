#ifndef _COMMON_H
#define _COMMON_H

#ifdef _WIN32
    #include<WinSock2.h>
    #include <Windows.h>
    #include <io.h>
    #pragma comment(lib,"ws2_32.lib")
    #define F_OK 0
#endif

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <map>
#include <vector>
#include <sys/types.h>
#include <filesystem>
using namespace std;
using namespace std::filesystem;
#include "Message.pb.h"
#include "Directory.h"
#include "File.h"

#define sharepath "C:\\Users\\lisai\\Desktop\\share" //share directory in current system

class Directory;

extern map<string,string> colors;
void initcolors();

protocol::Directory packDate(Directory dir);

#endif