#include "neuron.hpp"
#include <vector>
#include <array>
#include <cmath>
#include <iostream>
using namespace std;

const double STANDARD_MEMBRANE_POT = 20;
const double REFRACTORY_TIME = 1.5;
const double MEMBRANE_TIME_CONSTANT_TAU = 20;
const double MEMBRANE_RESISTENCE = 20; 
const double CONSTANT_J = 0.1; 


Neuron::Neuron()
: membranePotential(0), neuronTime(0), current(0), neuronIsRefractory(false), neuronWaiting(0), buffer(15,0), bufferCounter(0) {}


Neuron::~Neuron() {}


void Neuron::update()
{
	

	if (neuronWaiting < 0)
	{
		setNeuronIsRefractory(false);
	}
		
	else
	{
		
		if(getMembranePot() > STANDARD_MEMBRANE_POT)
		{
			spikesTime.push_back(neuronTime);
			setNeuronIsRefractory(true); 
			setMembranePot(0);
			neuronWaiting = -16;
		}
		else
		{
			setMembranePot((exp((-1)*(0.1/MEMBRANE_TIME_CONSTANT_TAU))* getMembranePot()) + (getCurrent() * MEMBRANE_RESISTENCE * (1 - exp((-1)*(0.1/MEMBRANE_TIME_CONSTANT_TAU)))) + (buffer[bufferCounter] * CONSTANT_J));  //qua bisognera aggiungere J e inoltre potrebbe volerci l'utilizzo di getter e setter. Anche R dovra cambiare molto probabilmente
			
	}
}
		spikesMembranePot.push_back(getMembranePot());
		bufferCounter += 1;
		neuronWaiting += 1;
		
		if (bufferCounter > 14)  //POTREI FARE UNA FUNYIONCINA//
	{
		bufferCounter = 0;
	}
}

void Neuron::receive()
{
	if (bufferCounter > 14)
	{
		bufferCounter = 0;
	}
	
	buffer[bufferCounter -1] += 1;
}

void Neuron::addTarget(Neuron* neuron)
{
	target.push_back(neuron);
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

bool Neuron::getNeuronIsRefractory()
{
	return neuronIsRefractory;
}
	
unsigned int Neuron::getNeuronTime()
{
	return neuronTime;
}
	
void Neuron::setNeuronTime(unsigned int t)
{
	neuronTime = t;
}
	
vector<Neuron*> Neuron::getTarget()
{
	return target;
}
