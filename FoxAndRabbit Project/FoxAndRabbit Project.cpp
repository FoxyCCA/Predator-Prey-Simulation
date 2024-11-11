#include <iostream>
#include <windows.h>
#include "MenuSelect.h"


int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.right / 2, r.bottom / 2, 600, 500, TRUE);

    Menu menu;
    menu.printMenu();

    return 0;
}