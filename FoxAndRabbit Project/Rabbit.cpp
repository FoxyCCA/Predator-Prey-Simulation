#include "Rabbit.h"
#include <iostream>

Rabbit::Rabbit() {}
Rabbit::Rabbit(double rabbitPopulation) { this->rabbitPopulation = rabbitPopulation; }

double Rabbit::getRabbitPopulation() { return this->rabbitPopulation; }
void Rabbit::setRabbitPopulation(double rabbitPopulation) { this->rabbitPopulation = rabbitPopulation; }

double Rabbit::findRateOfChange(double population) const {
	return (rabbitBirthRate * this->rabbitPopulation) - (rabbitDeathRate * this->rabbitPopulation * population);
}

void Rabbit::newPopulationSize(double rate) {
	this->rabbitPopulation = this->rabbitPopulation + 0.1f * rate;
}

std::wostream& operator <<(std::wostream& out, Rabbit& rab) {
	return out << "Rabbit Population: " << rab.rabbitPopulation << std::endl;
}
