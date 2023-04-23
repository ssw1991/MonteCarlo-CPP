#ifndef MC_CPP
#define MC_CPP

#include "MC.h"
#include <iostream>

using std::shared_ptr;

template<typename Sde, typename Fdm, typename RNG, typename Pricer>
void MCMediator<Sde,Fdm, RNG, Pricer>::start() {

	double vOld, vNew;
	for (int i = 1; i <= NSim; i++) {
		vOld = sde->InitialCondition(); 

		if ((i % 10000) == 0) {
			std::cout << i << " / " << NSim << std::endl;
		}

		for (std::size_t n = 1; n < res.size(); n++) {
			vNew = fdm->advance(vOld, fdm->x[n - 1], fdm->k, rng->GenerateRn(), rng->GenerateRn());
			res[n] = vNew; vOld = vNew;

		}
		pricer->ProcessPath(res);
		pricer->PostProcess();
	}
}

template<typename Sde, typename Fdm, typename RNG, typename Pricer>
MCMediator<Sde, Fdm, RNG, Pricer>::MCMediator(const std::shared_ptr<Sde>& s, 
	const shared_ptr<Fdm>& f, const shared_ptr<RNG>& r, const shared_ptr<Pricer>& p, int n, int NT) 
: sde(s), fdm(f), rng(r), pricer(p) {
	NSim = n;
	res = std::vector<double>(NT + 1);
}


#endif

