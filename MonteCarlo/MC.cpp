#ifndef MC_CPP
#define MC_CPP

#include "MC.h"
#include <iostream>

template<typename Sde, typename Fdm, typename RNG, typename Pricer>
void MCMediator<Sde,Fdm, RNG, Pricer>::start() {

	double Vold, Vnew;
	for (int i = 1; i <= NSim; i++) {
		Vold = sde->InitialCondition(); // Why is this in the loop

		if ((i / 10000) * 10000 == i) {
			std::cout << i << std::endl;
		}

		for (std::size_t n = 1; n < res.size(); n++)
		{
			Vnew = fdm->advance(Vold, fdm->x[n - 1], fdm->k, rng->GenerateRn(), rng->GenerateRn());
			res[n] = Vnew; Vold = Vnew;

		}
		pricer->ProcessPath(res);
		pricer->PostProcess();
	}
}

template<typename Sde, typename Fdm, typename RNG, typename Pricer>
MCMediator<Sde, Fdm, RNG, Pricer>::MCMediator(const std::shared_ptr<Sde>& s,
	const std::shared_ptr<Fdm>& f,
	const std::shared_ptr<RNG>& r,
	const std::shared_ptr<Pricer>& p, int n, int NT) : sde(s), fdm(f), rng(r), pricer(p) {
			NSim = n;
			res = std::vector<double>(NT + 1);
}


#endif

