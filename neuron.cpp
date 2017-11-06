#include "neuron.hpp"
#include <vector>
#include <array>
#include <cmath>
#include <iostream>
#include <random>
using namespace std;

const double VARIABLE_RATIO = 2;
const double INHIBITORY_STRENGHT = 5;
const double STANDARD_MEMBRANE_POT = 20;
const double REFRACTORY_TIME = 20;
const double MEMBRANE_TIME_CONSTANT_TAU = 200;
const double MEMBRANE_RESISTENCE = 20; 
const double CONSTANT_J = 0.1; 
const int NUMBER_NEURONS = 12500;
const int NUMBER_NEURONS_CONNECTED = 0.8 * NUMBER_NEURONS;
const int NUMBER_NEURONS_CONNECTED_EXCITATORY = 0.1 * NUMBER_NEURONS_CONNECTED;
const int NUMBER_NEURONS_CONNECTED_INHIBITORY = 0.25 * NUMBER_NEURONS_CONNECTED_EXCITATORY;
const double Vthr = STANDARD_MEMBRANE_POT/(CONSTANT_J * NUMBER_NEURONS_CONNECTED_EXCITATORY * MEMBRANE_TIME_CONSTANT_TAU);
const double Vext = Vthr * VARIABLE_RATIO;
static std::random_device rd;
static std::mt19937 gen(rd());
std::poisson_distribution<int> Poisson(Vext * NUMBER_NEURONS_CONNECTED_EXCITATORY);



Neuron::Neuron()
: membranePotential(0), current(0), neuronIsRefractory(false), neuronWaiting(0), buffer(15,0), bufferCounter(0), inhibitoryNeuron(false), target(0) {}


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
			setNeuronIsRefractory(true); 
			setMembranePot(0);
			neuronWaiting = -REFRACTORY_TIME - 1;
		}
		else
		{
			
			setMembranePot((exp((-1)*(0.1/MEMBRANE_TIME_CONSTANT_TAU))* getMembranePot()) + (getCurrent() * MEMBRANE_RESISTENCE * (1 - exp((-1)*(0.1/MEMBRANE_TIME_CONSTANT_TAU)))) + ((buffer[bufferCounter] + Poisson(gen)) * CONSTANT_J));  //qua bisognera aggiungere J e inoltre potrebbe volerci l'utilizzo di getter e setter. Anche R dovra cambiare molto probabilmente
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
	
	if (bufferCounter == 0)   //potrei fare una funyione anche quui//
	{
		buffer[14] +=1;
	}
	else 
	{
	
		buffer[bufferCounter -1] += 1;
	}

}

void Neuron::receiveNeg()
{
	if (bufferCounter == 0)   //potrei fare una funyione anche quui//
	{
		buffer[14] -= INHIBITORY_STRENGHT;
	}
	else
	{
	
	buffer[bufferCounter - 1] -= INHIBITORY_STRENGHT;
	}
}

void Neuron::addTarget(Neuron* neuron)
{
	if (neuron ==nullptr) { cout<< "fucktarget"<< endl; }
	
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
	
vector<Neuron*> Neuron::getTarget()
{
	return target;
}

void Neuron::setInhibitoryState(bool i)
{
	inhibitoryNeuron = i;
}

bool Neuron::getInhibitoryState()
{
	return inhibitoryNeuron;
}
