#include <iostream>
#include <fstream>
#include <vector>
#include "InstanceLoader.h"
#include "TSP.h"
#include "BruteForceSearch.h"
#include <conio.h>
#include <stdlib.h>
#include "DynamicProgramming.h"
#include "BranchNBound.h"
#include "AutomaticTest.h"
#include "TabuSearch.h"
#include <algorithm>
#include "GeneticAlgorithm.h"

void displayMenu();
void displayPermutation(std::vector<int> permutation);

int main() {

	srand(time(NULL));
	char choice;
	TSP* tsp = nullptr;

	do {
		displayMenu();
		choice = _getch();

		switch (choice) {
		case '1':
		{
			system("CLS");
			std::cout << "1. Wczytaj instancje z pliku.\n\n";
			std::string filePath;
			std::cout << "Podaj nazwe/sciezke pliku do wczytania.\n";
			std::cin >> filePath;
			tsp = new TSP(filePath);

			if (tsp->isLoadedProperly()) {
				std::cout << "Wczytanie danych powiodlo sie\n";
			}
			else {
				std::cout << "Nie udalo sie wczytac danych\n";
			}
			_getch();
			system("CLS");
			break;
		}
		case '2':
		{
			system("CLS");
			std::cout << "2. Wygeneruj losowy zestaw danych.\n\n";
			int size, minWeight, maxWeight, instanceId;
			bool symetrical = false;

			std::cout << "Podaj wielkosc problemu: \n";
			while (!(std::cin >> size) || size<0) {
				std::cout << "Blad\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "Podaj minimalna wage krawedzi: \n";
			while (!(std::cin >> minWeight) || minWeight < 0) {
				std::cout << "Bledna wartosc!\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "Podaj maksymalna wage krawedzi: \n";
			while (!(std::cin >> maxWeight) || maxWeight < minWeight) {
				std::cout << "Bledna wartosc!\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "Podaj identyfikator problemu: \n";
			while (!(std::cin >> instanceId)) {
				std::cout << "Bledna wartosc!\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::cout << "Czy problem ma byc symetryczny? (T/N)\n";
			std::string choice;
			std::cin >> choice;
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			while (choice[0] != 'n' && choice[0] != 't') {
				std::cout << "Bledna wartosc!\n";
				std::cout << "Czy problem ma byc symetryczny? (T/N)\n";
				std::cin >> choice;
				std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			}
			if (choice[0] == 't')
				symetrical = true;
			else if (choice[0] == 'n')
				symetrical = false;


			tsp = new TSP(size, minWeight, maxWeight, instanceId, symetrical);
			if (tsp->isLoadedProperly()) {
				std::cout << "Wygenerowanie danych powiodlo sie\n";
			}
			else {
				std::cout << "Nie udalo sie wygenerowac danych\n";
			}
			_getch();
			system("CLS");

			break;
		}
		case '3':
		{
			if (tsp == nullptr || !(tsp->isLoadedProperly())) {
				std::cout << "Nie wczytano instancji!\n";
				_getch();
				system("CLS");
				break;
			}
			char subChoice;
			std::cout << "1. Wpisz recznie permutacje\n";
			std::cout << "2. Policz dla kolejnych wierzcholkow po kolei\n";
			std::cout << "0. Wyjscie\n";

			subChoice = _getch();
			while (subChoice != '0') {
				switch (subChoice) {
				case '1':
				{
					system("CLS");
					std::cout << "Policz funkcje celu\n";
					std::cout << "1. Wpisz recznie permutacje\n";
					std::vector<int> permutation(tsp->getProblemSize());
					
					for (int i = 0; i < permutation.size(); i++) {
			system("CLS");
			std::cout << "3. Policz funkcje celu.\n\n";
						std::cout << "#" << i << " wierzcholek: " << std::endl;
						while (!(std::cin >> permutation[i]) || permutation[i] < 0 || permutation[i] >= permutation.size()) {
							std::cout << "Bledna wartosc\n";
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}

					tsp->countTC(permutation);
					std::cout << "TC: " << tsp->getTC() << "\n";
					_getch();
					subChoice = '0';
					system("CLS");
					break;
				}
				case '2':
				{
					system("CLS");
					std::cout << "Policz funkcje celu\n";
					std::cout << "2. Policz dla kolejnych wierzcholkow po kolei\n";
					std::vector<int> permutation(tsp->getProblemSize());
					std::generate(permutation.begin(), permutation.end(), [n = 0]() mutable { return n++; });
					tsp->countTC(permutation);
					std::cout << "TC: " << tsp->getTC() << "\n";
					_getch();
					subChoice = '0';
					system("CLS");
					break;
				}
				case '0':
					system("CLS");
					break;
				default:
				{
					std::cout << "Bledny wybor!\n";
					system("CLS");
					break;
				}
				}
			}
			break;
		}
		case '4':
		{
			system("CLS");
			std::cout << "4. Wyswietl instancje.\n\n";
			if (tsp == nullptr || !(tsp->isLoadedProperly())) {
				std::cout << "Nie wczytano instancji!\n";
				_getch();
				system("CLS");
				break;
			}

			tsp->displayInstance();
			_getch();
			system("CLS");
			break;
		}
		case '5':
		{

			system("CLS");
			std::cout << "5. Metody dokladne.\n\n";
			if (tsp == nullptr || !(tsp->isLoadedProperly())) {
				std::cout << "Nie wczytano instancji!\n";
				_getch();
				system("CLS");
				break;
			}

			char subChoice;
			std::cout << "1. Przeglad zupelny (Lexicographic order)\n";
			std::cout << "2. Przeglad zupelny (Heap's algorithm)\n";
			std::cout << "3. Programowanie dynamiczne\n";
			std::cout << "4. Branch and bound\n";
			std::cout << "0. Wyjscie\n";

			subChoice = _getch();
			system("CLS");
			while (subChoice != '0') {
				switch (subChoice) {
				case '1':
				{
					system("CLS");
					BruteForceSearch bt(*tsp);
					std::pair<std::vector<int>, int> result;
					result = bt.lexicographicOrdering();
					tsp->setTC(result.second);

					tsp->displayInstance();
					displayPermutation(result.first);
					_getch();
					system("CLS");
					subChoice = '0';
					break;
				}
				case '2':
				{
					system("CLS");
					BruteForceSearch bt(*tsp);
					std::pair<std::vector<int>, int> result;
					result = bt.heaps();
					tsp->setTC(result.second);

					tsp->displayInstance();
					displayPermutation(result.first);
					_getch();
					system("CLS");
					subChoice = '0';
					break;
				}
				case '3':
				{
					system("CLS");
					DynamicProgramming dp(*tsp);
					std::pair<std::vector<int>, int> result;
					result = dp.countDP();
					tsp->setTC(result.second);
					tsp->displayInstance();
					displayPermutation(result.first);
					_getch();
					system("CLS");
					subChoice = '0';
					break;
				}
				case '4':
				{
					system("CLS");
					BranchNBound bnb(*tsp);
					std::pair<std::vector<int>, int> result;
					result = bnb.computeBnB();					

					tsp->setTC(result.second);
					tsp->displayInstance();
					displayPermutation(result.first);
					_getch();
					system("CLS");
					subChoice = '0';
					break;
				}
				case '0':
				{
					system("CLS");
					break;
				}
				default:
				{
					std::cout << "Bledny wybor!\n";
					system("CLS");
					break;
				}
				}
			}

			
			break;
		}
		case '6':
		{

			system("CLS");
			std::cout << "Heurystyka.\n\n";
			if (tsp == nullptr || !(tsp->isLoadedProperly())) {
				std::cout << "Nie wczytano instancji!\n";
				_getch();
				system("CLS");
				break;
			}

			char subChoice;
			std::cout << "1. Tabu Search\n";
			std::cout << "2. Algorytm genetyczny\n";
			std::cout << "0. Wyjscie\n";

			subChoice = _getch();
			system("CLS");
			while (subChoice != '0') {
				switch (subChoice) {
				case '1':
				{
					system("CLS");
					TabuSearch ts(*tsp);
					std::vector<int> result;
					result = ts.findBest();
					int resultCost = tsp->countTC(result);

					tsp->setTC(resultCost);
					std::cout << "Cost: " << resultCost;
					displayPermutation(result);
					_getch();
					system("CLS");
					subChoice = '0';
					break;
				}
				case '2':
				{
					system("CLS");
					GeneticAlgorithm ga(*tsp);
					std::vector<int> result;
					ga.setMutation(true);
					result = ga.compute();
					int resultCost = tsp->countTC(result);

					tsp->setTC(resultCost);
					std::cout << "Cost with mutation: " << resultCost;
					displayPermutation(result);
					ga = GeneticAlgorithm(*tsp);
					ga.setMutation(false);
					result = ga.compute();
					resultCost = tsp->countTC(result);

					tsp->setTC(resultCost);
					std::cout << "Cost without mutation: " << resultCost;
					displayPermutation(result);
					_getch();
					system("CLS");
					subChoice = '0';
					break;
				}
				case '0':
				{
					system("CLS");
					break;
				}
				default:
				{
					std::cout << "Bledny wybor!\n";
					system("CLS");
					break;
				}
				}
			}


			break;
		}
		case '7':
		{
			system("CLS");
			std::cout << "Testy automatyczne\n\n";
			std::cout << "1. Branch and bound\n";
			std::cout << "2. Brute Force\n";
			std::cout << "3. Tabu Search\n";
			std::cout << "4. Genetic Algorithm\n";
			std::cout << "0. Powrot\n";
			 
			AutomaticTest at;
			char subChoice;
			subChoice = _getch();
			system("CLS");
			while (subChoice != '0') {
				switch (subChoice) {
				case '1': 
				{
					std::string fileName;
					int howManyTests, maxProblemSize;
					std::cout << "Podaj nazwe pliku do zapisu pomiarow\n";
					std::cin >> fileName;
					std::cout << "Podaj ilosc testow\n";
					std::cin >> howManyTests;
					std::cout << "Podaj maksymalna wielkosc problemu\n";
					std::cin >> maxProblemSize;

					if (at.performAutoTestBnB(fileName, maxProblemSize, howManyTests)) {
						std::cout << "Pomyslnie wygenerowano pomiary\n";
					}
					else {
						std::cout << "Nie udalo sie wygenerowac pomiarow\n";
					}				

					subChoice = '0';
					break;
				}
				case '2':
				{
					std::string fileName;
					int howManyTests, maxProblemSize;
					std::cout << "Podaj nazwe pliku do zapisu pomiarow\n";
					std::cin >> fileName;
					std::cout << "Podaj ilosc testow\n";
					std::cin >> howManyTests;
					std::cout << "Podaj maksymalna wielkosc problemu\n";
					std::cin >> maxProblemSize;

					if (at.performAutoTestBF(fileName, maxProblemSize, howManyTests)) {
						std::cout << "Pomyslnie wygenerowano pomiary\n";
					}
					else {
						std::cout << "Nie udalo sie wygenerowac pomiarow\n";
					}

					subChoice = '0';
					break;
				}
				case '3':
				{
					std::string fileName;
					int howManyTests, maxProblemSize ,iteration;
					std::cout << "Podaj nazwe pliku do zapisu pomiarow\n";
					std::cin >> fileName;
					std::cout << "Podaj ilosc testow\n";
					std::cin >> howManyTests;

					if (at.performAutoTourTestTS(fileName, howManyTests)) {
						std::cout << "Pomyslnie wygenerowano pomiary\n";
					}
					else {
						std::cout << "Nie udalo sie wygenerowac pomiarow\n";
					}

					subChoice = '0';
					break;
				}
				case '4':
				{
					std::string fileName;
					int howManyTests, maxProblemSize;
					std::cout << "Podaj nazwe pliku do zapisu pomiarow\n";
					std::cin >> fileName;
					std::cout << "Podaj ilosc testow\n";
					std::cin >> howManyTests;

					if (at.performAutoTourTestGA(fileName, howManyTests)) {
						std::cout << "Pomyslnie wygenerowano pomiary\n";
					}
					else {
						std::cout << "Nie udalo sie wygenerowac pomiarow\n";
					}

					subChoice = '0';
					break;
				}
				}
			}

			_getch();
			system("CLS");
			break;
		}
		case '0':
		{
			break;
		}
		default:
		{
			std::cout << "Nieznany wybor.\n";
			_getch();
			system("CLS");
			break;
		}

		}


	} while (choice != '0');
	
	delete tsp;

	exit(0);
	return 0;
}

void displayMenu() {
	std::cout << "-----------------------------\n";
	std::cout << "-------- PROJEKT PEA --------\n";
	std::cout << "--------     TSP     --------\n";
	std::cout << "-----------------------------\n\n";
	std::cout << "Wybierz opcje:\n";
	std::cout << "1. Wczytaj instancje z pliku.\n";
	std::cout << "2. Wygeneruj losowy zestaw danych.\n";
	std::cout << "3. Policz funkcje celu.\n";
	std::cout << "4. Wyswietl instancje.\n";
	std::cout << "5. Metody dokladne.\n";
	std::cout << "6. Heurystyka.\n";
	std::cout << "7. Testy automatyczne.\n";
	std::cout << "0. Wyjscie z programu.\n";
}

void displayPermutation(std::vector<int> permutation) {
	std::cout << "\nRozwiazanie problemu:\n\n";
	for (int i = 0; i < permutation.size(); i++) {
		if (i == permutation.size() - 1) 
			std::cout << permutation[i];
		else
			std::cout << permutation[i] << "-";
	}
	std::cout << "\n";
}
