#include "GeneticAlgorithm.h"

std::vector<std::vector<int>> GeneticAlgorithm::chooseCandidatesCompetition(std::vector<std::vector<int>> populationToRate)
{
	std::vector<std::vector<int>> candidates;
	int currentCompetitionSampleSize = competitionSampleSize;

	int elementsToChoose = populationSize;
	for (int j = 0; j < populationSize; j++)
	{
		std::vector<std::vector<int>> sample;
		populationToRate.size() < currentCompetitionSampleSize ? currentCompetitionSampleSize = populationToRate.size() : currentCompetitionSampleSize = competitionSampleSize;

		std::vector<int> alreadyChosen;
		int randomResultIndex;
		for (int i = 0; i < currentCompetitionSampleSize; i++)
		{
			do {
				randomResultIndex = rand() % populationToRate.size();
			} while (std::find(alreadyChosen.begin(), alreadyChosen.end(), randomResultIndex) != alreadyChosen.end());
			alreadyChosen.push_back(randomResultIndex);

			sample.push_back(populationToRate[randomResultIndex]);
		}

		int bestCost = INT_MAX;
		std::vector<int> candidate;
		for (int i = 0; i < currentCompetitionSampleSize; i++)
		{
			int currentCost = tsp.countTC(sample[i]);
			if (currentCost < bestCost) {
				bestCost = currentCost;
				candidate = sample[i];
			}
		}

		elementsToChoose--;
		candidates.push_back(candidate);

		for (auto iter = populationToRate.begin(); iter != populationToRate.end(); ++iter) {
			if (*iter == candidate) {
				populationToRate.erase(iter);
				break;
			}
		}
	}

	return candidates;
}

void GeneticAlgorithm::change(std::vector<std::vector<int>>& vect)
{
	std::vector<std::vector<int>> nextGeneration;
	int randomPartner;

	for (int i = 0; i < populationSize; i++) {
		for (int j = 0; j < childrenCount; j++) {
			do
				randomPartner = rand() % populationSize;
			while (randomPartner == i);
			
			auto child = PMX(vect[i], vect[randomPartner]);

			if (mutation) {
				if (mutationOnEveryElement) {
					int randomIndexToSwap;
					for (int k = 0; k < instanceSize; k++) {
						int mutationProbabilty = rand() % mutationRange;
						if (mutationProbabilty == 0) {
							do
								randomIndexToSwap = rand() % child.size();
							while (randomIndexToSwap == k);
							std::swap(child[k], child[randomIndexToSwap]);
						}
					}
				}
				else {
					int randomIndexToSwap;
					int randomIndexToSwap2;
					int mutationProbabilty = rand() % mutationRange;
					if (mutationProbabilty == 0) {
						randomIndexToSwap = rand() % child.size();
						do
							randomIndexToSwap2 = rand() % child.size();
						while (randomIndexToSwap2 == randomIndexToSwap);
						std::swap(child[randomIndexToSwap2], child[randomIndexToSwap]);
					}
				}
			}

			if (rand() % crossoverRange != 0 || rand() % crossoverRange != 1)
				nextGeneration.push_back(child);
		}
	}

	vect = nextGeneration;
}

std::vector<int> GeneticAlgorithm::PMX(std::vector<int> p1, std::vector<int> p2)
{
	int slicePoint1, slicePoint2;

	slicePoint1 = rand() % instanceSize;
	do
		slicePoint2 = rand() % (instanceSize + 1);
	while (slicePoint2 <= slicePoint1);

	std::vector<int> child;
	std::vector<int> child2;
	for (int j = 0; j < slicePoint1; j++) {
		child.push_back(-1);
		child2.push_back(-1);
	}

	std::vector<int> sliceToInsertChild = std::vector<int>(p2.begin() + slicePoint1, p2.begin() + slicePoint2);
	std::vector<int> sliceToInsertChild2 = std::vector<int>(p1.begin() + slicePoint1, p1.begin() + slicePoint2);
	child.insert(child.end(), sliceToInsertChild.begin(), sliceToInsertChild.end());
	child2.insert(child2.end(), sliceToInsertChild2.begin(), sliceToInsertChild2.end());

	for (int j = slicePoint2; j < instanceSize; j++) {
		child.push_back(-1);
		child2.push_back(-1);
	}

	for (int j = 0; j < instanceSize; j++) {
		if (j >= slicePoint1 && j < slicePoint2)
			continue;

		if (std::find(child.begin(), child.end(), p1[j]) == child.end()) {
			child[j] = p1[j];
		}
		else {
			int p1Temp = p1[j];
			int index = j;
			do {
				index = findIndexOfElem(p2, p1Temp);
				p1Temp = p1[index];
			} while (std::find(child.begin(), child.end(), p1Temp) != child.end());
			child[j] = p1Temp;
		}

		if (std::find(child2.begin(), child2.end(), p2[j]) == child2.end()) {
			child2[j] = p2[j];
		}
		else {
			int p2Temp = p2[j];
			int index = j;
			do {
				index = findIndexOfElem(p1, p2Temp);
				p2Temp = p2[index];
			} while (std::find(child2.begin(), child2.end(), p2Temp) != child2.end());
			child2[j] = p2Temp;
		}
	}
	std::vector<int> offspring = (tsp.countTC(child) < tsp.countTC(child2) ? child : child2);

	//return child;
	return offspring;
}

