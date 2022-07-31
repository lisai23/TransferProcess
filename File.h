#ifndef _FILE_H
#define _FILE_H

#include "Common.h"
#include <sys/stat.h>

class File
{
public:
    File();
    File(path filepath);
    std::string getFileName();
    size_t getSize();
    ~File();
private:
    std::string m_filename;
    path m_absolutepath;
    std::string m_relativepath;
    size_t m_size;
    int32_t m_crcvalue;
};

#endif