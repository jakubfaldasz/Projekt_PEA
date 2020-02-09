#pragma once
#include <vector>
#include <string>
#include <algorithm> 
#include "InstanceLoader.h"

class TSP
{
	std::string instanceName;
	int problemSize;
	std::vector<std::vector<int>> adjacencyMatrix;
	InstanceLoader ld;
	int TC;

public:

	TSP();
	TSP(std::string pathName);
	TSP(int size, int minWeight, int maxWeight, int instanceId, bool symetrical);
	int countTC(std::vector<int> permutation);
	void displayInstance();
	bool isLoadedProperly();

	std::pair<std::vector<int>, int> bruteForceSearch();

	std::vector<std::vector<int>> getAdjacencyMatrix();
	std::string getInstanceName();
	int getProblemSize();
	int getTC();
	void setTC(int tc);

};

