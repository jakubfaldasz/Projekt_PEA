#pragma once
#include <vector>
#include "TSP.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <map>
#include <algorithm>

class TabuSearch
{
	TSP problem;
	std::vector<std::vector<int>> instance;
	int instanceSize;
	std::vector<std::vector<int>> tabuMatrix;
	std::map<int,int> tabuList;
	std::vector<int> globalBest;
	std::vector<int> epochBest;
	std::vector<int> localBest;
	int globalBestCost;
	int iteration = 100;
	int cadency = 10;
	int epochs = 5;
	bool aspirationCriterion = false;
	bool greedy = true;
	std::vector<int> generateRandomPerm();
	std::vector<int> greedyNN();
	std::pair<int, int> findBestNeighbourTour();
	void initalizeTabuList();
	std::vector<int> swapAndUpdateTabu(int v1, int v2);

	void displayPerm(std::vector<int> vector);
public:
	TabuSearch(TSP& problem);
	
	std::vector<int> findBest();

	void setAspirationCriterion(bool aspirationCriterion);
	void setGreedy(bool greedy);

	void setIteration(int iteration);
	void setCadency(int cadency);
	void setEpochs(int epochs);

};

