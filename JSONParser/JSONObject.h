#ifndef JSONOBJECT_H
#define JSONOBJECT_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
using namespace std;

struct Value
{
    char* str;
    double num;
    bool bl;
    bool isString;
    bool isNumber;
    bool isBoolean;
    bool isNULL;
    bool isArray;
    bool isObject;
    Value() : isObject(true), isArray(false), isString(false), isNumber(false), isBoolean(false), isNULL(false){};
};
class JSONObject
{
        char* key;
        Value value;
        JSONObject* first;
        JSONObject* last;
        JSONObject* next;
        void appendToObject(ifstream& in);
        void appendToArray(ifstream& in);
        void appendString(ifstream& in);
        void appendNumber(ifstream& in);
        void appendNULL(ifstream& in);
        void appendBoolean(ifstream& in, char c);
        void appendObject(ifstream& in);
        void appendArray(ifstream& in);
        void appendStringPair(ifstream& in, char* key);
        void appendNumberPair(ifstream& in, char* key);
        void appendNULLPair(ifstream& in, char* key);
        void appendBooleanPair(ifstream& in, char* key, char c);
        void appendObjectPair(ifstream& in, char* key);
        void appendArrayPair(ifstream& in, char* key);
        int countKeys(char* fullpath) const;
        char** getKeys(char* fullpath) const;
        void removeFirst();
        void removeLast();
        void removeObject(JSONObject* curr, char* fullpath, char** keys, int i);
        void createObject(JSONObject* curr, char* fullpath, char* value, char** keys, int i);
        void writeElement(ofstream& out,JSONObject* curr, char* fullpath, char** keys, int i);
        void writeObject(ofstream& out);
        void writeElement(char* filename, char* fullpath);
    public:
        void readObject(ifstream& in);
        void readArray(ifstream& in);
        JSONObject(char* key = NULL);
        ~JSONObject();
        bool isEmpty() const;
        void setStringValue(char* str);
        void setNumberValue(double num);
        void setBooleanValue(bool bl);
        void setNULLValue();
        void setObjectValue();
        void setArrayValue();
        bool findData(char* key) const;
        void createObject(char* fullpath, char* value);
        void removeObject(char* fullpath);
        void write(char* filename);
        void print() const;
};

#endif // JSONOBJECT_H
