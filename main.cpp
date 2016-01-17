#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Net.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {

	srand((int) time(0));

	std::vector<int> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(2);
		
	Net net(v);
	net.setActivation(2,1);
	
	std::vector<double> input;
	input.push_back(-2);
	input.push_back(2);
	input.push_back(3);

	std::vector<double> targets;
	targets.push_back(10);
	targets.push_back(-5);
	
	std::cout << "input: ";
	for (int i = 0; i<input.size(); i++)
	{
		std::cout << input[i] << ",";
	}
	std::cout << std::endl;

	std::vector<double> output;	
	for (int i = 0; i<100; i++)
	{
		output = net.feedForward(input);
		net.backProp(targets);
	
		std::cout << "output: ";
		for (int i = 0; i<output.size(); i++)
		{
			std::cout << output[i] << ",";
		}
		std::cout << std::endl;
	}
	
	return 0;
}

