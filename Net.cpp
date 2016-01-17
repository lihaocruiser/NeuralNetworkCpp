#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "Net.h"

using std::vector;

Net::Net(std::vector<int> dimens)
{
	for (int i=0; i<dimens.size(); i++)
	{
		mDimens.push_back(dimens[i]);
	}
	for (int i=0; i<mDimens.size()-1; i++)
	{
		int dimIn = mDimens[i];
		int dimOut = mDimens[i+1];
		mLayers.push_back(Layer(dimOut, dimIn));
	}
	mNumInputs = mDimens[0];
	mNumOutputs = mDimens[mDimens.size()-1];
	mNumLayers = mDimens.size()-1;
}

void Net::setEta(int layerOrder, int eta)
{
	if (mNumLayers<layerOrder) {
		std::cout << "LayerOrder exceeds LayerNumber!" << std::endl;
	} else {
		mLayers[layerOrder-1].mEta = eta;
	}
}

void Net::setActivation(int layerOrder, int activationType)
{
	if (mNumLayers<layerOrder) {
		std::cout << "LayerOrder exceeds LayerNumber!" << std::endl;
	} else {
		mLayers[layerOrder-1].mActivationType = activationType;
	}
}

vector<double> Net::feedForward(vector<double> &inputs)
{
	mInputs = inputs;
	
	//stores the resultant outputs from each layer
	vector<double> outputs;
	
	int cWeight = 0;
	
	//first check that we have the correct amount of inputs
	if (inputs.size() != mNumInputs)
	{
		std::cout << "Error: input dimension not match." << std::endl;
		std::cout << "input size: " << inputs.size() << std::endl;
		std::cout << "mNumInputs: " << mNumInputs   << std::endl;
		return outputs;
	}
	
	//For each layer....
	for (int i=0; i<mNumLayers; ++i)
	{
		if ( i > 0 )
		{
			inputs = outputs;
		}
		outputs.clear();
		
		//for each node
		for (int j=0; j<mLayers[i].mNumNodes; ++j)
		{
			double a = 0;
			int numInputs = mLayers[i].mNodes[j].mNumWeights;
			//for each weight
			for (int k=0; k<numInputs-1; ++k)
			{
				//sum the weights x inputs
				a += mLayers[i].mNodes[j].mWeights[k] * inputs[k];
			}
			//add in the bias
			a += mLayers[i].mNodes[j].mWeights[numInputs-1] * 1;
			double z = mLayers[i].active(a);
			mLayers[i].mNodes[j].mA = a;		// sava a to current node
			mLayers[i].mNodes[j].mZ = z;		// sava z to current node
			outputs.push_back(z);				// feed to next layer
		}
	}
	
	inputs = mInputs;
	
	return outputs;
}


void Net::backProp(vector<double> &targets)
{
	/*	calc delta	*/
			
	//for the last layer
	int i = mNumLayers-1;
	for (int j=0; j<mLayers[i].mNumNodes; j++)
	{
		double a = mLayers[i].mNodes[j].mA;
		double z = mLayers[i].mNodes[j].mZ;
		double delta = (z - targets[j]) * mLayers[i].devAct(a);
		mLayers[i].mNodes[j].mDelta = delta;
	}
	//for other layers
	for (i=mNumLayers-2; i>=0; i--)
	{
		//for each node
		for (int j=0; j<mLayers[i].mNumNodes; j++)
		{
			// delta(l) = delta(l+1) * w(l+1) * devSig(a(l))
			double mdw = 0;
			for (int k=0; k<mLayers[i+1].mNumNodes; k++)
			{
				double d = mLayers[i+1].mNodes[k].mDelta;		// delta(l+1)
				double w = mLayers[i+1].mNodes[k].mWeights[j];	// weight(l+1)
				mdw += d*w;
				mdw = 0;
			}
			double devA = mLayers[i].devAct(mLayers[i].mNodes[j].mA);
			double delta = devA * mdw;
			mLayers[i].mNodes[j].mDelta = delta;
		}
	}
	
	
	/*	update weights	*/
	
	//for other layers
	for (int i=mLayers.size()-1; i>0; i--)
	{
		for (int j=0; j<mLayers[i].mNumNodes; j++)
		{
			//gradient = eta(l) * delta(l) * z(l-1)
			double delta = mLayers[i].mNodes[j].mDelta;
			double eta = mLayers[i].mEta;
			double mde = delta * eta;
			int k = 0;
			for (k=0; k<mLayers[i].mNodes[j].mNumWeights-1; k++)
			{
				//weights
				double z = mLayers[i-1].mNodes[k].mZ;
				mLayers[i].mNodes[j].mWeights[k] -= mde * z;
			}
			//bias weight
			mLayers[i].mNodes[j].mWeights[k] -= mde * 1;
		}
	}
	
	//for the first layer
	for (int j=0; j<mLayers[0].mNumNodes; j++)
	{
		//gradient = eta(l) * delta(l) * z(l-1)
		double delta = mLayers[0].mNodes[j].mDelta;
		double eta = mLayers[0].mEta;
		double mde = delta * eta;
		int k = 0;
		for (k=0; k<mLayers[0].mNodes[j].mNumWeights-1; k++)
		{
			//weights
			double z = mInputs[k];
			mLayers[0].mNodes[j].mWeights[k] -= mde * z;
		}
		//bias weight
		mLayers[0].mNodes[j].mWeights[k] -= mde * 1;
	}
}

