#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

class InstanceLoader
{
	int problemSize;
	std::string instanceName;
	std::vector<std::vector<int>> instance;
public:
	InstanceLoader();

	std::vector<std::vector<int>> loadInstance(std::string filePath);
	std::vector<std::vector<int>> generateRandomInstance(int size, int minWeight, int maxWeight, int instanceId, bool symetrical);

	int getProblemSize();
	std::string getInstanceName();
	static void displayInstance(std::vector<std::vector<int>> instance, std::string instanceName, int problemSize, int TC);
};

