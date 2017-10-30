#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

const double STANDARD_MEMBRANE_POT = 20;
const double REFRACTORY_TIME = 1.5;
const double MEMBRANE_TIME_CONSTANT_TAU = 20;
const double MEMBRANE_RESISTENCE = 20; 


void Neuron::update(unsigned int stopTime)
{
	setNeuronTime(0);
	setMembranePot(0);
	setNeuronIsRefractory(false);
	do
	{ if(getMembranePot() > STANDARD_MEMBRANE_POT)
		{
			spikesTime.push_back(neuronTime);
			setNeuronIsRefractory(true); 
			setMembranePot(0);
		}
		
		else if(neuronIsRefractory == true)
		{
	
			neuronTime += 15;
			setNeuronIsRefractory(false);
		}
		
		else
		{
			setMembranePot((exp((-1)*(0.1/MEMBRANE_TIME_CONSTANT_TAU))* getMembranePot()) + (getCurrent() * MEMBRANE_RESISTENCE * (1 - exp((-1)*(0.1/MEMBRANE_TIME_CONSTANT_TAU)))));  //qua bisognera aggiungere J e inoltre potrebbe volerci l'utilizzo di getter e setter. Anche R dovra cambiare molto probabilmente
			
		}
		spikesMembranePot.push_back(getMembranePot());
		neuronTime += 1;
		
		
	} while (getNeuronTime() < stopTime);
}

void Neuron::setMembranePot(double m)
{
	membranePotential = m;
}

double Neuron::getMembranePot()
{
	return membranePotential;
}

unsigned int Neuron::getNumberOfSpikes()
{
	return spikesTime.size();
}

void Neuron::storeSpikesMembraneAndTime() 
{
	cout << "Membrane Potential ********** Time(ms)" << endl;
	
	for(size_t i(0); i < spikesTime.size(); i++)
	{
		cout << spikesMembranePot[i] << " ********** " << spikesTime[i]*REFRACTORY_TIME << endl;
	}
}
	
void Neuron::setCurrent(double c)
{
	current = c;
}

double Neuron::getCurrent()
{
	return current;
}

void Neuron::setNeuronIsRefractory(bool a)
{
	neuronIsRefractory = a;
	
}
	
unsigned int Neuron::getNeuronTime()
{
	return neuronTime;
}
	
void Neuron::setNeuronTime(unsigned int t)
{
	neuronTime = t;
}
	
