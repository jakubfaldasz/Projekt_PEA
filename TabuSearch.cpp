#include "TabuSearch.h"

TabuSearch::TabuSearch(TSP& problem)
{
	srand(time(NULL));
	this->problem = problem;
	instance = problem.getAdjacencyMatrix();
	instanceSize = problem.getProblemSize();
	globalBest = generateRandomPerm();
	globalBestCost = problem.countTC(epochBest);

    tabuMatrix = std::vector<std::vector<int>>(instanceSize, std::vector<int>(instanceSize, 0));
}

std::vector<int> TabuSearch::findBest()
{
	int tries = 0;
	std::pair<int, int> vertexesToSwap;
	std::vector<int> tempTour;		
	int epochBestCost;
	int localBestCost;
	do {
		if(greedy)
			epochBest = greedyNN();
		else
			epochBest = generateRandomPerm();

		epochBestCost = problem.countTC(epochBest);
		int count = 0;
		do {
			vertexesToSwap = findBestNeighbourTour();
			localBest = swapAndUpdateTabu(vertexesToSwap.first, vertexesToSwap.second);
			localBestCost = problem.countTC(localBest);
			if (localBestCost < epochBestCost) {
				epochBest = localBest;
				epochBestCost = localBestCost;
			}
			count++;
		} while (count < iteration);
		tries++;
		if (problem.countTC(epochBest) < problem.countTC(globalBest))
			globalBest = epochBest;
	} while (tries < epochs);

	return globalBest;
}


void TabuSearch::setAspirationCriterion(bool aspirationCriterion)
{
	this->aspirationCriterion = aspirationCriterion;
}

void TabuSearch::setGreedy(bool greedy)
{
	this->greedy = greedy;
}

void TabuSearch::setIteration(int iteration)
{

}

void TabuSearch::setCadency(int cadency)
{
	this->cadency = cadency;
}

void TabuSearch::setEpochs(int epochs)
{
	this->epochs = epochs;
}

std::vector<int> TabuSearch::generateRandomPerm()
{
	std::vector<int> randomPerm;
	
	int nextValue;
	for (int i = 0; i < problem.getProblemSize(); i++)
	{
		bool hasItAlready = false;
		do {
			nextValue = rand() % problem.getProblemSize();
			if (std::find(randomPerm.begin(), randomPerm.end(), nextValue) != randomPerm.end())
				continue;
			else
				hasItAlready = true;
		} while (!hasItAlready);

		randomPerm.push_back(nextValue);
	}
	
	return randomPerm;
}
std::vector<int> TabuSearch::greedyNN()
{
	std::vector<int> result;

	int n = rand()%10;
	result.push_back(n);
	
	int minCost;
	int nextVertex;
	int currentVertex = n;

	do {
		minCost = INT_MAX;
		for (int i = 0; i < instanceSize; i++) {
			if (i == currentVertex || std::find(result.begin(), result.end(), i) != result.end() )
				continue;

			if (instance[currentVertex][i] < minCost) {
				minCost = instance[currentVertex][i];
				nextVertex = i;
			}
		}
		currentVertex = nextVertex;
		result.push_back(nextVertex);
	} while (result.size() != instanceSize);

	return result;
}
std::pair<int, int> TabuSearch::findBestNeighbourTour()
{
	int firstIndex = -1;
	int secondIndex = -1;
	int aspiracyIndex1, aspiracyIndex2;
	int minTour = INT_MAX;
	int minAspiracyTour = minTour;
	int tour;
	
	std::vector<int> temp = epochBest;
	for (int i = 0; i < instanceSize-1; i++) 
	{
		for (int j = i+1; j < instanceSize; j++) {
			if (tabuMatrix[i][j] > 0) {
				if (aspirationCriterion) {
					iter_swap(temp.begin() + i, temp.begin() + j);
					tour = problem.countTC(temp);
					if (tour < minAspiracyTour) {
						minAspiracyTour = tour;
						aspiracyIndex1 = i;
						aspiracyIndex2 = j;
					}
					temp = epochBest;
				}
				continue;
			}

			iter_swap(temp.begin() + i, temp.begin() + j);

			tour = problem.countTC(temp);
			if (tour < minTour) {
				minTour = tour;
				firstIndex = i;
				secondIndex = j;
			}
			temp = epochBest;
		}
	}

	//kryterium aspiracji
	if (minTour > problem.countTC(epochBest) && minAspiracyTour < minTour && aspirationCriterion) {
		firstIndex = aspiracyIndex1;
		secondIndex = aspiracyIndex2;
	}

	return std::pair<int, int>(firstIndex, secondIndex);
}


std::vector<int> TabuSearch::swapAndUpdateTabu(int v1, int v2)
{
	std::vector<int> tempVect = epochBest;
	iter_swap(tempVect.begin() + v1, tempVect.begin() + v2);
		
	for (int i = 0; i < instance.size()-1; i++) {
		for (int j = i+1; j < instance.size(); j++) {
			if (tabuMatrix[i][j] > 0) 
				tabuMatrix[i][j]--;
		}
	}

	tabuMatrix[v1][v2] = cadency;

	return tempVect;
}

void TabuSearch::displayPerm(std::vector<int> perm)
{
	for (int i = 0; i < perm.size(); i++) {
		if (i == perm.size() - 1)
			std::cout << perm[i];
		else
			std::cout << perm[i] << "-";
	}
	std::cout << "\n";
}

void TabuSearch::initalizeTabuList()
{
	tabuMatrix = std::vector<std::vector<int>>(instanceSize, std::vector<int>(instanceSize, 0));
}
