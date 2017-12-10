#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include "md5.h"

using namespace std;

char triplet(string s) {
	for (size_t i = 0; i < s.size()-2; ++i)
		if (s[i] == s[i+1] && s[i] == s[i+2])
			return s[i];
	return '\0';
}

bool fiveOf(char c, string s) {
	for (size_t i = 0; i < s.size()-4; ++i)
		if (s.substr(i, 5) == string(5, c))
			return true;
	return false;
}

void part1() {

	string salt = "yjdafjpo";

	set<pair<int, char>> check;

	int numKey = -1;
	
	int i = 0, keys = 0;
	while (numKey == -1) {
		
		string hash = md5(salt + to_string(i));
		char c = triplet(hash);
		if (c != '\0') {
			check.insert(make_pair(i, c));
			//cout << "Found key at " << i << endl;
		}

		set<pair<int, char>> toErase;
		for (auto p : check) {
			if (p.first != i && i < p.first + 1000) {
				if (fiveOf(p.second, hash)) {
						toErase.insert(p);
						++keys;
						cout << "Confirmed key nr. " << keys << " (" << 
								p.first << ") at: " << i << endl;
						if (keys == 64)
							numKey = p.first;
					}
				}
		}

		for (auto p : toErase)
			check.erase(p);

		++i;
	}

	cout << "Svaret på part 1: " << numKey << endl;
}

string doHash(string s, int n) {
	for (int i = 0; i < n; ++i)
		s = md5(s);
	
	return s;
}

void part2() {

	string salt = "yjdafjpo";

	vector<pair<int, char>> check;

	int numKey = -1;
	
	int i = 0, keys = 0;
	while (numKey == -1) {
		
		string hash = doHash(salt + to_string(i), 2017);
		char c = triplet(hash);
		if (c != '\0') {
			check.push_back(make_pair(i, c));
			//cout << "Found key at " << i << endl;
		}

		set<decltype(check.begin())> toErase;
		for (size_t j = 0; j < check.size(); ++j) {
			auto p = check[j];
			if (p.first < i && i < p.first + 1000) {
				if (fiveOf(p.second, hash)) {
					toErase.insert(check.begin() + i);
					++keys;
					cout << "Confirmed key nr. " << keys << " (" << 
							p.first << ") at: " << i << endl;
					if (keys == 64)
						numKey = p.first;
					}
				}
		}

		for (auto p : toErase)
			check.erase(p);

		++i;
	}

	cout << "Svaret på part 2: " << numKey << endl;
}

int main() {

//	part1();
	part2();

	return 0;
}
