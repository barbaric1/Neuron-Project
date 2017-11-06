#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <array>

class Neuron {
	
	private:
	
	double membranePotential;
	double current;
	bool neuronIsRefractory;
	std::vector<double> spikesMembranePot;
	int neuronWaiting;
	std::vector<int> buffer;
	unsigned int bufferCounter;
	bool inhibitoryNeuron;
	std::vector<Neuron*> target;
	
	
	
	
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
	
	
	
	
	
};




#endif
