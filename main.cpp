#include "network.hpp"
#include "neuron.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
	
	Network neuronNetwork;
	
	neuronNetwork.createNetwork();
	
	neuronNetwork.runSimulation(12000);
	
	neuronNetwork.textSpikesTime();
	
	neuronNetwork.textSpikesTimeOfNeuron();
	
	std::string out = "python pscript.py &";
	system( out.c_str());

	


return 0;

}
