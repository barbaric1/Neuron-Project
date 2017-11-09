#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include <vector>

class Network {
	
	
	private:
	
	std::vector<Neuron*> network;
	std::vector<std::vector<unsigned int>> spikesTimeOfNeuron;
	
	
	public:
	
	Network();
	~Network();
	
	void createNetwork();
	
	void runSimulation(unsigned int stopTime);
	
	void textSpikesTime();
	void textSpikesTimeOfNeuron()
	
	



};


#endif
