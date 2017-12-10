#include <iostream>
#include <vector>

using namespace std;

struct Disc {
	int positions;
	int current;

	int step(int n) {
		current += n;
		current %= positions;
		return current;
	}
};

bool isCorrect(vector<Disc> discs, int time) {
	for (size_t i = 0; i < discs.size(); ++i) {
		if (discs[i].step(time+i+1))
			return false;
	}
	return true;
}

void part1() {
	
	vector<Disc> discs = { 
			{5, 2},
			{13, 7},
			{17, 10},
			{3, 2},
			{19, 9},
			{7, 0},
			{11, 0}};		// part 2 legger til denne

	bool success = false;
	int time = 0;
	while (!success) {
		if (isCorrect(discs, ++time))
			success = true;
	}

	cout << "Svaret på part 2: " << time;
}

int main() {

	part1();	

	return 0;
}
