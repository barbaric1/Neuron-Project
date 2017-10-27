#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron {
	
	private:
	
	std::vector<unsigned int> spikes;
	std::double membranePotential;
	std::unsigned int neuronTime;
	std::double current;
	std::bool neuronIsRefractory;
	
	public:
	
	std::vector<unsigned int> update(unsigned int stopTime);
	
	
	
	
	
	
};




#endif
