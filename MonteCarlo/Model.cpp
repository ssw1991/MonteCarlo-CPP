#include "Model.h"
#include <iostream>
#include <random>

BaseModel::BaseModel() {
	mean = 0.0;
	sigma = 1.0;
	std::random_device rd{};
	rng = std::mt19937(rd());
}

BaseModel::BaseModel(double _mean, double _sigma) {

	mean = _mean;
	sigma = _sigma;
	std::random_device rd{};
	rng = std::mt19937(rd());
}

double BaseModel::next() {
	return std::normal_distribution<>(mean, sigma)(rng);
}

double BaseModel::evaluate(double inp) {return inp;};