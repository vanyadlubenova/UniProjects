#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "MD5.h"

using namespace std;

class Synchronizer
{
    private:
        const char* getHash(const string& file_path) const;
        void copyFile(const string& src_path, const string& dest_path) const;
        void createFile(const string& file_path, const string& file_name, const string& dest_path) const;
        void createFolder(const string& folder_path) const;
        void sync_deleted_files(const string& activedir, const string& backupdir) const;
    public:
        Synchronizer();
        ~Synchronizer();
        void sync(const string& activedir, const string& backupdir, int directory_size, int progress) const;
};

#endif // SYNCHRONIZER_H
