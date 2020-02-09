#include "TSP.h"

TSP::TSP()
{
	instanceName = "";
	adjacencyMatrix.resize(0);
	problemSize = 0;
	TC = 0;
}

TSP::TSP(std::string pathName)
{
	adjacencyMatrix = ld.loadInstance(pathName);
	instanceName = ld.getInstanceName();
	problemSize = ld.getProblemSize();
	TC = 0;
}

TSP::TSP(int size, int minWeight, int maxWeight, int instanceId, bool symetrical)
{
	adjacencyMatrix = ld.generateRandomInstance(size, minWeight, maxWeight, instanceId, symetrical);
	instanceName = ld.getInstanceName();
	problemSize = ld.getProblemSize();
	TC = 0;
}

int TSP::countTC(std::vector<int> permutation)
{
	int solution = 0;
	for (int i = 0; i < permutation.size(); i++) {
		if (i == permutation.size() - 1) {
			solution += adjacencyMatrix[permutation[i]][permutation[0]];
		}
		else {
			solution += adjacencyMatrix[permutation[i]][permutation[i+1]];
		}
	}

	TC = solution;
	return TC;
}

void TSP::displayInstance()
{
	InstanceLoader::displayInstance(adjacencyMatrix, instanceName, problemSize, TC);
}

bool TSP::isLoadedProperly()
{
	if (adjacencyMatrix.empty())
		return false;
	else
		return true;
}

std::pair<std::vector<int>, int> TSP::bruteForceSearch()
{

	return std::pair<std::vector<int>, int>();
}

std::vector<std::vector<int>> TSP::getAdjacencyMatrix()
{
	return adjacencyMatrix;
}

std::string TSP::getInstanceName()
{
	return instanceName;
}

int TSP::getProblemSize()
{
	return problemSize;
}

int TSP::getTC()
{
	return TC;
}

void TSP::setTC(int tc)
{
	TC = tc;
}
