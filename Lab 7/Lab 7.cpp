#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

mt19937 random_mt;

struct State {
	string state;
	int capitaIncome;
	unsigned int population;
	int medianIncome;
	unsigned int numHouseholds;

	State(string state = 0, int capitaIncome = 0, unsigned int population = 0, int medianIncome = 0, unsigned int numHouseholds = 0) {
		this->state = state;
		this->capitaIncome = capitaIncome;
		this->population = population;
		this->medianIncome = medianIncome;
		this->numHouseholds = numHouseholds;
	}
};

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides) {
	map<int, int> diceMap;
	unsigned int roll;
	unsigned int counter = 0;

	for (int i = 1; i <= numberOfSides; i++) {
		diceMap.emplace(i, 0);
	}

	for (int i = 0; i < numberOfRolls; i++) {
		roll = Random(1, numberOfSides);
		diceMap.emplace(roll, counter++);
		diceMap[roll] += 1;
	}

	map<int, int>::iterator iter;

	for (iter = diceMap.begin(); iter != diceMap.end(); iter++) {
		cout << endl;
		cout << iter->first << ": " << iter->second;
	}
}


int main() {
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
		// user input
		int numberOfRolls;
		cin >> numberOfRolls;

		cout << "Number of sides on this die: ";
		// user input
		int numberOfSides;
		cin >> numberOfSides;

		// Roll Dice
		RollDice(numberOfRolls, numberOfSides);

	}

	else if (option == 2)
	{
		// Load the states
		ifstream file;
		file.open("states.csv");
		string line;
		string state;
		int capitaIncome;
		unsigned int population;
		int medianIncome;
		unsigned int numHouseholds;
		map<string, State> stateMap;

		getline(file, line);

		if (file.is_open()) {
			while (getline(file, line)) {
				stringstream parse(line);
				getline(parse, line, ',');
				state = line;
				getline(parse, line, ',');
				capitaIncome = stoi(line);
				getline(parse, line, ',');
				population = stoi(line);
				getline(parse, line, ',');
				medianIncome = stoi(line);
				getline(parse, line, ',');
				numHouseholds = stoi(line);
				State temp(state, capitaIncome, population, medianIncome, numHouseholds);
				stateMap.emplace(state, temp);
			}
			// Get input for option 1 (show all states) or 2 (do a search for a particular state)
			cout << "1. Print all states\n";
			cout << "2. Search for a state\n";

			int choice;
			cin >> choice;

			if (choice == 1) {
				map<string, State>::iterator iter2;
				for (iter2 = stateMap.begin(); iter2 != stateMap.end(); iter2++) {
					cout << endl;
					cout << iter2->first << endl;
					cout << "Population: " << iter2->second.population << endl;
					cout << "Per Capita Income: " << iter2->second.capitaIncome << endl;
					cout << "Median Household Income: " << iter2->second.medianIncome << endl;
					cout << "Number of Households :" << iter2->second.numHouseholds << endl;
				}
			}

			else if (choice == 2) {
				string searchState;
				cin >> searchState;
				if (stateMap.find(searchState) == stateMap.end()) {
					cout << "No match found for " << searchState << endl;
				}
				else {
					cout << searchState << endl;
					cout << "Population: " << stateMap[searchState].population << endl;
					cout << "Per Capita Income: " << stateMap[searchState].capitaIncome << endl;
					cout << "Median Household Income: " << stateMap[searchState].medianIncome << endl;
					cout << "Number of Households :" << stateMap[searchState].numHouseholds << endl;
				}
			}
		}
		file.close();
	}
	return 0;
}