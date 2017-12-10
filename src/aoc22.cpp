#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <utility>
#include <fstream>

using namespace std;

struct Node {
	pair<int, int> pos;
	int size;
	int used;
	int avail;
	int use;
};

bool areEqual(Node a, Node b) {
	if (a.pos == b.pos && a.size == b.size && a.used == b.used &&
			a.avail == b.avail && a.use == b.use)
		return true;
	return false;
}

void part1() {

	fstream ifs("aoc22_input.txt");
	if (!ifs) {
		cout << "ERROR" << endl;
		return;
	}

	vector<Node> nodes;

	string line;
	getline(ifs, line);
	getline(ifs, line);
	while (getline(ifs, line)) {
		istringstream iss(line);
		string s;
		iss >> s;
		size_t i;
		for (i = 0; isdigit(s[i+16]) && i < s.length()-16; ++i);
		size_t j;
		for (j = 0; isdigit(s[i+18+j]) && j < s.length()-18-i; ++j);

		int x = stoi(s.substr(16, i));
		int y = stoi(s.substr(18+i, j));

		iss >> s;
		int size = stoi(s.substr(0, s.length()-1));

		iss >> s;
		int used = stoi(s.substr(0, s.length()-1));

		iss >> s;
		int avail = stoi(s.substr(0, s.length()-1));	

		iss >> s;
		int use = stoi(s.substr(0, s.length()-1));	

		nodes.push_back({{x, y}, size, used, avail, use});
	}


	int num = 0;
	for (const Node &a : nodes) {
		for (const Node &b : nodes) {
			if (a.used != 0 && !areEqual(a, b) && a.used <= b.avail) {
				++num;
			}
		}
	}

	cout << "Answer to part 1: " << num << endl;

	// print infon i en grid og løs for hånd
}

void part2() {
	

	fstream ifs("aoc22_input.txt");
	if (!ifs) {
		cout << "ERROR" << endl;
		return;
	}

	vector<vector<Node>> nodes;
	for (int i = 0; i < 31; ++i) {
		nodes.push_back(vector<Node>());
		for (int j = 0; j < 33; ++j)
			nodes.back().push_back(Node());
	}

	string line;
	getline(ifs, line);
	getline(ifs, line);
	while (getline(ifs, line)) {
		istringstream iss(line);
		string s;
		iss >> s;
		size_t i;
		for (i = 0; isdigit(s[i+16]) && i < s.length()-16; ++i);
		size_t j;
		for (j = 0; isdigit(s[i+18+j]) && j < s.length()-18-i; ++j);

		int x = stoi(s.substr(16, i));
		int y = stoi(s.substr(18+i, j));

		iss >> s;
		int size = stoi(s.substr(0, s.length()-1));

		iss >> s;
		int used = stoi(s.substr(0, s.length()-1));

		iss >> s;
		int avail = stoi(s.substr(0, s.length()-1));	

		iss >> s;
		int use = stoi(s.substr(0, s.length()-1));	

		nodes[y][x] = {{x, y}, size, used, avail, use};
	}

	for (size_t y = 0; y < nodes.size(); ++y) {
		for (size_t x = 0; x < nodes[y].size(); ++x) {
			if (nodes[y][x].size > 100) {
				cout << "# ";
			} else if (nodes[y][x].used == 0) {
				cout << "_ ";
			} else {
				cout << ". ";
			}
		}
		cout << '\n';
	}
}

int main() {

	part1();
	part2();

	return 0;
}
