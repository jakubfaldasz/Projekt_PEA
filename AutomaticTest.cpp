#include "AutomaticTest.h"

AutomaticTest::AutomaticTest()
{
	this->il = new InstanceLoader();
	problemCount = 0;
}

long long AutomaticTest::performTestBnB(int dataSet)
{
	problemCount++;
	tsp = new TSP("data" + std::to_string(dataSet) + ".txt");
	bnb = new BranchNBound(*tsp);

	auto startTime = Clock::now();
	bnb->computeBnB();
	auto endTime = Clock::now();
	
	delete tsp;
	delete bnb;
	return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
}

long long AutomaticTest::performTestBF(int dataSet)
{
	problemCount++;
	tsp = new TSP("data" + std::to_string(dataSet) + ".txt");
	bf = new BruteForceSearch(*tsp);

	auto startTime = Clock::now();
	bf->lexicographicOrdering();
	auto endTime = Clock::now();

	delete tsp;
	delete bf;
	return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
}

long long AutomaticTest::performTestTS(int dataSet, int iteration, int cadency, int epochs, bool aspiracy, bool greedy)
{
	problemCount++;
	tsp = new TSP("data" + std::to_string(dataSet) + ".txt");
	tabu = new TabuSearch(*tsp);

	tabu->setIteration(iteration);
	tabu->setEpochs(epochs);
	tabu->setCadency(cadency);
	tabu->setAspirationCriterion(aspiracy);
	tabu->setGreedy(greedy);
	auto startTime = Clock::now();
	tabu->findBest();
	auto endTime = Clock::now();

	delete tsp;
	delete tabu;
	return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

}

int AutomaticTest::performTourTestTS(int dataSet, int iteration, int cadency, int epochs, bool aspiracy, bool greedy, bool symetric)
{
	problemCount++;
	if(symetric) 
		tsp = new TSP("TSP\\data" + std::to_string(dataSet) + ".txt");
	else
		tsp = new TSP("ATSP\\data" + std::to_string(dataSet) + ".txt");
	tabu = new TabuSearch(*tsp);

	tabu->setIteration(iteration);
	tabu->setEpochs(epochs);
	tabu->setCadency(cadency);
	tabu->setAspirationCriterion(aspiracy);
	tabu->setGreedy(greedy);
	std::vector<int> result = tabu->findBest();
	int tour = tsp->countTC(result);

	delete tsp;
	delete tabu;
	return tour;
}

int AutomaticTest::performTourTestGA(int dataSet, int iteration, int populationSize, int competitionSampleSize, bool mutation, int mutationRange)
{
	problemCount++;
	tsp = new TSP("data" + std::to_string(dataSet) + ".txt");
	ga = new GeneticAlgorithm(*tsp);
	ga->setPopulationSize(populationSize);
	ga->setIterationCount(iteration);
	ga->setMutation(mutation);
	ga->setMutationRange(mutationRange);
	ga->setCompetitionSampleSize(competitionSampleSize);
	std::vector<int> result = ga->compute();
	int tour = tsp->countTC(result);

	delete tsp;
	delete tabu;

	return tour;
}



bool AutomaticTest::performAutoTestBnB(std::string fileName, int maxProblemSize, int howManyTests)
{
	myfile.open(fileName);
	if (myfile.is_open()) {		
		double average;
		long long sum = 0;
		myfile << "problem_size, time[microseconds]\n";
		for (int size = 10; size <= maxProblemSize; size++) {
			if (size == 17 || size == 19 || size == 20) continue;
			if (size == 21)
				howManyTests = 10;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTestBnB(size);
			}
			average = (double)sum / (double)howManyTests;
			myfile << average << "\n";
			sum = 0;
		}

		myfile.close();
		return true;
	}
	else {
		return false;
	}
}

bool AutomaticTest::performAutoTestBF(std::string fileName, int maxProblemSize, int howManyTests)
{
	myfile.open(fileName);
	if (myfile.is_open()) {
		double average;
		long long sum = 0;
		myfile << "problem_size, time[microseconds]\n";
		for (int size = 10; size <= maxProblemSize; size++) {
			if (size == 17 || size == 19 || size == 20) continue;
			if (size == 13)
				howManyTests = 10 ;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTestBF(size);
			}
			average = (double)sum / (double)howManyTests;
			myfile << average << "\n";
			sum = 0;
		}

		myfile.close();
		return true;
	}
	else {
		return false;
	}
}

