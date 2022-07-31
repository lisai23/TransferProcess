#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include "Common.h"
#include "File.h"
#include <vector>

class File;

class Directory
{  
public:
    Directory();
    Directory(path dirname);
    void ShowContents();
    std::string getDirName();
    vector<Directory> getDirList();
    vector<File> getFileList();
    size_t getSize();
    ~Directory();

    bool change();
private:
  string m_dirname;
  path m_absolutepath;
  string m_relativepath;
  size_t m_size;
  vector<Directory> m_dirList;
  vector<File> m_fileList;
};

#endif