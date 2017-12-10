#include <iostream>
#include <string>
#include <vector>
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

string doHash(string s, int n) {
	for (int i = 0; i < n; ++i)
		s = md5(s);
	
	return s;
}

int main() {

	string salt{"yjdafjpo"};
	int hashNum{2017};			// part 2

	cout << "Doing hashes..." << endl;
	vector<string> hashes;				// så hasher bare må regnes ut én gang
	for (size_t i = 0; i < 5000; ++i)
		hashes.push_back(doHash(salt + to_string(i), 2017));

	cout << "Beginning..." << endl;

	int keys{0};

	int i{0};
	while (keys < 64) {
		if (i >= hashes.size()) {
			cout << "filling with hashes... ";
			size_t size = hashes.size();
			for (int k = size; k < size+3000; ++k)
				hashes.push_back(doHash(salt + to_string(k), hashNum));
			cout << " DONE" << endl;
		}
		string hash = hashes[i];

		char c{triplet(hash)};

		if (c != '\0') {
			//cout << "Potential key at " << i << "... ";
			for (int j = i+1; j < i+1001; ++j) {

				if (j >= hashes.size()) {
					cout << "filling with hashes... ";
					size_t size = hashes.size();
					for (int k = size; k < size+3000; ++k)
						hashes.push_back(doHash(salt + to_string(k), hashNum));
					cout << " DONE" << endl;
				}
				
				string checkHash = hashes[j];
				if (fiveOf(c, checkHash)) {
					++keys;
					//cout << "IS THE " << keys << "TH KEY!!";
					cout << "found the " << keys << "th key at " << i << endl;
					if (keys == 64) {
						cout << "Answer: " << i << endl;	
					}
					break;
				}
			}
		}
		++i;
	}

	return 0;
}
