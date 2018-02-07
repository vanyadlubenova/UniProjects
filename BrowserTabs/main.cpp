#include <iostream>
#include "Browser.h"
using namespace std;
int main()
{
    Browser br;
    char* input = new char[2000];
    while(true)
    {
        cin >> input;
        if(strcmp(input, "BACK") == 0)
        {
            br.BACK();
        }
        else if(strcmp(input, "FORWARD") == 0)
        {
            br.FORWARD();
        }
        else if(strcmp(input, "REMOVE") == 0)
        {
            br.REMOVE();
        }
        else if(strcmp(input, "PRINT") == 0)
        {
            br.PRINT();
        }
        else if(strcmp(input, "GO") == 0)
        {
            cin >> input;
            br.GO(input);
        }
        else if(strcmp(input, "INSERT") == 0)
        {
            cin >> input;
            br.INSERT(input);
        }
        else if(strcmp(input, "SORT") == 0)
        {
            cin >> input;
            if(strcmp(input, "URL") == 0)
            {
                br.SORTByURL();
            }
            else if(strcmp(input, "TIME") == 0)
            {
                br.SORTByTimestamp();
            }
            else
            {
                cout << "This sort does not exist" << endl;
            }
        }
        else
        {
            cout << "Command does not exist" << endl;
        }
    }

    return 0;
}
