#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

bool operator ==(Fox& fox, Rabbit& rab) {
    if (abs(fox.getFoxPopulation() - rab.getRabbitPopulation()) < 100) {
        return true;
    }
    return false;
}

bool operator >(Fox& fox, Rabbit& rab) {
    return (fox.getFoxPopulation() > rab.getRabbitPopulation());
}

bool operator <(Fox& fox, Rabbit& rab) {
    return (fox.getFoxPopulation() < rab.getRabbitPopulation());
}

void Simulation::startSimulation(double foxPopulation, double rabbitPopulation, double simulationTime, bool isLoadFile) {
    Fox fox(foxPopulation);
    Rabbit rab(rabbitPopulation);
    double rabbitRate;
    double foxRate;
    int maxPopulationSize = (int)foxPopulation + (int)rabbitPopulation;
    short int rabPercentage = 0, foxPercentage = 0, currentFoxPercent = 0, currentRabPercent;

    std::vector<double> foxVector;
    std::vector<double> rabVector;
    
    for (float i = 0.0f; i < simulationTime; i+=0.1f) {
        rabbitRate = rab.findRateOfChange(fox.getFoxPopulation());
        foxRate = fox.findRateOfChange(rab.getRabbitPopulation());

        rab.newPopulationSize(rabbitRate);
        fox.newPopulationSize(foxRate);

        if (fox.getFoxPopulation() < 0) {
            fox.setFoxPopulation(0);
        } 
        
        if (rab.getRabbitPopulation() < 0) {
            rab.setRabbitPopulation(0);
        }

        foxVector.push_back(fox.getFoxPopulation());
        rabVector.push_back(rab.getRabbitPopulation());

        currentFoxPercent = (fox.getFoxPopulation() / maxPopulationSize) * 100;
        currentRabPercent = (rab.getRabbitPopulation() / maxPopulationSize) * 100;
        
        // UI---------------------------------------------------------------------------------
        system("cls");
        std::wcout << "\t<Simulation>\n" << std::endl;
        
        for (int percent = 90; percent >= 0; percent = percent - 10) {
            if (fox > rab && currentFoxPercent >= percent) { std::wcout << L"\t\u2588"; }
            else if(fox == rab && currentFoxPercent >= percent) { std::wcout << L"\t\u2588"; }
            else if(fox < rab && currentFoxPercent >= percent) { std::wcout << L"\t\u2588"; }
            else { std::wcout << "\t"; }

            if (fox < rab && currentRabPercent >= percent) { std::wcout << L"\t \u2588\n"; }
            else if (fox == rab && currentRabPercent >= percent) { std::wcout << L"\t \u2588\n"; }
            else if (fox > rab && currentRabPercent >= percent) { std::wcout << L"\t \u2588\n"; }
            else { std::wcout << "\t\n"; }
        }
        
        std::wcout << "\n       " << currentFoxPercent << "%\t" << currentRabPercent << "%\n";
        std::wcout << "\n       Fox\tRabbit\n" << std::endl;
        //-----------------------------------------------------------------------------------


        std::wcout << fox;
        std::wcout << rab;

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 100 millisecond delay
    }

    // Algorithm Library
    std::vector<double>::iterator foxMin = std::min_element(foxVector.begin(), foxVector.end());
    std::wcout << "\nSmallest fox population: " << *foxMin << std::endl;

    std::vector<double>::iterator rabMin = std::min_element(rabVector.begin(), rabVector.end());
    std::wcout << "Smallest rabbit population: " << *rabMin << std::endl;
    //------------------
    
    if (!isLoadFile) {
        Simulation::saveSimulation(foxPopulation, rabbitPopulation, simulationTime);
        Simulation::saveLogFile(foxVector, rabVector);
    }
    system("pause");
}

void Simulation::saveSimulation(double foxPopulation, double rabbitPopulation, double simulationTime) {
    try {
        std::ofstream file("savefile.txt", std::ofstream::app);

        file.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);

        if (file.is_open()) {
            file << foxPopulation << " " << rabbitPopulation << " " << simulationTime << "\n";
            file.close();
        }
    }
    catch (std::exception const& e) {
        std::wcout << "Error: " << e.what() << std::endl;
        system("pause");
    }
}


void Simulation::saveLogFile(std::vector<double> foxVector, std::vector<double> rabVector) {
    try {
        std::ofstream file("fhlogfile.txt", std::ofstream::out);

        file.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);

        if (file.is_open()) {
            for (int i = 0; i < foxVector.size(); i++) {
                file << "Fox Population: " << foxVector[i] << "\nRabbit Population: " << rabVector[i] << "\n";
            }
            file.close();
        }
    }
    catch (std::exception const& e) {
        std::wcout << "Error: " << e.what() << std::endl;
        system("pause");
    }
}

void Simulation::loadSimulation() {
    int count = 0;
    std::string throwAwayLine;
    double foxPopulation = 0, rabbitPopulation = 0, simulationTime = 0;
    try {
        std::ifstream file("savefile.txt", std::ifstream::in);
        std::istream fileData(file.rdbuf());

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        if (file.is_open()) {
            while (file.peek() != EOF)
            {
                getline(file, throwAwayLine);
                count++;
            }

            file.seekg(0);
            for (int i = 0; i < count; i++) {
                fileData >> foxPopulation >> rabbitPopulation >> simulationTime;
            }
            
            file.close();
            Simulation::startSimulation(foxPopulation, rabbitPopulation, simulationTime, true);
        }
    }
    catch (std::exception const& e) {
        std::wcout << "Error: " << e.what() << std::endl;
        system("pause");
    }
}