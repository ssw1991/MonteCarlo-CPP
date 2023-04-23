#ifndef RNG_HPP
#define RNG_HPP

#include <random>
class Rng {
public:
	virtual double GenerateRn() = 0;
};

class CPPRng : public Rng {
private:
	std::default_random_engine dre;
	std::normal_distribution<double> nor;

public:
	CPPRng() : dre(std::default_random_engine()),nor(std::normal_distribution<double>(0.0, 1.0)) {}
	
	double GenerateRn() override {
		return nor(dre);
	}
};

#endif