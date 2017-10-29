#include "neuron.hpp"
#include "vector"
#include "cmath"


const double STANDARD_MEMBRANE_POT = 20;
const double REFRACTORY_TIME = 0.1
const double MEMBRANE_TIME_CONSTANT_TAU = 20;
const double MEMBRANE_RESISTENCE = 20 //Questo dovra cambiare dopo//


void Neuron::update(unsigned int stopTime, double curr)
{
	//FORSE QUA CI VORRA UN SETTER PER SETTARE neuronIsRefractory A FALSE INIZIALMENTE
	
	setCurrent(curr);
	
	do
	{ if(getMembranePot() > STANDARD_MEMBRANE_POT)
		{
			spikesTime.push_back(neuronTime);
			neuronIsRefractory = true; //qu8a potrebbe servire un setter//
		}
		
		else if((neuronIsRefractory == true) and (getMembranePot() != 0)) //forse devo metterlo prima del primo "if", o piu probabilmente neuron is refractory non serve neanche e mi basta nella prima boucle if settare membranepotential a 0//
		{
			setMembranePot(0); //forse anche qui setter//
		}
		
		else
		{
			setMembranePot((exp((-1)*(REFRACTORY_TIME/MEMBRANE_TIME_CONSTANT_TAU))* getMembranePot()) + (getCurrent() * MEMBRANE_RESISTENCE * (1 - exp((-1)*(REFRACTORY_TIME/MEMBRANE_TIME_CONSTANT_TAU)))));  //qua bisognera aggiungere J e inoltre potrebbe volerci l'utilizzo di getter e setter. Anche R dovra cambiare molto probabilmente
			neuronIsRefractory = false;
		}
		spikesMembranePot.push_back(getMembranePot());
		neuronTime += REFRACTORY_TIME;
		
		
	} while (neuronTime < stopTime);
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

void Neuron::storeSpikesMembrane&Time() 
{
	cout << "Membrane Potential ********** Time(ms)" << endl;
	
	for(size_t i(0); i < spikesTime.size(); i++)
	{
		cout << spikesMembranePot[i] << " ********** " << spikesTime[i] << endl;
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

		
		
	
	
