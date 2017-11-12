#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include <vector>

class Network {
	
	
	private:
	
	std::vector<Neuron*> network;
	std::vector<std::vector<unsigned int>> spikesTimeOfNeuron;
	std::vector<unsigned int> spikeTime;
	
	
	public:
	
/** \brief A simple constructor for the Network class.
 *
 * Creates a new Network object and initializes all the parametres as needed for the start of the simulation.
 **/
	
	Network();
	
/** \brief Creates a neuron network.
 * 
 * Fills the simulation with the indicated amount of neurons, then decides which ones are inhibitory or excitatory.
 * The final step of this method consists increating the connections between neurons.
 **/
	
	void createNetwork();
	
/** \brief Runs the simulation of the whole neuron network.
 * \param stopTime: corresponds to the time that we want the simulation to run (not in ms, but in steps. One step = 0.1 ms).
 **/
	
	void runSimulation(unsigned int stopTime);
	
/**  \brief Serves only to write on a text that we will use to create a graph.
 * 
 * The graph that we will create in this case is the Spikes vs Time graph.
 **/
	
	void textSpikesTime();
	
/** \brief Serves only to write on a text that we will use to create a graph.
 * 
 * The graph that we will create in this case is the Spike for each neuron vs Time graph.
 **/
	
	void textSpikesTimeOfNeuron();
	
};

#endif
