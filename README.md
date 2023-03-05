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
  
