# MonteCarlo-CPP

This project is designed to imlpement MonteCarlo.  Starting from very simple, then extending the class heirarchy to build an extendable framework for running a variety of different simulations and schemes

At its base Monte Carlo is a numerical method providing the integration of functions.

## Initial Commit

This is a simple implementations.

-MonteCarlo
  - Initialized with a model
  - Runs the model over number of simulation and returns the  average
- Model
  - So far assumed to be gaussian
  - Has a next function to get the next random variable
  - An evaluate function.  In many cases this will be simply identity.  However, for more complex models this may require a transformation (for example an SDE scheme, or option payoff).
  
## Second Session
Here I made the MonteCarlo object take a template, with any model as the template parameter.  This allows us to use and self created class as long as it has a run and evaluate function.  In the future, and Concept will be used to ensure this is caught at compile time rather than run time.

Future progress will be generalizing the model through templates.  To integrate a specific distribution, we would just form the BaseModel over a rng of a specific distribution.  Additional enhancments will need to address the fact that evaluate may rely on a path, not just a double.  I will also properly fix the classes to reflect best practices.  
