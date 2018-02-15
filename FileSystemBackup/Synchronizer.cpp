#include "Synchronizer.h"

Synchronizer::Synchronizer()
{

}
Synchronizer::~Synchronizer()
{

}
const char* Synchronizer::getHash(const string& file_path) const
{
    MD5 md5;
    return md5.digestFile(const_cast<char*>(file_path.c_str()));
}
void Synchronizer::createFolder(const string&  folder_path) const
{
    mkdir(folder_path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
}
void Synchronizer::copyFile(const string& src_path, const string& dest_path) const
{
    ifstream source(src_path, ios::binary);
    ofstream dest(dest_path, ios::binary | ios::trunc);
    dest << source.rdbuf();
    source.close();
    dest.close();
}
void Synchronizer::createFile(const string& file_path, const string& file_name, const string& dest_path) const
{
    ifstream source(file_path, ios::binary);
    ofstream dest(dest_path + "/" + file_name, ios::binary);
    dest << source.rdbuf();
    source.close();
    dest.close();
}
void Synchronizer::sync(const string& activedir, const string& backupdir, int directory_size, int progress) const
{
    DIR *dir1;
    DIR *dir2;
    struct dirent *ent1;
    struct dirent *ent2;
    if ((dir1 = opendir (activedir.c_str())) != NULL && (dir2 = opendir (backupdir.c_str())) != NULL)
    {
        while ((ent1 = readdir (dir1)) != NULL)
        {
            if(strcmp(ent1->d_name, ".") == 0 || strcmp(ent1->d_name, "..") == 0)
            {
                continue;
            }
            bool file_exist = false;
            string ent1_file_path = activedir + "/" + ent1->d_name;
            const char* ent1_file_hash = getHash(const_cast<char*>(ent1_file_path.c_str()));
            while ((ent2 = readdir (dir2)) != NULL)
            {
                if(strcmp(ent2->d_name, ".") == 0 || strcmp(ent2->d_name, "..") == 0)
                {
                    continue;
                }
                if(strcmp(ent1->d_name, ent2->d_name) == 0 && ent1->d_type == ent2->d_type)
                {
                    file_exist = true;
                    string ent2_file_path = backupdir + "/" + ent2->d_name;
                    if(ent1->d_type == DT_DIR)
                    {
                        sync(ent1_file_path, ent2_file_path, directory_size, progress++);
                    }
                    if(ent1->d_type == DT_REG)
                    {
                        const char* ent2_file_hash = getHash(const_cast<char*>(ent2_file_path.c_str()));
                        if(strcmp(ent1_file_hash, ent2_file_hash) != 0)
                        {
                            copyFile(ent1_file_path, ent2_file_path);
                            cout << "copying " << ent1->d_name << " ";
                        }
                    }
                    break;
                }
            }
            if(!file_exist)
            {
                if(ent1->d_type == DT_DIR)
                {
                    createFolder(backupdir + "/" + ent1->d_name);
                    sync(ent1_file_path, backupdir + "/" + ent1->d_name, directory_size, progress++);
                }
                if(ent1->d_type == DT_REG)
                {
                    createFile(ent1_file_path, ent1->d_name, backupdir);
                }
            }
            progress++;
            cout << ent1->d_name << " ";
            cout << ((double)progress / directory_size) * 100.0 << "%" << endl;
            dir2 = opendir (backupdir.c_str());
        }
    }
    else
    {
        cout << "Could not open directory";
    }
    sync_deleted_files(activedir, backupdir);
}
void Synchronizer::sync_deleted_files(const string& activedir, const string& backupdir) const
{
    DIR *dir1;
    DIR *dir2;
    struct dirent *ent1;
    struct dirent *ent2;
    if ((dir1 = opendir (backupdir.c_str())) != NULL && (dir2 = opendir (activedir.c_str())) != NULL)
    {
        while ((ent1 = readdir (dir1)) != NULL)
        {
            if(strcmp(ent1->d_name, ".") == 0 || strcmp(ent1->d_name, "..") == 0)
            {
                continue;
            }
            bool file_exist = false;
            while((ent2 = readdir (dir2)) != NULL)
            {
                if(strcmp(ent2->d_name, ".") == 0 || strcmp(ent2->d_name, "..") == 0)
                {
                    continue;
                }
                if(strcmp(ent1->d_name, ent2->d_name) == 0 && ent1->d_type == ent2->d_type)
                {
                    file_exist = true;
                    if(ent1->d_type == DT_DIR)
                    {
                        sync_deleted_files(activedir + "/" + ent2->d_name, backupdir + "/" + ent1->d_name);
                    }
                    break;
                }
            }
            if(!file_exist)
            {
                string deleted_file = backupdir + "/" + ent1->d_name;
                remove(deleted_file.c_str());
            }
            dir2 = opendir (backupdir.c_str());
        }
    }
    else
    {
        cout << "Could not open directory";
    }
}
