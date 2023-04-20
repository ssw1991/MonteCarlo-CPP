#ifndef SDE_HPP
#define SDE_HPP

class GBM { // Simple SDE
private:
	double mu;       // Drift
	double vol;      // Constant volatility
	double d;        // Constant dividend yield
	double ic;       // Initial condition
	double exp;      // Expiry

public:
	GBM() = default;

	GBM(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition, double expiry) {
		mu = driftCoefficient;
		vol = diffusionCoefficient;
		d = dividendYield;
		ic = initialCondition;
		exp = expiry;
	}

	double Drift(double x, double t) { 
		return (mu - d) * x; 
	}

	double Diffusion(double x, double t) {
		return vol * x; 
	}
	
	double DriftCorrected(double x, double t, double B) {
		return Drift(x, t) - B * Diffusion(x, t)*DiffusionDerivative(x, t);
	}

	double DiffusionDerivative(double x, double t) {
		return vol;
	}

	double InitialCondition() const {return ic;}
	
	// Property to set/get time T
	double Expiry() const {
		return exp;
	}
};


#endif