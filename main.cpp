#include "neuron.hpp"
#include <iostream>

using namespace std;

int main ()
{
	
	
	unsigned int clock(0);
	unsigned int stopTime(100000);
	Neuron a;
	Neuron b;
	
	a.setInhibitoryState(true);
	b.setInhibitoryState(false);
	vector<Neuron*> neurons(0);
	
	neurons.push_back(&a);
	neurons.push_back(&b);
	
	a.addTarget(&b);
	b.addTarget(&a);
	
	do
	{
		
		for(auto neuron : neurons)
		{
			if (neuron ==nullptr) { cout<< "fuck"<< endl; }
			neuron->update();
			
			if (neuron->getNeuronIsRefractory() == true)
			{
				for(auto target : neuron->getTarget())
				{
					if (target ==nullptr) { cout<< "fucktarget"<< endl; }
					
					if (neuron->getInhibitoryState() == false)
					{
					
					target->receive();
					
					}
					
					else
					{
						target->receiveNeg();
						
										
					}
				
					
				}
				
			}
		}
			
		clock += 1;
		
	} while(clock < stopTime);
	


return 0;

}
