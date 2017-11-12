#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <cassert>
using namespace std;

/*! \brief All the constants used to make Neuron work.
 * 
 * The first two constants are the ones to change if we wish to obtein a different graph.
 **/

const double VARIABLE_RATIO = 2;
const double INHIBITORY_STRENGHT = 5;
const double STANDARD_MEMBRANE_POT = 20;
const double REFRACTORY_TIME = 20;
const double SIGNAL_BUFFER = 15;
const double MEMBRANE_TIME_CONSTANT_TAU = 200;
const double MEMBRANE_RESISTENCE = 20; 
const double CONSTANT_J = 0.1; 
const int NUMBER_NEURONS = 12500;
const int NUMBER_NEURONS_CONNECTED = 0.8 * NUMBER_NEURONS;
const int NUMBER_NEURONS_CONNECTED_EXCITATORY = 0.1 * NUMBER_NEURONS_CONNECTED;
const int NUMBER_NEURONS_CONNECTED_INHIBITORY = 0.25 * NUMBER_NEURONS_CONNECTED_EXCITATORY;
const double Vthr = STANDARD_MEMBRANE_POT/(CONSTANT_J * NUMBER_NEURONS_CONNECTED_EXCITATORY * MEMBRANE_TIME_CONSTANT_TAU);
const double Vext = Vthr * VARIABLE_RATIO;


Neuron::Neuron()
: membranePotential(0), current(0), neuronIsRefractory(false), neuronWaiting(0), buffer(16,0), bufferCounter(0), inhibitoryNeuron(true), target(0) {}

/** membrnePotential: the membrane potential of the Neuron.
 *  current: the external current input (this parameter is obsolete once we have a neural network).
 *  neuronIsRefractory: a bool that tells us if the Neuron is in a spiking state or not (if false, the neuron isn't spiking).
 *  neuronWaiting: a counter that keeps the Neuron actionless for some time after a spike occured.
 *  buffer: a vector that simulates our irng buffer.
 *  bufferCounter: a counter that helps us to move in our ring buffer every step of the simulation.
 *  inhibitoryNeuron: a bool that tells us if our Neuron in the Network is inhibitory or not.
 *  target: a vector that collects all the Neurons that are connected to our Neuron.
 **/

void Neuron::update()
{
	
static random_device rd;
static mt19937 gen(rd());
poisson_distribution<int> poisson(Vext * NUMBER_NEURONS_CONNECTED_EXCITATORY);
	
/** We want first to know if our Neuron is in a refractory state or not.
 **/

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
			
			/** This attribute grants us that our neuron will wait for exactly 20 steps of simulation after a spike without being able
			 * to spike again.
			 **/
			
			neuronWaiting = -REFRACTORY_TIME - 1;
		}
		else
		{
			
			setMembranePot((exp((-1)*(1/MEMBRANE_TIME_CONSTANT_TAU))* getMembranePot()) + (getCurrent() * MEMBRANE_RESISTENCE * (1 - exp((-1)*(1/MEMBRANE_TIME_CONSTANT_TAU)))) + (buffer[bufferCounter] + poisson(gen)) * CONSTANT_J);  
	    }
    }
		bufferCounter += 1;
		neuronWaiting += 1;
		
		/** Condition necessary to navigate through our ring buffer and avoid Segmentations Faults.
		 **/
		
		if (bufferCounter > 14) 
		{
		bufferCounter = 0;
		}
	
	/** Every time that one step ends, we have to empty our buffer ring vector.
	 **/
	
		buffer[bufferCounter] = 0;
}

void Neuron::receive(int buf)
{

/** To be sure to avoid Segmentation Faults, we put this condition in our method
 **/
	if (bufferCounter == 0) 
	{
		buffer[SIGNAL_BUFFER - 1] +=1;
	}
	
/** Once we are sure to avoid Segmentations Faults, we write on our buffer ring when a spike occured.
 **/
	
	else 
	{
	
		buffer[buf -1] += 1;
	}

}

void Neuron::receiveNeg(int buf)
{
	if (bufferCounter == 0)   
	{
		buffer[SIGNAL_BUFFER - 1] -= INHIBITORY_STRENGHT;
	}
	else
	{
	
	buffer[buf - 1] -= INHIBITORY_STRENGHT;
	}
}

void Neuron::addTarget(Neuron* neuron)
{
/** This assert grants us that our simulation will not run if the pointer to a Neuron that we add is equal to nullptr.
 **/
	assert(neuron != nullptr); 
	
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

int Neuron::getBufferTime()
{
		return bufferCounter;
}
