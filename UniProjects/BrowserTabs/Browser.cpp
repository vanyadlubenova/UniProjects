#include "Browser.h"

Browser::Browser()
{
    this->current = tabs.getFirst();
}

Browser::~Browser()
{

}
void Browser::GO(char* url)
{
    strcpy(this->current->url, url);
    this->current->dt = time(0);
}
void Browser::INSERT(char* url)
{
    this->tabs.insertAfter(this->current, url);
    this->current = this->current->next;
}
void Browser::BACK()
{
    this->current = current->prev;
    if(!this->current)
    {
        this->current = tabs.getLast();
    }
}
void Browser::FORWARD()
{
    this->current = current->next;
    if(!this->current)
    {
        this->current = tabs.getFirst();
    }
}
void Browser::REMOVE()
{
    Tab* tmp = current;
    if(!this->current)
    {
        current = current->prev;
    }
    else
    {
        current = current->next;
    }
    tabs.removeAt(tmp);
    if(tabs.isEmpty())
    {
        this->current = new Tab((char*)"about:blank");
        tabs.append(this->current->url, this->current->dt);
    }
}
void Browser::PRINT()
{
    for(Tab* it = tabs.getFirst(); it; it = it->next)
    {
        if(it == this->current)
        {
            cout << ">";
        }
        cout << it->url << " " << it->dt << endl;
    }
}
void Browser::SORTByURL()
{
    Tab* first = this->tabs.sortByURL(tabs.getFirst(), tabs.getSize());
    this->tabs.fix(first);
    this->current = tabs.getFirst();
}
void Browser::SORTByTimestamp()
{
    Tab* first = this->tabs.sortByTimestamp(tabs.getFirst(), tabs.getSize());
    this->tabs.fix(first);
    this->current = tabs.getFirst();
}
