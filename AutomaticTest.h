#pragma once
#include <chrono>
#include <iomanip>
#include <locale>
#include <fstream>
#include "TSP.h"
#include "BranchNBound.h"
#include "BruteForceSearch.h"
#include "TabuSearch.h"
#include "GeneticAlgorithm.h"


typedef std::chrono::high_resolution_clock Clock;

class AutomaticTest
{
	TSP* tsp;
	BranchNBound* bnb;
	BruteForceSearch* bf;
	TabuSearch* tabu;
	GeneticAlgorithm* ga;
	InstanceLoader* il;
	int problemCount;
	std::ofstream myfile;
	
public:

	AutomaticTest();
	
	long long performTestBnB(int dataSet);
	long long performTestBF(int dataSet);
	long long performTestTS(int dataSet, int iteration, int cadency, int epochs, bool aspiracy, bool greedy);
	int performTourTestTS(int dataSet, int iteration, int cadency, int epochs, bool aspiracy, bool greedy, bool symetric);
	int performTourTestGA(int dataSet, int iteration, int populationSize, int competitionSampleSize, bool mutation, int mutationRange);

	bool performAutoTestBnB(std::string fileName, int maxProblemSize, int howManyTests);
	bool performAutoTestBF(std::string fileName, int maxProblemSize, int howManyTests);
	bool performAutoTestTS(std::string fileName, int howManyTests);
	bool performAutoTourTestTS(std::string fileName, int howManyTests);
	bool performAutoTourTestGA(std::string fileName, int howManyTests);
	
};

