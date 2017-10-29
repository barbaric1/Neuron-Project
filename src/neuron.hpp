#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron {
	
	private:
	
	std::vector<unsigned int> spikesTime;
	std::double membranePotential;
	std::unsigned int neuronTime;
	std::double current;
	std::bool neuronIsRefractory;
	std::vector<double> spikesMembranePot;
	
	public:
	
	std::void update(unsigned int stopTime, double curr);
	std::void setMembranePot(double m);
	std::double getMembranePot();
	std::unsigned int getNumberOfSpikes();
	std::void storeSpikesMembrane&Time();
	std::void setCurrent(double c);
	std::double getCurrent();
	
	
	
	
	
	
};




#endif
