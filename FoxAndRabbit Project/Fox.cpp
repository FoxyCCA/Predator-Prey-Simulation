#include "Fox.h"


Fox::Fox() {}
Fox::Fox(double foxPopulation) { this->foxPopulation = foxPopulation; }

double Fox::getFoxPopulation() { return this->foxPopulation; }

void Fox::setFoxPopulation(double foxPopulation) { this->foxPopulation = foxPopulation; }

double Fox::findRateOfChange(double population) const {
	return (foxBirthRate * population * this->foxPopulation) - (foxDeathRate * this->foxPopulation);
}

void Fox::newPopulationSize(double rate) {
	this->foxPopulation = this->foxPopulation + 0.1f * rate;
}

std::wostream& operator <<(std::wostream& out, Fox& fox) {
	return out << "Fox population: " << fox.foxPopulation << std::endl;
}