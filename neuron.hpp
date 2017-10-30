#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron {
	
	private:
	
	std::vector<unsigned int> spikesTime;
	double membranePotential;
	unsigned int neuronTime;
	double current;
	bool neuronIsRefractory;
	std::vector<double> spikesMembranePot;
	
	
	public:
	
	void update(unsigned int stopTime);
	void setMembranePot(double m);
	double getMembranePot();
	unsigned int getNumberOfSpikes();
	void storeSpikesMembraneAndTime();
	void setCurrent(double c);
	double getCurrent();
	void setNeuronIsRefractory(bool a);
	unsigned int getNeuronTime();
	void setNeuronTime(unsigned int t);
	
	
	
	
	
	
};




#endif
