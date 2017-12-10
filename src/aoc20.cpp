#include <iostream>
#include <fstream>
#include <set>

using namespace std;

bool check(unsigned int test, set<pair<unsigned int, unsigned int>> ranges) {
	for (auto p : ranges)
		if (test >= p.first && test <= p.second)
			return false;
	return true;
}

void part1() {
	
	ifstream ifs("input/aoc20_input.txt");
	if (!ifs) {
		cout << "ERROR" << endl;
		return;
	}

	set<pair<unsigned int, unsigned int>> ranges;

	unsigned int from, to;
	while (ifs >> from) {
		ifs.ignore();
		ifs >> to;

		ranges.insert(make_pair(from, to));
	}

	//for (auto p : ranges)
		//cout << p.first << "\t\t" << p.second << endl;
	
	set<unsigned int> legal;
	for (auto p : ranges)
		if (check(p.second+1, ranges))
			legal.insert(p.second+1);	
	
	cout << "min: " << *(legal.begin()) << endl;
}

int legalOnesFrom(unsigned int start, set<pair<unsigned int, unsigned int>> ranges) {
	
	int num = 0;
	for (unsigned int i = start; i <= 4294967295; ++i) {
		if (check(i, ranges)) {
			++num;
		} else {
			break;
		}
	}

	return num;
}

void part2() {

	ifstream ifs("input/aoc20_input.txt");
	if (!ifs) {
		cout << "ERROR" << endl;
		return;
	}

	set<pair<unsigned int, unsigned int>> ranges;

	unsigned int from, to;
	while (ifs >> from) {
		ifs.ignore();
		ifs >> to;

		ranges.insert(make_pair(from, to));
	}

	//for (auto p : ranges)
		//cout << p.first << "\t\t" << p.second << endl;
	
	int numLegal = 0;
	for (auto p : ranges)
			numLegal += legalOnesFrom(p.second+1, ranges);	
	
	cout << "number of legals: " << numLegal << endl;

}

int main() {

	part1();
	part2();

	return 0;
}
