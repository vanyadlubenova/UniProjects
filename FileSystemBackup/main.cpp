#include <iostream>
#include "Synchronizer.h"
#include <cstring>
using namespace std;
int getDirectorySize(string source, int size)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (source.c_str())) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            {
                continue;
            }
            if(ent->d_type == DT_DIR)
            {
                size += getDirectorySize(source + "/" + ent->d_name, size);
            }
            else
            {
                size++;
            }
        }
    }
    else
    {
        cout << "Could not open directory";
    }

    return size;
}
int main(int argc, char* argv[])
{
    Synchronizer synchronizer;
    if(argc == 1 || argc == 2)
    {
        cout << "Missing main arguments";
    }
    else if(argc == 3)
    {
        synchronizer.sync(argv[1], argv[2], getDirectorySize(argv[1], 0), 0);
    }
    else if(argc == 4)
    {
        if(strcmp(argv[1], "-restore") == 0)
        {
            synchronizer.sync(argv[3], argv[2], getDirectorySize(argv[3], 0), 0);
        }
        else
        {
            cout << "Invalid input";
        }
    }
    else
    {
        cout << "Invalid input";
    }
    return 0;
}
