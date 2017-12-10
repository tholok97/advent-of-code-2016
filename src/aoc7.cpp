#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

bool supportsTLS(string addr) {

	vector<string> segments(1);
	bool flag = false;

	for (char c : addr) {
		if (c == '[' || c == ']') {
			segments.push_back("");
		} else {
			segments.back() += c;
		}
	}

	for (int i = 0; i < segments.size(); ++i) {
		string s = segments[i];
		if (s.length() > 3) {
			for (int j = 0; j < s.length()-3; ++j) {
				if (s[j] != s[j+1] && s[j] == s[j+3] && s[j+1] == s[j+2]) {
					if (i % 2 == 0) {
						flag = true;
					} else {
						return false;			// gi opp
					}
				}
			}
		}
	}

	return flag;
}

void part1() {
	
	ifstream ifs("input/aoc7_input.txt");
	if (!ifs) {
		cout << "ERROR!";
		return;
	}

	int num = 0;

	string line;
	while (getline(ifs, line))
		if (supportsTLS(line))
			++num;
	
	cout << "Svaret på part 1: " << num << endl;
}

bool supportsSSL(string addr) {

	vector<string> segments(1);

	for (char c : addr) {
		if (c == '[' || c == ']') {
			segments.push_back("");
		} else {
			segments.back() += c;
		}
	}

	set<string> aba;
	set<string> bab;

	for (int i = 0; i < segments.size(); ++i) {
		string s = segments[i];
		if (s.length() > 2) {
			for (int j = 0; j < s.length()-2; ++j) {
				string tri = s.substr(j,3);
				if (tri[0] != tri[1] && tri[0] == tri[2]) {
					if (i % 2 == 0) {
						aba.insert(tri);
					} else {
						bab.insert(tri);
					}
				}
			}
		}
	}

	for (string tri : aba) {
		string inv = tri.substr(1,1) + tri.substr(0,1) + tri.substr(1,1);
		if (bab.find(inv) != bab.end())
			return true;
	} 
	return false;

	/* DEBUG
	cout << "aba: " << endl;
	for (auto s : aba)
		cout << "\t" << s << endl;
	cout << endl;
	
	cout << "bab: " << endl;
	for (auto s : bab)
		cout << "\t" << s << endl;
	cout << endl;
	*/
}

void part2() {
	
	ifstream ifs("input/aoc7_input.txt");
	if (!ifs) {
		cout << "ERROR!";
		return;
	}

	int num = 0;

	string line;
	while (getline(ifs, line))
		if (supportsSSL(line))
			++num;
	
	cout << "Svaret på part 2: " << num << endl;
}

int main() {

	part1();
	part2();

	return 0;
}
