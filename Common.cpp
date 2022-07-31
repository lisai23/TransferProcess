#include "Common.h"

map<string,string> colors;

void initcolors()
{
   colors["black"] = "\033[30m";
   colors["red"] = "\033[31m";
   colors["green"] = "\033[32m";
   colors["yellow"] = "\033[33m";
   colors["blue"] = "\033[34m";
   colors["purple"] = "\033[35m";
   colors["cyan"] = "\033[36m";
   colors["white"] = "\033[37m";
   colors["end"] = "\033[0m";
}

protocol::Directory packDate(Directory dir)
{
   protocol::Directory Dir;

   for (size_t i = 0; i < dir.getDirList().size(); i++)
   {
      /* code */
   }
   
   return Dir;
}

