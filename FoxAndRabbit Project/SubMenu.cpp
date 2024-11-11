#include "SubMenu.h"
#include "Simulation.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif
#include <codecvt>
#include <cstdlib>

void SubMenu::printMenu() {
    system("cls");
    Simulation sim;
    Menu menu;

    int foxPopulation = 500, rabbitPopulation = 1000, simulationTime = 10;
    unsigned short int selectionLocation = 1;

    std::string menuFile;

    int value = KEY_UP;

    while (value != KEY_X) {
        system("cls");

        menuFile = ("submenu" + std::to_string(selectionLocation) + ".txt");
        menu.loadMenu(menuFile);

        std::wcout << "Current fox population size: " << foxPopulation << std::endl;
        std::wcout << "Current rabbit population size: " << rabbitPopulation << std::endl;
        std::wcout << "Current simulation time: " << simulationTime << std::endl;
        
        switch (_getch()) {
        case KEY_UP:
            if (selectionLocation > 1) {
                selectionLocation--;
            }
            break;

        case KEY_DOWN:
            if (selectionLocation < 4) {
                selectionLocation++;
            }
            break;

        case KEY_SPACE:
            if (selectionLocation == 1) {
                system("cls");
                sim.startSimulation(foxPopulation, rabbitPopulation, simulationTime);
            }
            if (selectionLocation == 2) {
                system("cls");
                std::wcout << "\n      <Select population size>\n";
                std::wcout << "\nEnter fox population size: ";
                std::cin >> foxPopulation;
                std::wcout << "\nEnter rabbit population size: ";
                std::cin >> rabbitPopulation;
                std::wcout << "\nEnter simulation time span: ";
                std::cin >> simulationTime;

                while (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    system("cls");

                    std::wcout << "Error - An input was not a number, try again\n";
                    std::wcout << "\nEnter fox population size: ";
                    std::cin >> foxPopulation;
                    std::wcout << "\nEnter rabbit population size: ";
                    std::cin >> rabbitPopulation;
                    std::wcout << "\nEnter simulation time span: ";
                    std::cin >> simulationTime;
                }

                if (foxPopulation < 0) foxPopulation = 0;
                if (rabbitPopulation < 0) rabbitPopulation = 0;
                if (simulationTime < 0) simulationTime = 0;
            }
            if (selectionLocation == 3) {
                system("cls");
                sim.loadSimulation();
            }
            if (selectionLocation == 4) {
                system("cls");
                return;
            }
            break;
        default:
            break;
        }
    }
    return;
}


