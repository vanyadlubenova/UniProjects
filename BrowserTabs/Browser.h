#ifndef BROWSER_H
#define BROWSER_H
#include "TabsContainer.h"
using namespace std;
class Browser
{
    TabsContainer tabs;
    Tab* current;
public:
    Browser();
    ~Browser();
public:
    void GO(char* url);
    void INSERT(char* url);
    void BACK();
    void FORWARD();
    void REMOVE();
    void PRINT();
    void SORTByURL();
    void SORTByTimestamp();
};

#endif // BROWSER_H
