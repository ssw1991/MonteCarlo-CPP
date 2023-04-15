#ifndef PRICER_HPP
#define PRICER_HPP


#include<functional>

class PricerBase{
public:
	// Create a single path
	virtual void ProcessPath(const std::vector<double>& arr) = 0;
	// Notify end of simulation
	virtual void PostProcess() = 0;
	// Discounting, should be a delegate/signal
	virtual double DiscountFactor() = 0;
	// Option price
	virtual double Price() = 0;
	std::function<double(double)> m_payoff;
	std::function<double()> m_discounter;
	PricerBase() = default;
	PricerBase(const std::function<double(double)>& payoff,
		const std::function<double()>& discounter)
	{
		m_payoff = payoff;
		m_discounter = discounter;
	}
};

// Pricing Engines 
class EuropeanPricer: public PricerBase{
private:
	double price;
	double sum, NSim;
public:
	EuropeanPricer() = default;
	  EuropeanPricer(const std::function<double(double)>& payoff, const std::function<double()>& discounter) : PricerBase(payoff, discounter) {
		  price = sum = 0.0; NSim = 0;
	  }
	  void ProcessPath(const std::vector<double>& arr) override {
		  // A path for each simulation/draw// Sum of option values at terminal time T
		  sum += m_payoff(arr[arr.size() - 1]); NSim++;
	  }
	  double DiscountFactor() override {
		  // Discounting
		  return m_discounter();
	  }
	  void PostProcess() override {
		  price = DiscountFactor() * sum / NSim;
	  }
	  double Price() override {
		  return price; 
	  }
};

#endif