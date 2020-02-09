#include "BranchNBound.h"

int BranchNBound::chooseNode(int currentParentNode)
{
	int minCost = INT_MAX;
	int nodeIndex = -1;
	for (int i = 1; i < nodes.size(); i++) {
		int lowerBound = nodes[i].getLowerBound();
		if (lowerBound < minCost && lowerBound < upperBound && !nodes[i].getVisited()) {
			minCost = lowerBound;
			nodeIndex = i;
		}
	}
	return nodeIndex;
}

BranchNBound::BranchNBound(TSP& problem)
{
	this->problem = problem;
	this->instance = problem.getAdjacencyMatrix();
	upperBound = INT_MAX;
}

std::pair<std::vector<int>, int> BranchNBound::computeBnB()
{
	bool keepGoing = true;
	Node firstNode(instance, 0, 0, 0, 0);
	firstNode.firstReduction();
	nodes.push_back(firstNode);
	int result;
	std::vector<int> permutation;
	
	std::vector<int> notVisitedVert;
	for (int i = 1; i < instance.size(); i++) 
		notVisitedVert.push_back(i);
	
	int currentParentNode = 0;
	Node parentNode = nodes[currentParentNode];

	while (keepGoing) {
		for (int j = 0; j < notVisitedVert.size(); j++) {
			Node newNode(parentNode.getMatrix(), notVisitedVert[j], nodes.size(), parentNode.getVertex(), parentNode.getNodeId());
			
			std::vector<int> tempChildren = notVisitedVert;
			tempChildren.erase(std::remove(tempChildren.begin(), tempChildren.end(), newNode.getVertex()), tempChildren.end());
			newNode.setChildren(tempChildren);

			int parentNodeCost = parentNode.getLowerBound();
			newNode.reduceMatrix(parentNodeCost);
			nodes.push_back(newNode);
		}

		currentParentNode = chooseNode(currentParentNode);
		if (currentParentNode != -1) {
			nodes[currentParentNode].setVisited(true);
			parentNode = nodes[currentParentNode];
			notVisitedVert = parentNode.getChildren();
			if (notVisitedVert.size() < 1)
				upperBound = parentNode.getLowerBound();
			continue;
		}

		bool hasBetter = false;
		for (int i = 0; i < nodes.size(); i++) {
			if (!nodes[i].getVisited() && nodes[i].getLowerBound() < upperBound) {
				hasBetter = true;
				parentNode = nodes[i];
				notVisitedVert = parentNode.getChildren();
			}
			else
				nodes[i].setVisited(true);
		}

		if(!hasBetter) {
			keepGoing = false;
			result = upperBound;
			for (int i = 0; i < instance.size(); i++) {
				permutation.push_back(parentNode.getVertex());
				parentNode = nodes[parentNode.getParentNodeId()];
			}
		}
	}
	std::reverse(permutation.begin(), permutation.end());

	return std::pair<std::vector<int>, int>(permutation, result);
}