#include "menuitem.h"

MenuItem::MenuItem(string title) : parent(nullptr)
{
    this->title = title;
}

void MenuItem::addItem(MenuItem *item)
{
    items.push_back(item);
    item->parent = this;
}

vector<MenuItem *> MenuItem::getItems() const
{
    return items;
}

string MenuItem::getTitle()
{
    return title;
}

void MenuItem::setTitle(string title)
{
    this->title = title;
}

void MenuItem::select()
{
    if (callback != nullptr) (*callback)();
}

void MenuItem::setAction(void (*cb)())
{
    callback = cb;
}
