// main.cpp : Defines the entry point for the application.
//


#include "MonteCarlo.cpp"
#include "Model.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	BaseModel myModel = BaseModel(0.0, 1.0);
	MonteCarlo<BaseModel> simulation = MonteCarlo(myModel);
	
	cout << simulation.run(10'000) << endl;
	return 0;
}
