#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming(TSP& problem)
{
	this->problem = problem;
	this->matrix = problem.getAdjacencyMatrix();
}

std::pair<std::vector<int>,int> DynamicProgramming::countDP() 
{
	std::vector<int> vertexes;
	for (int i = 1; i < matrix.size(); i++) 
		vertexes.push_back(i);
	
	return std::pair<std::vector<int>,int>(route,solve(0, vertexes));
}

int DynamicProgramming::solve(int vertex, std::vector<int> remaining)
{
	if (remaining.size() == 0)
		return matrix[vertex][0];
	else {
		std::vector<int> temp = remaining;
		std::vector<std::pair<int,int>> results;
		for (int i = 0; i < remaining.size(); i++) {
			deleteElementByValue(temp, remaining[i]);
			results.push_back(std::pair<int,int>(solve(remaining[i], temp) + matrix[vertex][remaining[i]], remaining[i]));
			temp = remaining;
		}

		int index = findMin(results);
	
		return results[index].first;
	}
}

int DynamicProgramming::findMin(std::vector<std::pair<int, int>> array)
{
	int k = INT_MAX;
	int index;
	for (int i = 0; i < array.size(); i++) {
		if (array[i].first < k) {
			k = array[i].first;
			index = i;
		}
	}
	return index;
}


void DynamicProgramming::deleteElementByValue(std::vector<int>& array, int value)
{
	array.erase(std::remove(array.begin(), array.end(), value), array.end());
}
