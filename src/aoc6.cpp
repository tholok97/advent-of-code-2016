#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void part1() {

	const int cols = 8;

	ifstream ifs("input/aoc6_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	map<char, int> maps[cols];

	string line;
	while (getline(ifs, line)) {
		
		for (int i = 0; i < cols; ++i) {
			++maps[i][line[i]];
		}
	}

	string message;
	for (int i = 0; i < cols; ++i) {
		
		vector<pair<char, int>> vec;
		for (auto p : maps[i])
			vec.push_back(p);

		sort(vec.begin(), vec.end(), [](const pair<char, int> &p1, 
				const pair<char, int> &p2) { return p1.second > p2.second; });

		message += vec[0].first;
	}

	cout << "Svaret på part 1:" << message << endl;
}

void part2() {

	const int cols = 8;

	ifstream ifs("input/aoc6_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	map<char, int> maps[cols];

	string line;
	while (getline(ifs, line)) {
		
		for (int i = 0; i < cols; ++i) {
			++maps[i][line[i]];
		}
	}

	string message;
	for (int i = 0; i < cols; ++i) {
		
		vector<pair<char, int>> vec;
		for (auto p : maps[i])
			vec.push_back(p);

		// < ENESTE FORSKJELL XD
		sort(vec.begin(), vec.end(), [](const pair<char, int> &p1, 
				const pair<char, int> &p2) { return p1.second < p2.second; });

		message += vec[0].first;
	}

	cout << "Svaret på part 2:" << message << endl;
}

int main() {

	part1();
	part2();

	return 0;
}
