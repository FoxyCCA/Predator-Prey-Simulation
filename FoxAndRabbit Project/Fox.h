#pragma once
#include "Animal.h"
#include <fstream>

class Fox : public Animal {
private:
	double foxPopulation = 0;
	const float foxBirthRate = 0.001f, foxDeathRate = 0.5f;
public:
	Fox();
	Fox(double foxPopulation);

	double getFoxPopulation();
	void setFoxPopulation(double foxPopulation);
	
	double findRateOfChange(double population) const override;

	void newPopulationSize(double rate) override;

	friend std::wostream& operator <<(std::wostream& out, Fox& fox);
};