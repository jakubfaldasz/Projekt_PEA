#include "BruteForceSearch.h"

void BruteForceSearch::first()
{
	for (int i = 1; i < problem.getProblemSize(); i++) {
		permutation.push_back(i);
	}
}

bool BruteForceSearch::next()
{
	int k = -1;
	for (int i = 0; i < permutation.size() -1; i++) {
		if (permutation[i] < permutation[i + 1])
			k = i;	
	}

	if (k == -1)
		return false;

	int l = k+1;
	for (int i = k+1; i < permutation.size(); i++) {
		if (permutation[k] < permutation[i]) 
			l = i;
	}

	int temp = permutation[k];
	permutation[k] = permutation[l];
	permutation[l] = temp;

	reverseSequence(k + 1);

	return true;
}

void BruteForceSearch::reverseSequence(int index) {
	int temp;
	for (int i = 0, k = permutation.size()-1; i < (permutation.size()-index)/2; i++, k--) {
		temp = permutation[i + index];
		permutation[i + index] = permutation[k];
		permutation[k] = temp;		
	}
}

void BruteForceSearch::heapPermute(int k, std::vector<int> &arr) {

	if (k == 1) {
		arr.insert(arr.begin(), 0);
		int tempTC = problem.countTC(arr);
		if (tempTC < TC) {
			TC = tempTC;
			result = arr;
		}
		arr.erase(arr.begin());
		return;
	}
	else {
		for (int i = 0; i < k; i++) {
			heapPermute(k - 1, arr);
			if (k % 2 == 0 && i < k-1) {
				std::swap(arr[i], arr[k - 1]);
			}
			else {
				std::swap(arr[0], arr[k - 1]);
			}
		}
	}
}
 
BruteForceSearch::BruteForceSearch()
{
}

BruteForceSearch::BruteForceSearch(TSP &problem)
{
	this->problem = problem;
}

std::pair<std::vector<int>, int> BruteForceSearch::lexicographicOrdering()
{
	first();
	permutation.insert(permutation.begin(), 0);
	TC = problem.countTC(permutation);
	result = permutation;
	permutation.erase(permutation.begin());

	int tempTC;
	while (next()) {

		permutation.insert(permutation.begin(), 0);
		tempTC = problem.countTC(permutation);
		if (tempTC < TC) {
			TC = tempTC;
			result = permutation;
		}
		permutation.erase(permutation.begin());
	}

	return std::pair<std::vector<int>, int>(result, TC);
}

std::pair<std::vector<int>, int> BruteForceSearch::johnsonTrotter()
{
	return std::pair<std::vector<int>, int>();
}

std::pair<std::vector<int>, int> BruteForceSearch::heaps()
{
	first();
	permutation.insert(permutation.begin(), 0);
	TC = problem.countTC(permutation);
	result = permutation;
	permutation.erase(permutation.begin());

	heapPermute(permutation.size(), permutation);

	return std::pair<std::vector<int>, int>(result, TC);
}
