#include "neuron.hpp"
#include <iostream>

using namespace std;

int main ()
{
	unsigned int clock(0);
	unsigned int stopTime(10);
	Neuron a;
	Neuron b;
	
	vector<Neuron*> neurons;
	
	neurons.push_back(&a);
	neurons.push_back(&b);
	
	a.addTarget(&b);
	
	do
	{
		
		for(auto neuron : neurons)
		{
			neuron->update();
			
			if (neuron->getNeuronIsRefractory() == true)
			{
				for(auto target : neuron->getTarget())
				{
					target->receive();
				}
			}
		}
			
		clock += 1;
		
	} while(clock < stopTime);
	


return 0;

}
