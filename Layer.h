#ifndef LAYER_H
#define LAYER_H

#include "Node.h"

class Layer
{
	public:
	    int mNumNodes;
	    int mNumInputs;
	    int mActivationType;	// default 0 for sigmoid node, other values for linear node
	    double mEta;
	    std::vector<Node> mNodes;
	    
    	Layer(int numInputs, int numNodes);
    	double active(double a);
    	double devAct(double a);
    
    private:
		inline double sigmoid(double a);
		inline double devSig(double a);
};

#endif

