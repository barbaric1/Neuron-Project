#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron {
	
	private:
	
	double membranePotential;
	double current;
	bool neuronIsRefractory;
	int neuronWaiting;
	std::vector<int> buffer;
	unsigned int bufferCounter;
	bool inhibitoryNeuron;
	std::vector<Neuron*> target;
	std::vector<unsigned int> spikesTime;
	
	
	
	public:
	
/** \brief A simple constructor for the Neuron class.
 *
 * Creates a new Neuron and initializes all the parametres as needed for the start of the simulation.
 **/
	
	Neuron();
	
/** \brief The main method concerning one step of simulation for a single Neuron.
 * 
 * 
 * The method consist in a void function without parameters that will simply run for one simulation step a Neuron, making it spike or not.
 **/
	
	void update();
	
	/** \brief A setter for the parameter membranePotential.
	 * \param m: corresponds to the value that we want to give to membranePotential.
	 **/
	
	
	void setMembranePot(double m);
	
	/** \brief A getter for the parameter membranePotential.
	 **/
	
	
	double getMembranePot();
	
	/** \brief A setter for the parameter current (obsolete after the creation of a Network).
	 * \param c: the value that we want to give to current.
	 **/
	
	
	void setCurrent(double c);
	
	/** \brief A getter for the parameter current (obsolete after the creation of a Network).
	 **/
	
	double getCurrent();
	
	/** \brief A setter for the parameter neuronIsRefractory.
	 * \param a: the value (true or false) that we want to give to neuronIsRefractory.
	 **/
	
	
	void setNeuronIsRefractory(bool a);
	
	/** \brief A getter for the parameter neuronIsRefractory.
	 **/
	
	
	bool getNeuronIsRefractory();
	
	/** \brief The method that will send the signal of a spike to a target neuron through the ring buffer.
	 * 
	 * The method will also check if the bufferCounter is bigger than the size of our buffer and adjust it if so.
	 * This method is exclusive to excitatory Neurons.
	 * \param buf: parameter that's important to indicate the delay of the spike to the target Neuron. In fact the Neuron will always 
	 * be one step of simulation ahead of its target Neurons.
	 **/
	
	void receive(int buf);
	
	/** \brief Same as the method receive, but for the inhibitory Neurons, as they behave differently than the excitatory
	 * Neurons with the ring buffer.
	 **/
	
	void receiveNeg(int buf);
	
	/** \brief adds a Neuron to the list of target of our Neuron.
	 * \param neuron: is a pointer to a Neuron object.
	 **/
	
	void addTarget(Neuron* neuron);
	
	/** \brief sends back the list of target of our Neuron.
	 **/
	
	std::vector<Neuron*> getTarget();
	
	/** \brief A setter for the parameter inhibitoryState.
	 *  \param i: a bool taht indicates the value (true or false) that we want give to inhibitoryState.
	 **/ 
	
	
	void setInhibitoryState(bool i);
	
	/** \brief A getter for the parameter inhibitoryState.
	 **/
	
	bool getInhibitoryState();
	
	/** \brief A getter fo the parameter bufferCounter.
	 **/
	
	
	int getBufferTime ();
	
	
};

#endif
