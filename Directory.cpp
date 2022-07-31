#include "Directory.h"
#include "Common.h"

Directory::Directory()
    :m_dirname("")
    ,m_relativepath("")
{
    
}

Directory::Directory(path dirname)
    :m_absolutepath(dirname)
    ,m_size(0)
    ,m_relativepath("")
{
    if(!is_directory(m_absolutepath))
    {
        cout << m_absolutepath << "\": is not a directory" << endl; 
        return;
    }

    m_dirname = m_absolutepath.filename().string();
    //directory_entry entry(m_absolutepath);
    directory_iterator list(m_absolutepath);
    for (auto& it:list) 
    {
        //if (directory_entry(it.path()).status().type() == file_type::directory)
        if(is_directory(it.path()))
        {
            m_dirList.push_back(Directory(it.path()));
        }
        else
        {
            m_fileList.push_back(File(it.path()));
        }
    }

    for (auto it = m_dirList.begin(); it != m_dirList.end(); it++)
    {
        m_size += (*it).getSize();
    }

    for (auto it = m_fileList.begin(); it != m_fileList.end(); it++)
    {
        m_size += (*it).getSize();
    }
    
}

Directory::~Directory()
{
}

std::string Directory::getDirName()
{
    return m_dirname;
}

void Directory::ShowContents()
{
    directory_iterator list(m_absolutepath);
    for (auto& it:list) 
    {
        string color = colors["yellow"];
        if(is_directory(it.path()))
        {
            color = colors["blue"];
        }

        cout << color << it.path().filename().string() << colors["end"]  << endl;
    }
}

size_t Directory::getSize()
{
    return m_size;
}

bool Directory::change()
{
    return false;
}

vector<Directory> Directory::getDirList()
{
    return m_dirList;
}

vector<File> Directory::getFileList()
{
    return m_fileList;
}