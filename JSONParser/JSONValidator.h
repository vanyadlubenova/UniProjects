#ifndef JSONVALIDATOR_H
#define JSONVALIDATOR_H
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class JSONValidator
{
    private:
        bool checkBoolean(ifstream& in, char c);
        bool checkString(ifstream& in);
        bool checkNumber(ifstream& in);
        bool checkObject(ifstream& in);
        bool checkArray(ifstream& in);
        bool checkBooleanArray(ifstream& in, char c);
        bool checkStringArray(ifstream& in);
        bool checkNumberArray(ifstream& in);
        bool checkOBjectArray(ifstream& in, char** arr, int length);
        int countObjectKeys(ifstream& in);
        char** getObjectKeys(ifstream& in, int length);
    public:
        JSONValidator();
        ~JSONValidator();
        bool isValid(char* filename);
};

#endif // JSONVALIDATOR_H
