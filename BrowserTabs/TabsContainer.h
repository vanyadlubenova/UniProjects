#ifndef TABSCONTAINER_H
#define TABSCONTAINER_H
#include "Tab.h"
using namespace std;

class TabsContainer
{
    Tab* first;
    Tab* last;
    int size;
private:
    void del(Tab* n);
    void cpy(const TabsContainer& tc);
    void removeFirst();
    void removeLast();
public:
    TabsContainer();
    TabsContainer(const TabsContainer& other);
    TabsContainer& operator=(const TabsContainer& other);
    ~TabsContainer();

    Tab* getFirst() const;
    Tab* getLast() const;
    int getSize() const;
    void append(char* url, time_t dt = time(0));
    void insertAfter(Tab* where, char* url);
    void removeAt(Tab* where);
    bool isEmpty();
    Tab* split(Tab* tabs, int where);
    void fix(Tab* first);
    Tab* mergeByURL(Tab* tab1, Tab* tab2);
    Tab* sortByURL(Tab* tabs, int size);
    Tab* mergeByTimestamp(Tab* tab1, Tab* tab2);
    Tab* sortByTimestamp(Tab* tabs, int size);
};

#endif // TABSCONTAINER_H
