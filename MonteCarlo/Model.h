#ifndef MODEL_H
#define MODEL_H

#include <random>
#include <iostream>

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


class PosModel: public BaseModel {
private:
	double lim;
public:
	PosModel() :BaseModel::BaseModel() { lim = 0.0; };

	PosModel(double mean, double sigma, double _lim) :BaseModel::BaseModel(mean, sigma) {
		lim = _lim;
	}
	double evaluate(double inp) {
		std::cout << lim << "  HERE" << std::endl;
		return (lim < inp) ? inp : 0.0;
	}
};
#endif