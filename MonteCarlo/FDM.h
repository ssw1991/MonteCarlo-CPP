#ifndef FDM_HPP
#define FDM_HPP

#include <memory>

template<typename Sde>
class EulerFdm{
private:
	std::shared_ptr<Sde> sde; 
	int NT; 
public:
	std::vector<double> x;          // The mesh array
	double k;                      // Mesh size
	double dtSqrt;
	EulerFdm() = default;
	EulerFdm(const std::shared_ptr<Sde>& stochasticEquation, 
		int numSubdivisions): 
		sde(stochasticEquation), NT(numSubdivisions)
	{
		NT = numSubdivisions;
		k = sde->Expiry() / static_cast<double>(NT);
		dtSqrt = std::sqrt(k);
		x = std::vector<double>(NT + 1);
		
		// Create the mesh array
		x[0] = 0.0;
		for (std::size_t n = 1; n < x.size(); ++n)
		{
			x[n] = x[n - 1] + k;
		}
	}
	double advance(double xn, double tn, double dt, double normalVar, double normalVar2) const
	{
		return xn + sde->Drift(xn, tn) * dt + sde->Diffusion(xn, tn) * dtSqrt * normalVar;
	}
};

#endif FDM_HPP