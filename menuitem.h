#ifndef MENUITEM_H
#define MENUITEM_H

#include <vector>
#include <string>

using namespace std;

class MenuItem
{
public:
    MenuItem(string title = "");
    void addItem(MenuItem *item);
    vector<MenuItem *> getItems() const;
    string getTitle();
    void setTitle(string title);

    void select();

    void setAction(void (*cb)());

    MenuItem* parent;
private:
    void (*callback)() = nullptr;
    string title;
    vector<MenuItem*> items;
};

#endif // MENUITEM_H
