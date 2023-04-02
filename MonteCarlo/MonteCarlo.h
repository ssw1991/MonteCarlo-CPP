// MonteCarlo.h : Include file for standard system include files,
// or project specific include files.

#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <iostream>
#include "Model.h"

template<typename Model>
class MonteCarlo{
private:
	Model model;

public:

	MonteCarlo(Model &m);
	double run(int nsim=100);
	//double run_to_tol(double tol, int max_sim)
};

#endif