#ifndef TAB_H
#define TAB_H
#include <iostream>
#include <cstring>
#include <ctime>
const int max_url = 2083;

struct Tab
{
    Tab* next;
    Tab* prev;
    char* url;
    time_t dt;
    Tab(char* _url, Tab* _next = NULL, Tab* _prev = NULL, time_t _dt = time(0));
    ~Tab();
};

#endif // TAB_H
