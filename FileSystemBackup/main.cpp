#include <iostream>
#include "Synchronizer.h"

using namespace std;

int getDirectorySize(const string& directory)
{
    DIR *dir;
    struct dirent *ent;
    int size = 0;
    if ((dir = opendir (directory.c_str())) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if(ent->d_type == DT_DIR)
            {
                size += getDirectorySize(directory + "/" + ent->d_name);
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
        synchronizer.sync(argv[1], argv[2], getDirectorySize(argv[1]));
    }
    else if(argc == 4)
    {
        if(strcmp(argv[1], "-restore") == 0)
        {
            synchronizer.sync(argv[3], argv[2], getDirectorySize(argv[3]));
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
