#include <iostream>
#include <bitset>
#include "CA_2.h"

using namespace std;

bool rules(bool a, bool b, bool c) {
	if ((a == 0 &&  b == 0 && c == 1) || (a == 1 && b == 0 && c == 0) ||
			(a == 0 && b == 1 && c == 1) || (a == 1 && b == 1 && c == 0))
		return false;
	return true;
}

void step(bitset<100> &state) {
	
	bitset<100> next;
	for (size_t i = 0; i < 100; ++i) {
		bool a = (i == 0) ? 1 : state[i-1];
		bool b = state[i];
		bool c = (i == 99) ? 1 : state[i+1];

		next[i] = rules(a, b, c);
	}

	state = next;
}

void print(bitset<100> state) {
	for (size_t i = 0; i < 100; ++i)
		cout << (state[i] ? '.' : '^');
	cout << endl;
}

int numSafe(bitset<100> state) {
	int ret = 0;
	for (size_t i = 0; i < 100; ++i)
		if (state[i])
			++ret;
	return ret;
}

int main() {

	string s = ".^^^.^.^^^^^..^^^..^..^..^^..^.^.^.^^.^^....^.^...^.^^.^^.^^..^^..^.^..^^^.^^...^...^^....^^.^^^^^^^";
	
	for (char &c : s)
		c = (c == '.' ? '1' : '0');
	
	bitset<100> row(s);

	int num = 0;
	for (size_t i = 0; i < 400000; ++i) {		// svaet på part 1 er samme men
		if (i % 10000 == 0)						// med 40
			cout << "at " << i << endl;
		num += numSafe(row);
		step(row);
	}

	cout << num << endl;



	return 0;
}
