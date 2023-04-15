
#include "Pricer.h"
#include "SDE.h"
#include "FDM.h"
#include "MC.cpp"
#include <memory>
#include "RNG.h"
#include <functional>
#include <iostream>


int main() {
	int NSim = 1'000'000; 
	int NT = 500; 
	double driftCoefficient = 0.08; 
	double diffusionCoefficient = 0.3; 
	double dividendYield = 0.0; 
	double initialCondition = 60.0; 
	double expiry = 1; 
	std::shared_ptr<GBM> sde = std::shared_ptr<GBM>(new GBM(driftCoefficient, diffusionCoefficient, dividendYield, initialCondition, expiry)); 
	double K = 60.0;


	std::function<double(double)> payoffCall = [&K](double x)
		{return std::max<double>(0.0, x - K); };
	double r = 0.08; 
	double T = 0.25;
	std::function<double()> discounter = [&r, &T]() 
	{ return std::exp(-r * T); };
	
	std::shared_ptr<EuropeanPricer> pricerCall = std::shared_ptr<EuropeanPricer>(new EuropeanPricer(payoffCall, discounter));

	std::shared_ptr<EulerFdm<GBM>> fdm = std::shared_ptr<EulerFdm<GBM>> (new EulerFdm<GBM>(sde, NT));
	std::shared_ptr<CPPRng> rngCPP = std::shared_ptr<CPPRng>(new CPPRng());
	
	MCMediator<GBM, EulerFdm<GBM>, CPPRng, EuropeanPricer> s2(sde, fdm, rngCPP, pricerCall, NSim, NT);
	s2.start();
	std::cout << "\n Call Price: " << pricerCall->Price();
	return 0;
}