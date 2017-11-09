#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron {
	
	private:
	
	double membranePotential;
	double current;
	bool neuronIsRefractory;
	int neuronWaiting;
	std::vector<int> buffer;
	unsigned int bufferCounter;
	bool inhibitoryNeuron;
	std::vector<Neuron*> target;
	std::vector<unsigned int> spikesTime;
	
	
	
	public:
	
	Neuron();
	~Neuron();
	void update();
	void setMembranePot(double m);
	double getMembranePot();
	void setCurrent(double c);
	double getCurrent();
	void setNeuronIsRefractory(bool a);
	bool getNeuronIsRefractory();
	void receive();
	void receiveNeg();
	void addTarget(Neuron* neuron);
	std::vector<Neuron*> getTarget();
	void setInhibitoryState(bool i);
	bool getInhibitoryState();
	std::vector<unsigned int> getSpikesTime();
	
	
	
	
	
	
};




#endif
