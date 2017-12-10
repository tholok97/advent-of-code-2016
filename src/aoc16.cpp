#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dargon(vector<bool> &state) {

	vector<bool> b = state;
	reverse(b.begin(), b.end());

	for (size_t i = 0; i < b.size(); ++i)
		b[i] = !b[i];
	
	state.push_back(false);
	state.insert(state.end(), b.begin(), b.end());
}

vector<bool> checksum(vector<bool> state, size_t fileSize) {

	while (state.size() <= fileSize) {
		dargon(state);
	}

	vector<bool> checksum(state);

	checksum.resize(fileSize);

	do {
		vector<bool> nextCheckSum;
		for (size_t i = 0; i < checksum.size(); i += 2) {
			nextCheckSum.push_back(checksum[i] == checksum[i+1]);
		}
		checksum = nextCheckSum;
	} while (checksum.size() % 2 == 0);

	return checksum;
}

int main() {

	int fileSize = 272;	
	vector<bool> state = {0,1,1,1,1,0,0,1,1,0,0,1,1,1,0,1,1};

	cout << "Svaret på part 1: ";
	for (bool bit : checksum(state, fileSize))
		cout << bit;
	cout << endl;


	fileSize = 35651584;
	state = {0,1,1,1,1,0,0,1,1,0,0,1,1,1,0,1,1};

	cout << "Svaret på part 2: ";
	for (bool bit : checksum(state, fileSize))
		cout << bit;

	return 0;
}
