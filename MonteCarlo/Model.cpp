#include "Model.h"
#include <iostream>
#include <random>

Model::Model() {
	mean = 0.0;
	sigma = 1.0;
	std::random_device rd{};
	rng = std::mt19937(rd());
}

Model::Model(double _mean, double _sigma) {

	mean = _mean;
	sigma = _sigma;
	std::random_device rd{};
	rng = std::mt19937(rd());
}

double Model::next() {
	return std::normal_distribution<>(mean, sigma)(rng);
}

double Model::evaluate(double inp) {return inp;};