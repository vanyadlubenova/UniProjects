#include "Tab.h"

Tab::Tab(char* _url, Tab* _next, Tab* _prev, time_t _dt)
{
    this->url = new char[max_url];
    strcpy(this->url, _url);
    this->next = _next;
    this->prev = _prev;
    this->dt = _dt;
}

Tab::~Tab()
{
    delete[] this->url;
}
