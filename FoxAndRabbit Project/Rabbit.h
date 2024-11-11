#pragma once
#include "Animal.h"
#include <fstream>

class Rabbit : public Animal {
private:
	double rabbitPopulation = 0;
	const float rabbitBirthRate = 0.2f, rabbitDeathRate = 0.001f;
public:
	Rabbit();
	Rabbit(double rabbitPopulation);

	double getRabbitPopulation();
	void setRabbitPopulation(double rabbitPopulation);
	
	double findRateOfChange(double population) const override;

	void newPopulationSize(double rate) override;

	friend std::wostream& operator <<(std::wostream& out, Rabbit& rab);
};