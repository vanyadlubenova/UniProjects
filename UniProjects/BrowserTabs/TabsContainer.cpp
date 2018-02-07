#include "TabsContainer.h"


void TabsContainer::del(Tab* n)
{
    if(n == NULL)
    {
        return;
    }
    del(n->next);
    delete n;
    this->size--;
}
void TabsContainer::cpy(const TabsContainer& other)
{
    for(Tab* it = other.first; it; it = it->next)
    {
        append(it->url, it->dt);
    }
    this->size = other.size;
}
TabsContainer::TabsContainer()
{
    first = last = new Tab((char*)"about:blank");
    this->size = 1;
}
TabsContainer::TabsContainer(const TabsContainer& other)
{
    cpy(other);
}
TabsContainer& TabsContainer::operator=(const TabsContainer& other)
{
    if(this != &other)
    {
        del(first);
        cpy(other);
    }
    return *this;
}
TabsContainer::~TabsContainer()
{
    del(first);
}
Tab* TabsContainer::getFirst() const
{
    return this->first;
}
Tab* TabsContainer::getLast() const
{
    return this->last;
}
int TabsContainer::getSize() const
{
    return this->size;
}
bool TabsContainer::isEmpty()
{
    return !first;
}
void TabsContainer::append(char* url, time_t dt)
{
    if(isEmpty())
    {
        first = last = new Tab(url, NULL, NULL, dt);
    }
    else
    {
        last->next = new Tab(url, NULL, last, dt);
        last = last->next;
    }
    this->size++;
}
void TabsContainer::insertAfter(Tab* where, char* url)
{
    if(!where)
    {
        return;
    }
    else if(where == last)
    {
        append(url);
    }
    else
    {
        Tab* n = new Tab(url, where->next, where);
        where->next = n;
        where->next->prev = n;
        this->size++;
    }
}
void TabsContainer::removeFirst()
{
    Tab* tmp = first;
    first = first->next;
    first->prev = NULL;
    delete tmp;
}
void TabsContainer::removeLast()
{
    Tab* tmp = last;
    last = last->prev;
    last->next = NULL;
    delete tmp;
}
void TabsContainer::removeAt(Tab* where)
{
    if(!where)
    {
        return;
    }
    else if(where == first)
    {
        removeFirst();
    }
    else if(where == last)
    {
        removeLast();
    }
    else
    {
        where->next->prev = where->prev;
        where->prev->next = where->next;
        delete where;
    }
    this->size--;
}
Tab* TabsContainer::split(Tab* fst, int where)
{
    while(--where)
    {
        fst = fst->next;
    }
    Tab* result = fst->next;
    fst->next = NULL;
    return result;
}
void TabsContainer::fix(Tab* fst)
{
    if(!fst) return;
    this->first = fst;
    fst->prev = NULL;
    while(fst->next)
    {
        fst->next->prev = fst;
        fst = fst->next;
    }
    last = fst;
}
Tab* TabsContainer::mergeByURL(Tab* tab1, Tab* tab2)
{
    if(!tab1) return tab2;
    if(!tab2) return tab1;
    Tab* result;
    if(strcmp(tab1->url, tab2->url) < 0)
    {
        result = tab1;
        tab1 = tab1->next;
    }
    else
    {
        result = tab2;
        tab2 = tab2->next;
    }
    Tab* current = result;
    while(tab1 && tab2)
    {
        if(strcmp(tab1->url, tab2->url) < 0)
        {
            current->next = tab1;
            tab1 = tab1->next;
        }
        else
        {
            current->next = tab2;
            tab2 = tab2->next;
        }
        current = current->next;
    }
    if(!tab1)
    {
        current->next = tab2;
    }
    if(!tab2)
    {
        current->next = tab1;
    }
    return result;
}
Tab* TabsContainer::sortByURL(Tab* fst, int size)
{
    if(size < 2) return fst;
    Tab* snd = split(fst, size / 2);
    fst = sortByURL(fst, size / 2);
    snd = sortByURL(snd, size - (size / 2 + 1));
    return mergeByURL(fst, snd);
}
Tab* TabsContainer::mergeByTimestamp(Tab* tab1, Tab* tab2)
{
    if(!tab1) return tab2;
    if(!tab2) return tab1;
    Tab* result;
    if(tab1->dt <= tab2->dt)
    {
        result = tab1;
        tab1 = tab1->next;
    }
    else
    {
        result = tab2;
        tab2 = tab2->next;
    }
    Tab* current = result;
    while(tab1 && tab2)
    {
        if(tab1->dt <= tab2->dt)
        {
            current->next = tab1;
            tab1 = tab1->next;
        }
        else
        {
            current->next = tab2;
            tab2 = tab2->next;
        }
        current = current->next;
    }
    if(!tab1)
    {
        current->next = tab2;
    }
    if(!tab2)
    {
        current->next = tab1;
    }
    return result;
}
Tab* TabsContainer::sortByTimestamp(Tab* fst, int size)
{
    if(size < 2) return fst;
    Tab* snd = split(fst, size / 2);
    fst = sortByTimestamp(fst, size / 2);
    snd = sortByTimestamp(snd, size - (size / 2 + 1));
    return mergeByTimestamp(fst, snd);
}
