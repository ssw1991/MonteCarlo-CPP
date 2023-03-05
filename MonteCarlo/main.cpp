// main.cpp : Defines the entry point for the application.
//


#include "MonteCarlo.h"
#include "Model.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	Model myModel = Model(0.0, 1.0);
	MonteCarlo simulation = MonteCarlo(myModel);
	
	cout << simulation.run(10'000) << endl;
	return 0;
}
