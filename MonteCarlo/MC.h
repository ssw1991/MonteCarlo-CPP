#ifndef MC_HPP
#define MC_HPP

#include <memory>
#include <vector>


template<typename Sde, typename Fdm,typename RNG, typename Pricer>
class MCMediator : private Sde, private Fdm, private RNG, private Pricer
{
private:
	std::shared_ptr<Sde> sde;
	std::shared_ptr<Fdm> fdm;
	std::shared_ptr<RNG> rng;
	std::shared_ptr<Pricer> pricer;

	int NSim;
	std::vector<double> res;

public:
	MCMediator() {};
	MCMediator(const std::shared_ptr<Sde>& s,
		const std::shared_ptr<Fdm>& f,
		const std::shared_ptr<RNG>& r,
		const std::shared_ptr<Pricer>& p, int n, int NT);
	void start();
};


#endif

