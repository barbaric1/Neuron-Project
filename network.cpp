#include "network.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

const int NUMBER_NEURONS = 12500;
const int NUMBER_NEURONS_CONNECTED = 0.8 * NUMBER_NEURONS;
const int NUMBER_NEURONS_CONNECTED_EXCITATORY = 0.1 * NUMBER_NEURONS_CONNECTED;
const int NUMBER_NEURONS_CONNECTED_INHIBITORY = 0.25 * NUMBER_NEURONS_CONNECTED_EXCITATORY;


Network::Network()
: network(0), spikesTimeOfNeuron(0) {}

Network::~Network() {}

void Network::createNetwork()
{
	random_device rd;
	mt19937 gen;
	uniform_int_distribution<> I(0, 2449);
	uniform_int_distribution<> E(2500,12499);
	
	
	
	
	
	for (unsigned int i(0); i < NUMBER_NEURONS; ++i)
	{
		network.push_back(new Neuron());
		
		if ( i < NUMBER_NEURONS_CONNECTED)
		{
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
			
			network[i]->update();
			
			if (network[i]->getNeuronIsRefractory() == true)
			{
				++network[i]->getSpikesTime()[clock];
				for(auto target : network[i]->getTarget())
				{
					
					if (network[i]->getInhibitoryState() == false)
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
	
	for(unsigned int k(0); k < NUMBER_NEURONS; ++k)
	{
		spikesTimeOfNeuron.push_back(network[k]->getSpikesTime());
	}
	
}

void Network::textSpikesTime()
{
	ofstream paperella;
	paperella.open("spikesTime.txt");
	
	for(unsigned int i(0); i < getSpikesTime().size(); ++i)
	{
		paperella << i << ", " << spikesTime[i] << endl;
	}
	
	paperella.close();
}

void Network::textSpikesTimeOfNeuron()
{
	ofstream sbriciolona;
	sbriciolona.open("spikesTimeOfNeuron.txt");
	
	for(unsigned int i(0); i < spikesTimeOfNeuron.size(); ++i)
	{
		for(unsigned int k(0); k < spikesTimeOfNeuron[i].size(); ++k)
		{
			sbriciolona << i << ", " << spikesTimeOfNeuron[i][k] << endl;
		}
	}
	
	
	sbriciolona.close();
}
	
	
	
	
