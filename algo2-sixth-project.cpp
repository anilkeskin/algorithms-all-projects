/*
	ANIL KESKÝN - 150170801 - Q3
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
int max_func(int a, int b) { return (a > b) ? a : b; }
pair<int, set<int>> MaxProfit(int numOfCrystals, vector<int> profits, vector<int> entryCosts)
{
	set<int> citiesToVisit;
	int M[profits.size() + 1][numOfCrystals + 1];
	for (int w = 0;w <=numOfCrystals;w++)
	{
		M[0][w] = 0;
	}
	for (unsigned int w = 0;w <=profits.size();w++)
	{
		M[w][0] = 0;
	}
	for (unsigned int i = 1;i <= profits.size();i++)
	{
		for (int w = 1; w <= numOfCrystals;w++)
		{
			if (entryCosts[i-1] > w)
			{
				M[i][w] = M[i - 1][w];
			}
			else
			{
				int value1 = M[i-1][w];
				int value2 = profits[i-1] + M[i-1][w-entryCosts[i-1]];
				M[i][w] = max_func(value1,value2);
			}
		}
	}
	int maxProfit = M[entryCosts.size()][numOfCrystals];
	int i = entryCosts.size();
	int w = numOfCrystals;
	int numOfCities = profits.size();
	while (i > 0 && w > 0)
	{
		if (M[i][w] != M[i-1][w])
		{
			citiesToVisit.insert(i);
			w = w - entryCosts[i-1];
		}
		i = i - 1;
	}
	cout << "Dynaming Programming Table" << endl;
	for (int i = 0; i <= numOfCities; i++) {
		for (int j = 0; j <= numOfCrystals; j++) {
			cout << std::right << std::setw(3) << M[i][j];
		}
		cout << endl;
	}

	return pair<int, set<int>>(maxProfit, citiesToVisit);
}

int main() {
	int numOfCrystals;
	vector<int> profits;
	vector<int> entryCosts;

	//string inputFilename="q3_maxProfit_test1.txt";
	//cout << "Enter the name of the input file: ";
	//cin >> inputFilename;

	string inputFilename;
	cout << "Enter the name of the input file: ";
	cin >> inputFilename;

	ifstream input(inputFilename);

	if (!input.is_open()) {
		cerr << "File named \"" << inputFilename << "\" could not open!" << endl;
		return EXIT_FAILURE;
	}

	string line;
	if (getline(input, line)) {
		numOfCrystals = stoi(line);
	}
	while (getline(input, line, ' ')) {
		profits.push_back(stoi(line));
		getline(input, line);
		entryCosts.push_back(stoi(line));
	}

	pair<int, set<int>> result = MaxProfit(numOfCrystals, profits, entryCosts);

	cout << "Max profit is " << result.first << "." << endl;
	cout << "Cities visited:";
	for (int cityNumber : result.second) {
		cout << " " << cityNumber;
	}
	cout << endl;
}
