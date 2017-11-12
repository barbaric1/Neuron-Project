#include <iostream>
#include "gtest/gtest.h"
#include "neuron.hpp"
#include <cmath>


/** Obsolete, as we don't use anymore the current
 **/

TEST (Neuron_test, MembraneTest) 
{
	/*Neuron neuron;
	neuron.setCurrent(1.0);
	neuron.update(10);
	
	EXPECT_NEAR(20.0*(1.0-std::exp(-1.0/20.0)), neuron.getMembranePot(),0.0001); */
	} 

int main(int argc,char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