int GeneticAlgorithm::findIndexOfElem(std::vector<int> vect, int value)
{
	auto indPtr = std::find(vect.begin(), vect.end(), value);
	if (indPtr == vect.end())
		return -1;
	else
		return std::distance(vect.begin(), indPtr);
}

void GeneticAlgorithm::initializePopulation()
{
	for (int i = 0; i < populationSize; i++) {
		if (greedy)
			population.push_back(greedyNN());
		else
			population.push_back(generateRandomPerm());
	}
}

void GeneticAlgorithm::ratePopulation(std::vector<std::vector<int>>& parents)
{
	int lowestCost = globalLowestCost;
	std::vector<int> currentBestResult;
	for (int i = 0; i < parents.size(); i++) {
		int currentCost = tsp.countTC(parents[i]);
		if (currentCost < lowestCost) {
			lowestCost = currentCost;
			currentBestResult = parents[i];
		}
	}
	bestResult = currentBestResult;
}

std::vector<int> GeneticAlgorithm::greedyNN()
{
	std::vector<int> result;

	int n = rand() % 10;
	result.push_back(n);

	int minCost;
	int nextVertex;
	int currentVertex = n;

	do {
		minCost = INT_MAX;
		for (int i = 0; i < instanceSize; i++) {
			if (i == currentVertex || std::find(result.begin(), result.end(), i) != result.end())
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

std::vector<int> GeneticAlgorithm::generateRandomPerm()
{
	std::vector<int> randomPerm;

	int nextValue;
	for (int i = 0; i < instanceSize; i++)
	{
		bool hasItAlready = false;
		do {
			nextValue = rand() % instanceSize;
			if (std::find(randomPerm.begin(), randomPerm.end(), nextValue) != randomPerm.end())
				continue;
			else
				hasItAlready = true;
		} while (!hasItAlready);

		randomPerm.push_back(nextValue);
	}

	return randomPerm;
}

GeneticAlgorithm::GeneticAlgorithm(TSP& tsp)
{
	this->tsp = tsp;
	instanceSize = tsp.getProblemSize();
	instance = tsp.getAdjacencyMatrix();
}

std::vector<int> GeneticAlgorithm::compute()
{
	if (iterations) {
		initializePopulation();
		int t = 0;
		while (t < iterationCount)
		{
			ratePopulation(population);
			previousPopulation = population;
			population = chooseCandidatesCompetition(previousPopulation);
			change(population);
			t++;
		}
	}
	else {
		initializePopulation();
		auto timeStart = clock();
		while (1) {
			if ((clock() - timeStart) / CLOCKS_PER_SEC >= runTime)
				break;
			ratePopulation(population);
			previousPopulation = population;
			population = chooseCandidatesCompetition(previousPopulation);
			change(population);

		}
	}
	return bestResult;
}

void GeneticAlgorithm::setMutation(bool mutation)
{
	this->mutation = mutation;
}

void GeneticAlgorithm::setMutationRange(int mutationRange)
{
	this->mutationRange = mutationRange;
}

void GeneticAlgorithm::setCompetitionSampleSize(int competitionSampleSize)
{
	this->competitionSampleSize = competitionSampleSize;
}

void GeneticAlgorithm::setPopulationSize(int populationSize)
{
	this->populationSize = populationSize;
}

void GeneticAlgorithm::setChildrenCount(int childrenCount)
{
	this->childrenCount = childrenCount;
}

void GeneticAlgorithm::setIterationCount(int iterationCount)
{
	this->iterationCount = iterationCount;
}

void GeneticAlgorithm::displayPermutation(std::vector<int> permutation, std::string str) {
	std::cout << str << ": ";
	for (int i = 0; i < permutation.size(); i++) {
		if (i == permutation.size() - 1)
			std::cout << permutation[i];
		else
			std::cout << permutation[i] << "-";
	}
	std::cout << "\n";
}
