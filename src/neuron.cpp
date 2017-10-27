#include "neuron.hpp"
#include "vector"
#include "cmath"


const double STANDARD_MEMBRANE_POT = 20;
const double REFRACTORY_TIME = 0.1
const double MEMBRANE_TIME_CONSTANT_TAU = 20;
const double MEMBRANE_RESISTENCE = 20 //Questo dovra cambiare dopo//


vector<unsigned int> Neuron::update(unsigned int stopTime)
{
	do
	{ if(membranePotential > STANDARD_MEMBRANE_POT)
		{
			spikes.push_back(neuronTime);
			neuronIsRefractory = true; //qu8a potrebbe servire un setter//
		}
		
		else if(neuronIsRefractory == true) //forse devo metterlo prima del primo "if", o piu probabilmente neuron is refractory non serve neanche e mi basta nella prima boucle if settare membranepotential a 0//
		{
			membranePotential = 0; //forse anche qui setter//
		}
		
		else
		{
			membranePotential = (exp((-1)*(REFRACTORY_TIME/MEMBRANE_TIME_CONSTANT_TAU))* membranePotential) + current * MEMBRANE_RESISTENCE * (1 - exp((-1)*(REFRACTORY_TIME/MEMBRANE_TIME_CONSTANT_TAU)));  //qua bisognera aggiungere J e inoltre potrebbe volerci l'utilizzo di getter e setter. Anche R dovra cambiare molto probabilmente
			neuronIsRefractory = false;
		}
		
		neuronTime += REFRACTORY_TIME;
		
		
	} while (neuronTime < stopTime);
	
	return spikes;
	
}


		
		
	
	
