
#ifndef MONTECARLO_CPP
#define MONTECARLO_CPP

#include "MonteCarlo.h"
#include "Model.h"


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

#endif