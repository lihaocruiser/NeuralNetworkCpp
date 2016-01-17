## Intro

2 kinds of nodes: sigmoid and linear

random initialized weights

## Usage

get a simple net:
```
	Net net(vector<int> dimens);
```
or
```
	Net net(vector<Layer> layers);
```

set learning rate:
```
	net.setEta(int layerOrder, double eta);
```

set activation function type:
```
	net.setActive(int layerOrder, int type);	// 0 for sigmoid, other values for linear
```

feedforward:
```
	vector<double> output = net.feedforward(vector<double> input);
```

backpropagate:
```
	net.backpropagate(vector<double> targets);
```
