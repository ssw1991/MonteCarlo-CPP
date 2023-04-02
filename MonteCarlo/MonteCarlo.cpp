
#ifndef MONTECARLO_CPP
#define MONTECARLO_CPP

#include "MonteCarlo.h"
#include "Model.h"
#include <iostream>
#include<stdlib.h>

template<typename Model> MonteCarlo<Model>::MonteCarlo(Model &m){
	model = m;
}

template<typename Model> double MonteCarlo<Model>::run(int nsim) {
	double val = 0;
	for (int i = 0; i < nsim; i++) {

		val += model.evaluate(model.next());
	}
	return val / nsim;
}

template<typename Model> double MonteCarlo<Model>::run_to_tol(double tol, int max_sim) {
	
	double prev_val = model.evaluate(model.next());
	double curr_val = model.evaluate(model.next());

	int num_sim = 2; //Already did two simulations
	std::cout << curr_val / (num_sim)-prev_val / (num_sim - 1) << " " << curr_val << " " << prev_val << " " << num_sim << std::endl;
	
	while ((abs(curr_val / num_sim-prev_val /(num_sim - 1)) >= tol) && (num_sim < max_sim)) {
		prev_val = curr_val;
		curr_val += model.evaluate(model.next());
		std::cout << curr_val / (num_sim)-prev_val / (num_sim - 1) << " " << curr_val << " " << prev_val << std::endl;
		num_sim++;
	}
	std::cout << "Num sim: " << num_sim << std::endl;
	return curr_val / num_sim;
}

#endif