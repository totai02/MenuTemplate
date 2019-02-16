#ifndef MENUBAR_H
#define MENUBAR_H

#include <iostream>
#include <vector>
#include "PCD8544.h"

#include "menuitem.h"

#define ITEM_START_POS 13
#define ITEM_SIZE 8

using namespace std;

class MenuBar
{
public:
    MenuBar(string title = "Main Menu");
    void addItem(MenuItem *item);
    void setTitle(string title);
    void enter();
    void up();
    void down();
    void back();
    void update();

private:
    int cursorPos = 0;
    int windowPos = 0;
    MenuItem root;
    MenuItem* currentMenu;

};

#endif // MENUBAR_H
