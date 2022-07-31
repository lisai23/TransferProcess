#include "File.h"

File::File()
    :m_filename("")
    ,m_size(0)
    ,m_crcvalue(0)
    ,m_relativepath("")
{
}

File::File(path filepath)
    :m_absolutepath(filepath)
    ,m_relativepath("")
    ,m_crcvalue(0)
{
    if(!exists(m_absolutepath))
    {
        cout << "file: \"" << m_absolutepath << "\" is not exist" << endl; 
        return;
    }

    m_filename = m_absolutepath.filename().string();
    
	struct stat statbuf;

	if(stat(m_absolutepath.string().c_str(), &statbuf) < 0)
    {
        fprintf(stderr, "Get %s Size Error: %s\n", m_filename.c_str() ,strerror(errno));
    }
    else
    {
        m_size = statbuf.st_size;
    }
}

File::~File()
{
}

std::string File::getFileName()
{
    return m_filename;
}

size_t File::getSize()
{
    return m_size;
}