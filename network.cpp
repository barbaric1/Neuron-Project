#include "network.hpp"
#include <iostream>
#include <vector>
#include <random>  
#include <fstream>
#include <cassert> 

using namespace std;

const int NUMBER_NEURONS = 12500;
const int NUMBER_NEURONS_CONNECTED = 0.8 * NUMBER_NEURONS;
const int NUMBER_NEURONS_CONNECTED_EXCITATORY = 0.1 * NUMBER_NEURONS_CONNECTED;
const int NUMBER_NEURONS_CONNECTED_INHIBITORY = 0.25 * NUMBER_NEURONS_CONNECTED_EXCITATORY;


Network::Network()
: network(0), spikesTimeOfNeuron(12500), spikeTime(12000,0) {}


void Network::createNetwork()
{
	/** Helps to randomly chose which Neuron in the various targets vectors will be excitatory or inhibitory.
	 **/
	
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_int_distribution<> I(NUMBER_NEURONS_CONNECTED, NUMBER_NEURONS - 1);
	static uniform_int_distribution<> E(0,NUMBER_NEURONS_CONNECTED - 1);
	
	
	
	for (unsigned int i(0); i < NUMBER_NEURONS; ++i)
	{
		network.push_back(new Neuron());
		
		if ( i < NUMBER_NEURONS_CONNECTED)
		{
			/** This assert will let us avoid  Segmentations Faults in case that our pointer to a Neuron that we want to add to the network
			 * is queal to nullptr.
			 * I chosed that the first 10000 Neurons of the Network will be excitatory, the rest inhibitory.
			 **/
			
			assert(network[i] != nullptr);
			network[i]->setInhibitoryState(false);
		}
	}
		
	for (unsigned int i(0); i < NUMBER_NEURONS; ++i)
	{
		for (unsigned int k(0); k < NUMBER_NEURONS_CONNECTED_INHIBITORY; ++k)
		{
			network[I(gen)]->addTarget(network[i]);
		}
		
		for (unsigned int w(0); w < NUMBER_NEURONS_CONNECTED_EXCITATORY; ++w)
		{
			network[E(gen)]->addTarget(network[i]);
		}
	}
}


void Network::runSimulation(unsigned int stopTime)
{
	
	
	unsigned int clock(0);
	do
	{
		
		for(unsigned int i(0); i < NUMBER_NEURONS; ++i)
		{ 
			
			/** Protectes from Segmentations Faults.
			 **/
			
			assert(network[i] != nullptr);
			
			network[i]->update();
			
			if (network[i]->getNeuronIsRefractory() == true)
			{
				
				/** Every time that a Neuron spikes, this two lines will write in the two vectors that we need for the graphs.
				 **/
				
				++spikeTime[clock];
				spikesTimeOfNeuron[i].push_back(clock);
				
				for(auto target : network[i]->getTarget())
				{
					
					/** For each Neuron that spikes, it sends (depending of the type of Neuron) a signal to each target Neuron, with
					 * correct delay
					 **/
					
					if (network[i]->getInhibitoryState() == false)
					{
					
					target->receive(network[i]->getBufferTime());
					
					}
					
					else
					{
					
					target->receiveNeg(network[i]->getBufferTime());
						
					}
				
				}
			}
		}
			
		clock += 1;		
		
	} while(clock < stopTime);
	
}

void Network::textSpikesTime()
{
	ofstream paperella;
	paperella.open("spikesTime.txt");
	
	int t(0);
	
	for(auto spike_nbr : spikeTime)
	{
		
		
		paperella << t << ", " << spike_nbr << endl;
		
		++t;
	}
	
	paperella.close();
}

void Network::textSpikesTimeOfNeuron()
{
	ofstream sbriciolona;
	sbriciolona.open("spikesTimeOfNeuron.txt");
	
	int j(0);
	
	for(auto neur : spikesTimeOfNeuron)
	{
		
		for(auto spike_nbr : neur)
		{
		
		
		sbriciolona << spike_nbr<< ", " << j << endl;
		}
		++j;
	}
	
	
	sbriciolona.close();
}
	
	
	
	
