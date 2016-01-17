#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
	public:
	    int mNumWeights;
	    std::vector<double> mWeights;
	    double mA;		// a
	    double mZ;		// z
	    double mDelta;	// delta
	    
	    Node(int numInputs);
	
	private:
		static int mNumTotal;
};

#endif

