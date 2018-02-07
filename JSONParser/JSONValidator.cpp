#include "JSONValidator.h"

bool JSONValidator::checkBoolean(ifstream& in, char c)
{
    if(c == 't')
    {
        if(in.eof())
        {
            return 0;
        }
        char str[4];
        in.get(str, 4);
        if(strcmp(str, "rue") != 0)
        {
            return 0;
        }
    }
    else if(c == 'f')
    {
        if(in.eof())
        {
            return 0;
        }
        char str[5];
        in.get(str, 5);
        if(strcmp(str, "alse") != 0)
        {
            return 0;
        }
    }
    else if(c == 'n')
    {
        if(in.eof())
        {
            return 0;
        }
        char str[4];
        in.get(str, 4);
        if(strcmp(str, "ull") != 0)
        {
            return 0;
        }
    }
    else
    {
        cout << "Error: Parse error" << endl << "Expecting 'EOF', boolean value, got 'undefined'";
        return 0;
    }
    return 1;
}
bool JSONValidator::checkString(ifstream& in)
{
    if(in.eof())
    {
        return 0;
    }
    string str;
    in.ignore(str.max_size(), '"');
    if(in.eof())
    {
        return 0;
    }
    in.unget();
    char c;
    in >> c;
    if(c != '"')
    {
        cout << "Error: Parse error" << endl << "Expecting 'EOF', 'quotation marks', got 'undefined'";
        return 0;
    }
    return 1;
}
bool JSONValidator::checkNumber(ifstream& in)
{
    in.unget();
    double n;
    if(!(in >> n))
    {
        cout << "Error: Parse error" << endl << "Expecting double precision floating point number, got 'undefined'";
        return 0;
    }
    return 1;
}
bool JSONValidator::checkBooleanArray(ifstream& in, char c)
{
    if(!checkBoolean(in, c))
    {
        return 0;
    }
    if(in.eof())
    {
        return 0;
    }
    in >> skipws;
    in >> c;
    if(c == ']')
    {
        return 1;
    }
    else if(c == ',')
    {
        while(true)
        {
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(!checkBoolean(in, c))
            {
                return 0;
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c == ']')
            {
                break;
            }
            if(c != ',')
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
bool JSONValidator::checkStringArray(ifstream& in)
{
    if(!checkString(in))
    {
        return 0;
    }
    if(in.eof())
    {
        return 0;
    }
    char c;
    in >> skipws;
    in >> c;
    if(c == ']')
    {
        return 1;
    }
    else if(c == ',')
    {
        while(true)
        {
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if( c != '"')
            {
                return 0;
            }
            if(!checkString(in))
            {
                return 0;
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c == ']')
            {
                break;
            }
            if(c != ',')
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
bool JSONValidator::checkNumberArray(ifstream& in)
{
    if(!checkNumber(in))
    {
        return 0;
    }
    if(in.eof())
    {
        return 0;
    }
    char c;
    in >> skipws;
    in >> c;
    if(c == ']')
    {
        return 1;
    }
    else if(c == ',')
    {
        while(true)
        {
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c < '0' || c > '9')
            {
                return 0;
            }
            if(!checkNumber(in))
            {
                return 0;
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c == ']')
            {
                break;
            }
            if(c != ',')
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
int JSONValidator::countObjectKeys(ifstream& in)
{
    int count = 0;
    char c = in.get();
    while(c != '}')
    {
        if(c == ':')
        {
            count++;
        }
        in >> c;
    }
    return count;
}
char** JSONValidator::getObjectKeys(ifstream& in, int length)
{
    char** keys = new char*[length];
    char* key = new char[2048];
    char c = in.get();
    for(int i = 0; i < length; i++)
    {
        while(c != '"')
        {
            in >> c;
        }
        in.get(key, 2048, '"');
        in.get();
        in >> c;
        if(c == ':')
        {
            keys[i] = new char[2048];
            strcpy(keys[i], key);
        }
        else
        {
            i--;
        }
    }
    while(c != '}')
    {
        in >> c;
    }
    return keys;

}
bool JSONValidator::checkOBjectArray(ifstream& in, char** arr, int length)
{
    if(in.eof())
    {
        return 0;
    }
    in >> skipws;
    char c = in.get();
    if(c == ']')
    {
        return 1;
    }
    else if(c == ',')
    {
        while(true)
        {
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c != '{')
            {
                return 0;
            }
            streampos pos = in.tellg();
            if(!checkObject(in))
            {
                return 0;
            }
            in.seekg(pos);
            int length2 = countObjectKeys(in);
            if(length != length2)
            {
                return 0;
            }
            in.seekg(pos);
            char** arr2 = getObjectKeys(in, length2);
            for(int i = 0; i < length; i++)
            {
                if(strcmp(arr[i], arr2[i]) != 0)
                {
                    return 0;
                }
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c == ']')
            {
                break;
            }
            if(c != ',')
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
bool JSONValidator::checkArray(ifstream& in)
{
    if(in.eof())
    {
        return 0;
    }
    in >> skipws;
    char c;
    in >> c;
    if(c == ']')
    {
        return 1;
    }
    else if( c == '{')
    {
        streampos pos = in.tellg();
        if(!checkObject(in))
        {
            return 0;
        }
        in.seekg(pos);
        int objectkeys = countObjectKeys(in);
        in.seekg(pos);
        char** arr = getObjectKeys(in, objectkeys);
        return checkOBjectArray(in, arr, objectkeys);
    }
    else if(c == 't' || c == 'f' || c == 'n')
    {
        return checkBooleanArray(in, c);
    }
    else if(c == '"')
    {
        return checkStringArray(in);
    }
    else if(c >= '0' && c <= '9')
    {
        return checkNumberArray(in);
    }
    else
    {
        cout << "Error: Parse error" << endl << "Expecting ']', '{', 'quotation marks', boolean value, 'digit', got 'undefined'";
        return 0;
    }
}
bool JSONValidator::checkObject(ifstream& in)
{
    if(in.eof())
    {
        return 0;
    }
    streampos pos = in.tellg();
    in >> skipws;
    char c;
    in >> c;
    if(c == '}')
    {
        return 1;
    }
    else if(c == '"')
    {
        while(true)
        {
            if(!(checkString(in)))
            {
                return 0;
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c != ':')
            {
                return 0;
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c >= '0' && c <= '9')
            {
                in.unget();
                if(!checkNumber(in))
                {
                    return 0;
                }
            }
            else if(c == '"')
            {
                if(!checkString(in))
                {
                    return 0;
                }
            }
            else if(c == '{')
            {
                if(!checkObject(in))
                {
                    return 0;
                }
            }
            else if(c == '[')
            {
                if(!checkArray(in))
                {
                    return 0;
                }
            }
            else
            {
                if(!(checkBoolean(in, c)))
                {
                    cout << "aa";
                    return 0;
                }
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            in >> c;
            if(c == '}')
            {
                break;
            }
            if(c != ',')
            {
                return 0;
            }
            if(in.eof())
            {
                return 0;
            }
            in >> skipws;
            char c;
            in >> c;
            if(c != '"')
            {
                return 0;
            }
        }
        in.seekg(pos);
        int objectkeys = countObjectKeys(in);
        in.seekg(pos);
        char** arr = getObjectKeys(in, objectkeys);
        for(int i = 0; i < objectkeys - 1; i++)
        {
            for(int j = i + 1; j < objectkeys; j++)
            {
                if(strcmp(arr[i], arr[j]) == 0)
                {
                    return 0;
                }
            }
        }
    }
    else
    {
        cout << "Error: Parse error" << endl << "Expecting 'EOF', '}', ',', ']', got 'undefined";
        return 0;
    }
    return 1;
}
JSONValidator::JSONValidator()
{

}

JSONValidator::~JSONValidator()
{

}
bool JSONValidator::isValid(char* filename)
{
    ifstream in(filename);
    if(!in)
    {
        cout << "Can't open file";
        return 0;
    }
    char c;
    if(!in.eof())
    {
        in >>skipws;
        in >> c;
        if(c != '{')
        {
            return 0;
        }
        return checkObject(in);
    }
    else
    {
        cout << "File is empty";
        return 0;
    }
}
