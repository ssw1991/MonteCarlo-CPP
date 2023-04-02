#ifndef MODEL_H
#define MODEL_H

#include <random>

class BaseModel {
private:
	std::mt19937 rng;
	double mean;
	double sigma;

public:
	BaseModel();
	BaseModel(double mean, double sigma);
	double next();
	double evaluate(double inp);
};

#endif