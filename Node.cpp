#include "Node.h"

#include <cstdlib>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iostream>

Node::Node(int numInputs): mNumWeights(numInputs+1)
{
    for (int i=0; i<mNumWeights; ++i)
    {
    	double weight = (rand() % 200 - 100) / 100.0f;
    	//std::cout << weight << std::endl;
   		mWeights.push_back(weight);
    }
}

