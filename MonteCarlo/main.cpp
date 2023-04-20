
#include "Pricer.h"
#include "SDE.h"
#include "FDM.h"
#include "MC.cpp"
#include <memory>
#include "RNG.h"
#include <functional>
#include <iostream>

using std::shared_ptr;

int main() {
	const int NSim = 1'000'000; 
	const int NT = 500; 

	double driftCoefficient = 0.0; 
	double diffusionCoefficient = 0.3; 
	double dividendYield = 0.0; 
	double initialCondition = 60.0; 
	double expiry = 1; 

	shared_ptr<GBM> sde = shared_ptr<GBM>(new GBM(driftCoefficient, diffusionCoefficient, dividendYield, initialCondition, expiry)); 
	double K = 60.0;

	std::function<double(double)> payoffCall = [&K](double x)
		{return std::max<double>(0.0, x - K); };

	std::function<double(double)> payoffPut = [&K](double x)
		{return std::max<double>(0.0, K - x); };

	double r = 0.08; 
	double T = 1;
	std::function<double()> discounter = [&r, &T]() 
		{ return std::exp(-r * T); };
	
	shared_ptr<EuropeanPricer> pricerCall = shared_ptr<EuropeanPricer>(new EuropeanPricer(payoffCall, discounter));

	shared_ptr<EulerFdm<GBM>> fdm = shared_ptr<EulerFdm<GBM>> (new EulerFdm<GBM>(sde, NT));
	shared_ptr<CPPRng> rngCPP = shared_ptr<CPPRng>(new CPPRng());
	
	MCMediator<GBM, EulerFdm<GBM>, CPPRng, EuropeanPricer> s2(sde, fdm, rngCPP, pricerCall, NSim, NT);
	s2.start();
	std::cout << "\n Call Price: " << pricerCall->Price() << std::endl;

	shared_ptr<DownAndInPricer> PricerDownAndInPut = 
		shared_ptr<DownAndInPricer>(new DownAndInPricer(payoffPut, discounter, 55.0));
	MCMediator<GBM, EulerFdm<GBM>, CPPRng, DownAndInPricer> s(sde, fdm, rngCPP, PricerDownAndInPut, NSim, NT);
	s.start();
	std::cout << "Down and In put Price: " << PricerDownAndInPut->Price() << std::endl; 

	shared_ptr<BarrierPricerFunctional> PricerDownAndInPutFunctional = 
		shared_ptr<BarrierPricerFunctional>(new BarrierPricerFunctional(payoffPut, discounter, 55.0, down_and_in));
	MCMediator<GBM, EulerFdm<GBM>, CPPRng, BarrierPricerFunctional> s3(sde, fdm, rngCPP, PricerDownAndInPutFunctional, NSim, NT);
	s3.start();
	std::cout << "Down and In put Price with functional approach: " << PricerDownAndInPut->Price() << std::endl;

	std::function<bool(const std::vector<double>&, double)> myDownIn = 
		std::bind(activation, std::placeholders::_1, std::placeholders::_2, Direction::DOWN, false);
	shared_ptr<BarrierPricerFunctional> PricerDownAndInPutFunctionalEnum = 
		shared_ptr<BarrierPricerFunctional>(new BarrierPricerFunctional(payoffPut, discounter, 55.0, myDownIn));
	MCMediator<GBM, EulerFdm<GBM>, CPPRng, BarrierPricerFunctional> s4(sde, fdm, rngCPP, PricerDownAndInPutFunctionalEnum, NSim, NT);
	s4.start();
	std::cout << "Down and In put Price with functional approach: " << PricerDownAndInPut->Price() << std::endl;

	return 0;
}