#include "MenuSelect.h"
#include "SubMenu.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif
#include <codecvt>
#include <cstdlib>


void Menu::printMenu() {
    int selectionLocation = 0;
    Menu menu;
    menu.loadMenu("menu1.txt");

    int value = KEY_UP;

    while (value != KEY_X) {
        switch (_getch()) {
        case KEY_UP:
            selectionLocation = 0;
            system("cls");
            menu.loadMenu("menu1.txt");
            break;

        case KEY_DOWN:
            selectionLocation = 1;
            system("cls");
            menu.loadMenu("menu2.txt");
            break;

        case KEY_SPACE:
            if (selectionLocation == 0) {
                SubMenu submenu;
                submenu.printMenu();
                menu.loadMenu("menu1.txt");
            }
            if (selectionLocation == 1) {
                return;
            }
            break;
        default:
            continue;
        }

    }
}


void Menu::loadMenu(std::string fileName) {
    try {
        std::ifstream file(fileName);
	    std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(file.rdbuf());
	    std::wistream wf(&conv);

        file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

        if (file.is_open()) {
	        #ifdef _WIN32
		        _setmode(_fileno(stdout), _O_WTEXT);
	        #else
		        std::setlocale(LC_ALL, "");
	        #endif 
                for (wchar_t c; wf.get(c); )
                    std::wcout << c;
        }

	    file.close();
    }
    catch (std::exception const& e) {
        std::wcout << "Error: " << e.what() << std::endl;
        system("pause");
    }
    
}
