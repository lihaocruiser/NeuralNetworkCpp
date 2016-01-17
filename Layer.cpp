#include "Layer.h"

#include <cmath>
#include <iostream>

Layer::Layer(int numNodes, int numInputs): mNumNodes(numNodes), mActivationType(0), mEta(0.1)
{
	std::cout << "Layer:"  << numInputs << "x" << numNodes << std::endl;
	for (int i=0; i<mNumNodes; i++)
	{
		mNodes.push_back(Node(numInputs));
	}
}

double Layer::active(double a)
{
	if (mActivationType == 0) {
		return sigmoid(a);
	} else {
		return a;
	}
}

double Layer::devAct(double a)
{
	if (mActivationType == 0) {
		return devSig(a);
	} else {
		return 1;
	}
}

double Layer::sigmoid(double activation)
{
	return 1 / (1+exp(-activation));
}

double Layer::devSig(double activation)
{
	double y = sigmoid(activation);
	return y * (1-y);
}

