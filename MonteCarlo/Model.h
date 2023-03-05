#ifndef MODEL_H
#define MODEL_H

#include <random>

class Model {
private:
	std::mt19937 rng;
	double mean;
	double sigma;

public:
	Model();
	Model(double mean, double sigma);
	double next();
	double evaluate(double inp);
};

#endif