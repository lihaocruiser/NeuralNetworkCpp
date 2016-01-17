#ifndef NET_H
#define NET_H

#include "Layer.h"

class Net
{

private:

	int mNumInputs;
	int mNumOutputs;
	int mNumLayers;

	std::vector<int> mDimens;
	std::vector<Layer> mLayers;
	std::vector<double> mInputs;
	
public:

	Net(std::vector<int> dimens);
	Net(std::vector<Layer>& layers);

	void setEta(int layerOrder, double eta);
	void setActivation(int layerOrder, int activationType);
	
	std::vector<double> feedForward(std::vector<double> &inputs);
	void backProp(std::vector<double> &targets);

};

#endif

