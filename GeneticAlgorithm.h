#pragma once
#include <vector>
#include "TSP.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

class GeneticAlgorithm
{
	TSP tsp;
	std::vector<std::vector<int>> instance;
	int instanceSize;

	int childrenCount = 3;
	int populationSize = 100;
	int iterationCount = 100;
	int competitionSampleSize = 2;

	bool mutation = true;
	bool mutationOnEveryElement = false;
	int mutationRange = 10;

	bool iterations = true;
	int runTime = 600;

	bool greedy = true;

	int crossoverRange = 10;
	std::vector<std::vector<int>> population;
	std::vector<std::vector<int>> previousPopulation;
	std::vector<int> bestCandidates;
	std::vector<int> bestResult;
	int globalLowestCost = INT_MAX;

	std::vector<std::vector<int>> chooseCandidatesCompetition(std::vector<std::vector<int>> currentPopulation);
	void change(std::vector<std::vector<int>>& vect);
	std::vector<int> PMX(std::vector<int> p1, std::vector<int> p2 );
	void initializePopulation();
	void ratePopulation(std::vector<std::vector<int>> &parents);
	void displayPermutation(std::vector<int> permutation, std::string str);
	int findIndexOfElem(std::vector<int> vect, int value);

	std::vector<int> greedyNN();
	std::vector<int> generateRandomPerm();
public:
	GeneticAlgorithm(TSP& tsp);

	std::vector<int> compute();
	void setMutation(bool mutation);
	void setMutationRange(int mutationRange);
	void setCompetitionSampleSize(int competitionSampleSize);
	void setPopulationSize(int populationSize);
	void setChildrenCount(int childrenCount);
	void setIterationCount(int iterationCount);
};

