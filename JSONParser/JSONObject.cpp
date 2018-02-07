
#include "JSONObject.h"

JSONObject::JSONObject(char* key)
{
    if(key != NULL)
    {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
    }
    first = last = next = NULL;
}
JSONObject::~JSONObject()
{

}
bool JSONObject::isEmpty() const
{
    return !first;
}
void JSONObject::setStringValue(char* str)
{
    this->value.isObject = false;
    this->value.isString = true;
    this->value.str = new char[strlen(str) + 1];
    strcpy(this->value.str, str);
}
void JSONObject::setNumberValue(double num)
{
    this->value.isObject = false;
    this->value.isNumber = true;
    this->value.num = num;
}
void JSONObject::setBooleanValue(bool bl)
{
    this->value.isObject = false;
    this->value.isBoolean = true;
    this->value.bl = bl;
}
void JSONObject::setNULLValue()
{
    this->value.isObject = false;
    this->value.isNULL = true;
}
void JSONObject::setArrayValue()
{
    this->value.isObject = false;
    this->value.isArray = true;
}
void JSONObject::readObject(ifstream& in)
{
    char c;
    in >> skipws;
    in.ignore();
    in >> skipws;
    in >> c;
    if(c == '}')
    {
        return;
    }
    if(c == '"')
    {
        while(c != '}')
        {
            if(c == '"')
            {
                appendToObject(in);
            }
            in >> c;
        }
    }
}
void JSONObject::readArray(ifstream& in)
{
    char c;
    in >> skipws;
    in.ignore();
    in >> skipws;
    in >> c;
    if(c == ']')
    {
        return;
    }
    in.unget();
    appendToArray(in);

}

