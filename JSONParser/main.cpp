#include "JSONValidator.h"
#include "JSONObject.h"
using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        cout << "Missing main arguments";
        return 1;
    }
    JSONValidator v;
    JSONObject json;
    if(v.isValid(argv[1]))
    {
        ifstream in(argv[1]);
        json.readObject(in);
        if(argc == 3)
        {
            if(strcmp(argv[2], "print"))
            {
                json.print();
            }
            else
            {
                json.write(argv[2]);
            }
        }
        else if(argc == 4)
        {
            if(strcmp(argv[2], "-r") == 0)
            {
                json.removeObject(argv[3]);
            }
            else
            {
                cout << "Unknown command";
            }
        }
        else if(argc == 5)
        {
            if(strcmp(argv[2], "-c") == 0)
            {
                json.createObject(argv[3], argv[4]);
            }
            else
            {
                cout << "Unknown command";
            }
        }
    }
    else
    {
        cout << "File is not valid";
    }
    return 0;
}
