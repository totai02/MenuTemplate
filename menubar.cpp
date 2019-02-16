#include "menubar.h"

int min(int a, int b)
{
    return a <= b ? a : b;
}

MenuBar::MenuBar(string title) : currentMenu(nullptr),
                                 root(MenuItem(title))
{
    currentMenu = &root;
}

void MenuBar::addItem(MenuItem *item)
{
    root.addItem(item);
    update();
}

void MenuBar::enter()
{
    MenuItem *selected = currentMenu->getItems()[cursorPos];
    if (selected->getItems().size() > 0)
    {
        currentMenu = selected;
        cursorPos = 0;
        windowPos = 0;
        update();
    }
    else
    {
        selected->select();
    }
}

void MenuBar::up()
{
    if (cursorPos > 0) cursorPos--;
    else cursorPos = currentMenu->getItems().size() - 1;

    if (cursorPos < windowPos) windowPos = cursorPos;
    if (cursorPos > windowPos + 3) windowPos = cursorPos - 3;

    update();
}

void MenuBar::down()
{
    if (cursorPos < currentMenu->getItems().size() - 1) cursorPos++;
    else cursorPos = 0;

    if (cursorPos < windowPos) windowPos = cursorPos;
    if (cursorPos > windowPos + 3) windowPos = cursorPos - 3;

    update();
}

void MenuBar::back()
{
    if (currentMenu->parent != nullptr)
    {
        currentMenu = currentMenu->parent;
        cursorPos = 0;
        windowPos = 0;
        update();
    }
}

void MenuBar::update()
{
    LCDclear();

    // draw title
    LCDsetTextColor(WHITE);
    LCDfillrect(0, 0, 84, 11, BLACK);
    LCDdrawstring_P((84 - currentMenu->getTitle().size() * 6) / 2, 2, currentMenu->getTitle().c_str());

    // draw background cursor
    LCDfillrect(2, ITEM_START_POS + ITEM_SIZE * (cursorPos - windowPos), 80, 9, BLACK);

    // draw item
    for (int i = windowPos; i < min(windowPos + 4, currentMenu->getItems().size()); i++)
    {
        string text = currentMenu->getItems()[i]->getTitle();
        if (text.size() > 13) text = text.substr(0, 13);
        LCDsetTextColor(BLACK);
        if (i == cursorPos)
        {
            LCDsetTextColor(WHITE);
            LCDdrawstring_P(3, ITEM_START_POS + ITEM_SIZE * (i - windowPos) + 1, text.c_str());
        }
        else if (i > cursorPos)
        {
            LCDdrawstring_P(3, ITEM_START_POS + ITEM_SIZE * (i - windowPos) + 2, text.c_str());
        }
        else
        {
            LCDdrawstring_P(3, ITEM_START_POS + ITEM_SIZE * (i - windowPos), text.c_str());
        }
    }

    LCDdrawrect(0, 0, 84, 48, BLACK);
    LCDsetTextColor(BLACK);
    LCDdisplay();
}
