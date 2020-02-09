#pragma once
#include "TSP.h"

class DynamicProgramming
{
	TSP problem;

	std::vector<std::vector<int>> matrix;
	int TC;
	std::vector<int> result;
	std::vector<int> route;

	int solve(int city, std::vector<int> remaining);
	int findMin(std::vector<std::pair<int, int>>array);
	void deleteElementByValue(std::vector<int> &array, int value);

public:

	DynamicProgramming(TSP &problem);
	std::pair<std::vector<int>, int> countDP();
	
	//std::pair<std::vector<int>, int> 
	int computeTSP();


};

