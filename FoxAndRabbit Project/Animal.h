#pragma once

class Animal {
public:
	virtual double findRateOfChange(double population) const = 0;
	virtual void newPopulationSize(double rate) = 0;
};
