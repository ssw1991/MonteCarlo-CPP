#ifndef PRICER_HPP
#define PRICER_HPP


#include<functional>
#include<algorithm>

class PricerBase {
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
		const std::function<double()>& discounter) {
		m_payoff = payoff;
		m_discounter = discounter;
	}
};

// Pricing Engines 
class EuropeanPricer: public PricerBase {
protected:
	double price;
	double sum, NSim;

public:
	EuropeanPricer() = default;

	EuropeanPricer(const std::function<double(double)>& payoff, const std::function<double()>& discounter) 
	: PricerBase(payoff, discounter) {
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

class BarrierPricer: public EuropeanPricer {
protected:
	double barrier;

public:
	BarrierPricer() = default;
	
	BarrierPricer(const std::function<double(double)>& payoff, 
		const std::function<double()>& discounter, const double b) 
	: EuropeanPricer(payoff, discounter) { barrier = b; }

	virtual bool is_active(const std::vector<double>& arr) = 0;

	void ProcessPath(const std::vector<double>& arr) override {
		if (is_active(arr)) { EuropeanPricer::ProcessPath(arr); }
		else { NSim++; }  // Simulation was not incremented if this block is hit
	}
};

class DownAndInPricer : public BarrierPricer {
public:
	DownAndInPricer() = default;

	DownAndInPricer(const std::function<double(double)>& payoff, 
		const std::function<double()>& discounter, const double b) 
	: BarrierPricer(payoff, discounter, b) {}

	virtual bool is_active(const std::vector<double>& arr) override {
		bool active = false;
		for (double val : arr) {
			if (val <= barrier) { active = true; break; }
		}
		return active;
	}

};

class BarrierPricerFunctional : public EuropeanPricer {
protected:
	double barrier; 

public:
	BarrierPricerFunctional() = default;

	BarrierPricerFunctional(const std::function<double(double)>& payoff, 
		const std::function<double()>& discounter, const double b, 
		const std::function<bool(const std::vector<double>&, double b)>& active) 
	: EuropeanPricer(payoff, discounter) { 
		is_active = active; 
		barrier = b; 
	}
	
	std::function<bool(const std::vector<double>&, double)> is_active;

	void ProcessPath(const std::vector<double>& arr) override {
		if (is_active(arr, barrier)) { EuropeanPricer::ProcessPath(arr); }
		else { NSim++; }  // Simulation was not incremented if this block is hit
	}

};


// Functions 

// Perhaps there is a way to generalize more elegantly 
bool down_and_in(const std::vector<double>& arr, double b) {
	bool active = false;
	for (double val : arr) {
		if (val <= b) { active = true; break; }
	}
	return active;
}

bool down_and_out(const std::vector<double>& arr, double b) {
	bool active = true;
	for (double val : arr) {
		if (val <= b) { active = false; break; }
	}
	return active;
}

bool up_and_in(const std::vector<double>& arr, double b) {
	bool active = false;
	for (double val : arr) {
		if (val >= b) { active = true; break; }
	}
	return active;
}

bool up_and_out(const std::vector<double>& arr, double b) {
	bool active = true;
	for (double val : arr) {
		if (val >= b) { active = false; break; }
	}
	return active;
}

enum Direction {
	UP,
	DOWN,
};

bool activation(const std::vector<double>& arr, double b, Direction d, bool init) {
	bool active = init;
	for (double val : arr) {

		switch (d) {
			case DOWN:
				if (val <= b) { active = !active; break; }
				break;
			case UP:
				if (val >= b) { active = !active; break; }
				break;
		}
	}
	return active;
}

#endif