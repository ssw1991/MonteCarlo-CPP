


#include "MonteCarlo.h"
#include "Model.h"


MonteCarlo::MonteCarlo(Model &m){
	model = m;
}

double MonteCarlo::run(int nsim) {
	double val = 0;
	for (int i = 0; i < nsim; i++) {

		val += model.evaluate(model.next());
	}
	return val / nsim;
}