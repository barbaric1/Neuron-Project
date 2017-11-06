#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <array>

class Neuron {
	
	private:
	
	std::vector<unsigned int> spikesTime;
	double membranePotential;
	unsigned int neuronTime;
	unsigned int absoluteTime;
	double current;
	bool neuronIsRefractory;
	std::vector<double> spikesMembranePot;
	std::vector<Neuron*> target;  //bohhh//
	std::vector<int> buffer;
	unsigned int bufferCounter;
	int neuronWaiting;
	
	
	public:
	
	Neuron();
	~Neuron();
	void update();
	void setMembranePot(double m);
	double getMembranePot();
	unsigned int getNumberOfSpikes();
	void storeSpikesMembraneAndTime();
	void setCurrent(double c);
	double getCurrent();
	void setNeuronIsRefractory(bool a);
	bool getNeuronIsRefractory();
	unsigned int getNeuronTime();
	void setNeuronTime(unsigned int t);
	void receive();
	void addTarget(Neuron* neuron);
	std::vector<Neuron*> getTarget();
};




#endif