bool AutomaticTest::performAutoTestTS(std::string fileName, int howManyTests)
{
	myfile.open(fileName);
	int problems[] = { 10,11,12,13,14,15,16,17,18,21,24,26,29,34,36,39,42,43,45,48,53,56,58,65,70,71,100,120,171 };
	if (myfile.is_open()) {
		myfile.imbue(std::locale("Polish_poland"));
		int iteration = 100;
		int cadency;
		int epochs = 5;
		bool greedy = true;
		bool aspiration = true;
		double average;
		long long sum = 0;
		myfile << "problem_size, time[microseconds], iterations, cadency, greedy\n";
		for (auto size : problems) {
			cadency = size;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTestTS(size, iteration, size, epochs, aspiration, greedy);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << average << "; " << iteration << "; " << cadency << "; " << greedy << "\n";
			sum = 0;
		}
		greedy = false;
		for (auto size : problems) {
			cadency = size;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTestTS(size, iteration, size, epochs, aspiration, greedy);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << average << "; " << iteration << "; " << cadency << "; " << greedy << "\n";
			sum = 0;
		}

		myfile.close();
		return true;
	}
	else {
		return false;
	}
}

bool AutomaticTest::performAutoTourTestTS(std::string fileName, int howManyTests)
{
	myfile.open(fileName);
	int asymetricProblems[] = { 11,14,16,17,18,34,36,39,43,45,48,53,56,65,70,71,100,171 };
	int symetricProblems[] = { 10,12,13,15,17,21,24,26,29,42,58,120};

	if (myfile.is_open()) {
		myfile.imbue(std::locale("Polish_poland"));
		bool symetric = false;
		int iteration = 100;
		int cadency;
		int epochs = 5;
		bool greedy = true;
		bool aspiration = true;
		double average;
		long sum = 0;
		myfile << "problem_size; average_cost; iterations; cadency; greedy; symetric\n";
		for (auto size : asymetricProblems) {
			cadency = size;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTourTestTS(size, iteration, (size/10) + 5, epochs, aspiration, greedy, symetric);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << (int) average << "; " << iteration << "; " << cadency << "; " << greedy << ";"<< symetric <<"\n";
			sum = 0;
		}
		greedy = false;
		for (auto size : asymetricProblems) {
			cadency = size;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTourTestTS(size, iteration, (size / 10) + 5, epochs, aspiration, greedy, symetric);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << (int) average << "; " << iteration << "; " << cadency << "; " << greedy << ";" << symetric << "\n";
			sum = 0;
		}

		symetric = true;
		greedy = true;
		for (auto size : symetricProblems) {
			cadency = size;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTourTestTS(size, iteration, (size / 10) + 5, epochs, aspiration, greedy, symetric);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << (int) average << "; " << iteration << "; " << cadency << "; " << greedy << ";" << symetric <<"\n";
			sum = 0;
		}
		greedy = false;
		for (auto size : symetricProblems) {
			cadency = size;
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTourTestTS(size, iteration, (size / 10) + 5, epochs, aspiration, greedy, symetric);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << (int) average << "; " << iteration << "; " << cadency << "; " << greedy << ";" << symetric <<"\n";
			sum = 0;
		}

		myfile.close();
		return true;
	}
	else {
		return false;
	}
}

bool AutomaticTest::performAutoTourTestGA(std::string fileName, int howManyTests)
{
	myfile.open(fileName);
	int problems[] = { 10,11,12,13,14,15,16,17,18,21,24,26,29,34,36,39,42,43,45,48,53,56,58,65,70,71,100,120,171,323,358,403,443};
	
	if (myfile.is_open()) {
		myfile.imbue(std::locale("Polish_poland"));
		int iteration = 100;
		int populationSize = 100;
		int competitionSampleSize = 5;
		bool mutation = true;
		int mutationRange = 10;
		double average;
		long sum = 0;
		myfile << "problem_size; average_cost; iterations; population_size; competition_sample_size; mutation; mutation_range\n";
		for (auto size : problems) {
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTourTestGA(size, iteration, populationSize, competitionSampleSize, mutation, mutationRange);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << (int)average << "; "<<  iteration <<"; " << populationSize << "; " << competitionSampleSize << "; " << mutation << ";" << mutationRange << "\n";
			sum = 0;
		}
		mutation = false;
		for (auto size : problems) {
			myfile << size << "; ";
			for (int i = 0; i < howManyTests; i++) {
				sum += performTourTestGA(size, iteration, populationSize, competitionSampleSize, mutation, mutationRange);
			}
			average = (double)sum / (double)howManyTests;
			myfile << std::fixed << std::setprecision(2) << (int)average << "; " << iteration << "; " << populationSize << "; " << competitionSampleSize << "; " << mutation << ";" << mutationRange << "\n";
			sum = 0;
		}
		
		myfile.close();
		return true;
	}
	else {
		return false;
	}
}
