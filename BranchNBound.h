#pragma once
#include "TSP.h"
#include "Node.h"

class BranchNBound
{
	TSP problem;
	std::vector<std::vector<int>> instance;
	std::vector<Node> nodes;
	int upperBound;

	int chooseNode(int currentParentNode);

public:

	BranchNBound(TSP& problem);

	std::pair<std::vector<int>, int> computeBnB();


};

