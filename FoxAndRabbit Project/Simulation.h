#pragma once
#include "Fox.h"
#include "Rabbit.h"
#include <vector>

class Simulation {
public:
	void startSimulation(double foxPopulation, double rabbitPopulation, double simulationTime, bool isLoadFile = false);
	void saveSimulation(double foxPopulation, double rabbitPopulation, double simulationTime);
	void saveLogFile(std::vector<double> foxVector, std::vector<double> rabVector);
	void loadSimulation();
};