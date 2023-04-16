# MonteCarlo-CPP

This project is designed to imlpement MonteCarlo.  Starting from very simple, then extending the class heirarchy to build an extendable framework for running a variety of different simulations and schemes

At its base Monte Carlo is a numerical method providing the integration of functions.

## Initial Commit

This is a simple implementations.

- MonteCarlo
  - Initialized with a model
  - Runs the model over number of simulation and returns the  average
- Model
  - So far assumed to be gaussian
  - Has a next function to get the next random variable
  - An evaluate function.  In many cases this will be simply identity.  However, for more complex models this may require a transformation (for example an SDE scheme, or option payoff).
  
## Second Session
Here I made the MonteCarlo object take a template, with any model as the template parameter.  This allows us to use and self created class as long as it has a run and evaluate function.  In the future, and Concept will be used to ensure this is caught at compile time rather than run time.

Future progress will be generalizing the model through templates.  To integrate a specific distribution, we would just form the BaseModel over a rng of a specific distribution.  Additional enhancments will need to address the fact that evaluate may rely on a path, not just a double.  I will also properly fix the classes to reflect best practices.  


## Third Session

Implemented the scheme as presented here, written by Daniel Duffy. https://onlinelibrary.wiley.com/doi/epdf/10.1002/wilm.10647.  Will extend from here.

## Fourth Session

Extended pricers to implement European style Barrier options, in two ways.  One useing inheritance.  This required alot of duplication of code.  Though is pretty readable.  However in each class that would be written, the only difference is the activation function.  To simplify this, we have a single barrier option class, that can simply be initalized with an activation function object. We then implement the respective functions.  This can be further simplified by having a single function with signature bool (std::vector<double> arr, double barrier, bool intial, enum direction).  This function can then set the inital condition, loop through the array.  A switch statement off of the enum can determine the operation (<=, or >=) and toggle the return. The activation function can then be created by using std::partial and binding the initial condition, and the enum.  This is also now at the point where a builder can be constructed, as we can price the following
- European Call
- European Put
- Down and out Call
- Down and out Put
- Down and in Call
- Down and in Put
- Up and out Call
- Up and out Put
- Up and in Call
- Up and in Put

