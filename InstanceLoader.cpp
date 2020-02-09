#include "InstanceLoader.h"

InstanceLoader::InstanceLoader()
{
	srand(time(NULL));
}

std::vector<std::vector<int>> InstanceLoader::loadInstance(std::string filePath)
{
	std::ifstream fileStream;
	fileStream.open(filePath);
	if (fileStream.is_open()) {
		fileStream >> instanceName;
		fileStream >> problemSize;

		std::vector<std::vector<int>> adjacencyMatrix(problemSize, std::vector<int>(problemSize,0));

		for (int i = 0; i < problemSize; i++) {
			for (int j = 0; j < problemSize; j++) {
				fileStream >> adjacencyMatrix[i][j];
			}
		}

		instance = adjacencyMatrix;

		return adjacencyMatrix;		
	}
	else {
		return std::vector<std::vector<int>>();
	}
}

std::vector<std::vector<int>> InstanceLoader::generateRandomInstance(int size, int minWeight, int maxWeight, int instanceId, bool symetrical)
{
	if (size <= 0 || minWeight > maxWeight) {
		return std::vector<std::vector<int>>();
	}

	instanceName = "Random instance #" + std::to_string(instanceId);
	problemSize = size;

	std::vector<std::vector<int>> adjacencyMatrix(problemSize, std::vector<int>(problemSize, 0));

	if (symetrical) {
		int move = 0;
		for (int i = 0; i < problemSize; i++) {
			for (int j = 0 + move; j < problemSize; j++) {
				if (i == j) {
					adjacencyMatrix[i][j] = -1;
				}
				else {
					int value = rand() % maxWeight + minWeight;
					adjacencyMatrix[i][j] = value;
					adjacencyMatrix[j][i] = value;
				}
			}
			move++;
		}
	}
	else {
		for (int i = 0; i < problemSize; i++) {
			for (int j = 0; j < problemSize; j++) {
				if (i == j) {
					adjacencyMatrix[i][j] = -1;
				}
				else {
					int value = rand() % maxWeight + minWeight;
					adjacencyMatrix[i][j] = value;
				}
			}
		}
	}

	instance = adjacencyMatrix;
	return adjacencyMatrix;
}

int InstanceLoader::getProblemSize()
{
	return problemSize;
}

std::string InstanceLoader::getInstanceName()
{
	return instanceName;
}

void InstanceLoader::displayInstance(std::vector<std::vector<int>> instance, std::string instanceName, int problemSize, int TC)
{
	std::cout << instanceName << "\nWielkosc instancji: " << problemSize << "\nTC:" << TC << "\n\n";
	for (int i = 0; i < problemSize; i++) {
		for (int j = 0; j < problemSize; j++) {
			if (instance[i][j] / 10 > 0 || instance[i][j] < 0) {
				if (instance[i][j] / 100 > 0) {
					std::cout << instance[i][j] << " ";
				}
				else {
					std::cout << " " << instance[i][j] << " ";
				}
			}
			else {
				std::cout << "  " << instance[i][j] << " ";
			}
		}

		std::cout << std::endl;
	}
}
