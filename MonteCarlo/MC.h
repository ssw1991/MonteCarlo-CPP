#ifndef MC_HPP
#define MC_HPP

#include <memory>
#include <vector>

using std::shared_ptr;

template<typename Sde, typename Fdm,typename RNG, typename Pricer>
class MCMediator : private Sde, private Fdm, private RNG, private Pricer {
private:
	shared_ptr<Sde> sde;
	shared_ptr<Fdm> fdm;
	shared_ptr<RNG> rng;
	shared_ptr<Pricer> pricer;

	int NSim;
	std::vector<double> res;

public:
	MCMediator() {};

	MCMediator(const shared_ptr<Sde>& s,
		const shared_ptr<Fdm>& f,
		const shared_ptr<RNG>& r,
		const shared_ptr<Pricer>& p, int n, int NT);
		
	void start();
};


#endif

