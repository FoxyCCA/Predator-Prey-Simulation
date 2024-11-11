#pragma once
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_X 120
#define KEY_SPACE 32

class Menu {
public:
	virtual void printMenu();
	void loadMenu(std::string fileName);
};