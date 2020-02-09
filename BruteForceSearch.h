#pragma once
#include <vector>
#include <iostream>
#include "TSP.h"

class BruteForceSearch
{
	TSP problem;
	std::vector<int> permutation;
	int TC;
	std::vector<int> result;

	void first();
	bool next();
	void reverseSequence(int index);
	void permutate(std::vector<int> a, int size);
	void heapPermute(int n, std::vector<int> &arr);

public:

	BruteForceSearch();
	BruteForceSearch(TSP& tsp);
	std::pair<std::vector<int>, int> lexicographicOrdering();
	std::pair<std::vector<int>, int> johnsonTrotter();
	std::pair<std::vector<int>, int> heaps();


};