void JSONObject::appendStringPair(ifstream& in, char* key)
{
    char c;
    streampos pos = in.tellg();
    int size = 0;
    in >> c;
    while(c != '"')
    {
        c = in.get();
        size++;
    }
    char* value = new char[size];
    in.seekg(pos);
    in.get(value, size + 1, '"');
    in.ignore();
    if(isEmpty())
    {
        first = last = new JSONObject(key);
        first->setStringValue(value);
    }
    else
    {
        last->next = new JSONObject(key);
        last = last->next;
        last->setStringValue(value);
    }
}
void JSONObject::appendNumberPair(ifstream& in, char* key)
{
    double value;
    in.unget();
    in >> value;
    if(isEmpty())
    {
        first = last = new JSONObject(key);
        first->setNumberValue(value);
    }
    else
    {
        last->next = new JSONObject(key);
        last = last->next;
        last->setNumberValue(value);
    }
}
void JSONObject::appendBooleanPair(ifstream& in, char* key, char c)
{
    bool value;
    if(c == 't')
    {
        value = true;
    }
    else
    {
        value = false;
    }
    if(isEmpty())
    {
        first = last = new JSONObject(key);
        first->setBooleanValue(value);
    }
    else
    {
        last->next = new JSONObject(key);
        last = last->next;
        last->setBooleanValue(value);
    }
}
void JSONObject::appendNULLPair(ifstream& in, char* key)
{
    if(isEmpty())
    {
        first = last = new JSONObject(key);
        first->setNULLValue();
    }
    else
    {
        last->next = new JSONObject(key);
        last = last->next;
        last->setNULLValue();
    }
}
void JSONObject::appendObjectPair(ifstream& in, char* key)
{
    if(isEmpty())
    {
        first = last = new JSONObject(key);
        first->readObject(in);
    }
    else
    {
        last->next = new JSONObject(key);
        last = last->next;
        last->readObject(in);
    }
}
void JSONObject::appendArrayPair(ifstream& in, char* key)
{
    if(isEmpty())
    {
        first = last = new JSONObject(key);
        first->setArrayValue();
        first->readArray(in);
    }
    else
    {
        last->next = new JSONObject(key);
        last = last->next;
        last->setArrayValue();
        last->readArray(in);
    }
}
void JSONObject::appendString(ifstream& in)
{
    char c;
    streampos pos = in.tellg();
    int size = 0;
    in >> c;
    while(c != '"')
    {
        c = in.get();
        size++;
    }
    char* value = new char[size];
    in.seekg(pos);
    in.get(value, size + 1, '"');
    in.ignore();
    if(isEmpty())
    {
        first = last = new JSONObject();
        first->setStringValue(value);
    }
    else
    {
        last->next = new JSONObject();
        last = last->next;
        last->setStringValue(value);
    }
}
void JSONObject::appendNumber(ifstream& in)
{
    double value;
    in.unget();
    in >> value;
    if(isEmpty())
    {
        first = last = new JSONObject();
        first->setNumberValue(value);
    }
    else
    {
        last->next = new JSONObject();
        last = last->next;
        last->setNumberValue(value);
    }
}
void JSONObject::removeFirst()
{
    JSONObject* obj = first;
    first = first->next;
    delete obj;
}
void JSONObject::removeLast()
{
    JSONObject* obj = first;
    while(obj->next != last)
    {
        obj = obj->next;
    }
    JSONObject* r = last;
    obj->next = NULL;
    last = obj;
    delete r;
}
void JSONObject::removeObject(JSONObject* curr, char* fullpath, char** keys, int i)
{
        if(i == countKeys(fullpath))
        {
            cout << "Key is not found";
            return;
        }
        for(JSONObject* it = curr->first; it; it=it->next)
        {
            if(strcmp(it->key, keys[i]) == 0)
            {
                if(i != (countKeys(fullpath) - 1))
                {
                    removeObject(curr, fullpath, keys, i + 1);
                }
                else if(it == first)
                {
                    removeFirst();
                }
                else if(it == last)
                {
                    removeLast();
                }
                else
                {
                    JSONObject* r = first;
                    while(r ->next != it)
                    {
                        r = r->next;
                    }
                    r->next = r->next->next;
                    delete it;
                }
            }

        }
        cout << "Key is not found";
}
void JSONObject::removeObject(char* fullpath)
{
    removeObject(this, fullpath, getKeys(fullpath), 0);
}
void JSONObject::appendBoolean(ifstream& in, char c)
{
    bool value;
    if(c == 't')
    {
        value = true;
        in.ignore(3);
    }
    else
    {
        value = false;
        in.ignore(4);
    }
    if(isEmpty())
    {
        first = last = new JSONObject();
        first->setBooleanValue(value);
    }
    else
    {
        last->next = new JSONObject();
        last = last->next;
        last->setBooleanValue(value);
    }
}
void JSONObject::appendNULL(ifstream& in)
{
    if(isEmpty())
    {
        first = last = new JSONObject();
        first->setNULLValue();
    }
    else
    {
        last->next = new JSONObject();
        last = last->next;
        last->setNULLValue();
    }
}
void JSONObject::appendObject(ifstream& in)
{
    if(isEmpty())
    {
        first = last = new JSONObject();
        first->readObject(in);
    }
    else
    {
        last->next = new JSONObject();
        last = last->next;
        last->readObject(in);
    }
}
void JSONObject::appendArray(ifstream& in)
{
    if(isEmpty())
    {
        first = last = new JSONObject();
        first->setArrayValue();
        first->readArray(in);
    }
    else
    {
        last->next = new JSONObject();
        last = last->next;
        last->setArrayValue();
        last->readArray(in);
    }
}
void JSONObject::appendToObject(ifstream& in)
{
    char c;
    char* key = new char[2048];
    in.get(key, 2048, '"');
    in.ignore(2048, ':');
    in.ignore();
    in >> skipws;
    in >> c;
    if(c == '"')
    {
       appendStringPair(in, key);
    }
    else if(c >= '0' && c <= '9')
    {
        appendNumberPair(in, key);
    }
    else if(c == 't' || c == 't')
    {
        appendBooleanPair(in, key, c);
    }
    else if(c == 'n')
    {
        appendNULLPair(in, key);
    }
    else if(c == '{')
    {
        in.unget();
        appendObjectPair(in, key);
    }
    else if(c == '[')
    {
        in.unget();
        appendArrayPair(in, key);
    }
}
void JSONObject::appendToArray(ifstream& in)
{
    in >> skipws;
    char c;
    in >> c;
    while(c != ']')
    {
        if(c == '"')
        {
           appendString(in);
        }
        else if(c >= '0' && c <= '9')
        {
            appendNumber(in);
        }
        else if(c == 't' || c == 'f')
        {
            appendBoolean(in, c);
        }
        else if(c == 'n')
        {
            appendNULL(in);
        }
        else if(c == '{')
        {
            in.unget();
            appendObject(in);
        }
        else if(c == '[')
        {
            in.unget();
            appendArray(in);
        }
        else if(c == ',')
        {
            in >> skipws;
            in >> c;
            continue;
        }
        in >> skipws;
        in >> c;
    }
}
bool JSONObject::findData(char* key) const
{
    bool flag = false;
    for(JSONObject* it = first; it; it=it->next)
    {
        if(strcmp(it->key, key) == 0)
        {
            flag = true;
        }
    }
    return flag;
}
char** JSONObject::getKeys(char* fullpath) const
{
    char** keys = new char*[countKeys(fullpath)];
    char* key;
    key = strtok (fullpath," ,.-");
    int i = 0;
    while (key != NULL)
    {
        key = strtok (NULL, " ,.-");
        keys[i] = key;
        i++;
    }
    return keys;
}
int JSONObject::countKeys(char* fullpath) const
{
    int size = 1;
    for(int i = 0; i < strlen(fullpath); i++)
    {
        if(fullpath[i] == ':')
        {
            size++;
        }
    }
    return size;
}
void JSONObject::writeElement(char* filename, char* fullpath)
{
    ofstream out(filename);
    if(!out)
    {
        cout << "Can't open file";
    }
    writeElement(out, this, fullpath, getKeys(fullpath), 0);
}
void JSONObject::writeElement(ofstream& out, JSONObject* curr, char* fullpath, char** keys, int i)
{
        if(i == countKeys(fullpath))
        {
            cout << "Key is not found";
            return;
        }
        for(JSONObject* it = curr->first; it; it=it->next)
        {
            if(strcmp(it->key, keys[i]) == 0)
            {
                if(i != countKeys(fullpath) - 1)
                {
                    writeElement(out, it, fullpath, keys, i + 1);
                }
                else
                {
                    it->writeObject(out);
                }
            }
        }
        cout << "Key is not found";
}
void JSONObject::createObject(JSONObject* curr, char* fullpath, char* value, char** keys, int i)
{
        if(i == countKeys(fullpath))
        {
            cout << "Key is not found";
            return;
        }
        for(JSONObject* it = curr->first; it; it=it->next)
        {
            if(strcmp(it->key, keys[i]) == 0)
            {
                if(i != countKeys(fullpath) - 2)
                {
                    createObject(it, fullpath, value, keys, i + 1);
                }
                else
                {
                    ofstream out("json");
                    out << value;
                    out.close();
                    ifstream in("json");
                    in >> skipws;
                    char c = in.get();
                    if(c == '"')
                    {
                        it->appendStringPair(in, keys[i]);
                        return;
                    }
                    else if(c >= '0' && c <= '9')
                    {
                        it->appendNumberPair(in, keys[i]);
                        return;
                    }
                    else if(c == 't' || c == 'f')
                    {
                        it->appendBooleanPair(in, keys[i], c);
                        return;
                    }
                    else if(c == '[')
                    {
                        in.unget();
                        it->appendArrayPair(in, keys[i]);
                    }
                    else if(c == '{')
                    {
                        in.unget();
                        it->appendObjectPair(in, keys[i]);
                    }
                    remove("json");
              }
          }
        }
        cout << "Key is not found";
}
void JSONObject::createObject(char* fullpath, char* value)
{
    createObject(this, fullpath, value, getKeys(fullpath), 0);
}
void JSONObject::writeObject(ofstream& out)
{
    if(this->value.isString)
    {
        out << '"' << this->value.str<< '"' ;
    }
    else if(this->value.isNumber)
    {
        out << this->value.num;
    }
    else if(this->value.isBoolean)
    {
        if(this->value.bl)
        {
            out << "true";
        }
        else
        {
            out << "false";
        }
    }
    else if(this->value.isObject)
    {
        out << "{" << "\n";
        for(JSONObject* it = first; it; it=it->next)
        {
            if(it->key != NULL)
            {
                out<< '"'  << it->key<< '"'  << " : ";
            }
            it->writeObject(out);
            if(it->next != NULL)
            {
                out << "," << "\n";
            }
            else
            {
                out << "\n";
            }
        }
        out << "}" << "\n";
    }
    else
    {
        out << "[";
        for(JSONObject* it = this->first; it; it=it->next)
        {
            it->writeObject(out);
            if(it->next != NULL)
            {
                out << ',';
            }

        }
        out << "]";
    }
}
void JSONObject::write(char* filename)
{
    ofstream out(filename);
    if(!out.good())
    {
        cout << "File already exist" << endl;
        cout << "Type new filename" << endl;
        char* newfilename = new char[255];
        cin >> newfilename;
        write(newfilename);
    }
    writeObject(out);
}
void JSONObject::print() const
{
    if(this->value.isString)
    {
        cout << this->value.str;
    }
    else if(this->value.isNumber)
    {
        cout << this->value.num;
    }
    else if(this->value.isBoolean)
    {
        if(this->value.bl)
        {
            cout << "true";
        }
        else
        {
            cout << "false";
        }
    }
    else if(this->value.isObject)
    {
        cout << "{" << endl;
        for(JSONObject* it = first; it; it=it->next)
        {
            if(it->key != NULL)
            {
                cout << it->key << " : ";
            }
            it->print();
            if(it->next != NULL)
            {
                cout << "," << endl;
            }
            else
            {
                cout << endl;
            }
        }
        cout << "}" << endl;
    }
    else
    {
        cout << "[";
        for(JSONObject* it = this->first; it; it=it->next)
        {
            it->print();
            if(it->next != NULL)
            {
                cout << ',';
            }

        }
        cout << "]";
    }
}
