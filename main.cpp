#include "network.hpp"
#include "neuron.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
	
	Network neuronNetwork;
	
	neuronNetwork.createNetwork();
	
	neuronNetwork.runSimulation(10000);
	


return 0;

}
