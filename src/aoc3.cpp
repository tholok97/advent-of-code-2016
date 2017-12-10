#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool isTriangle(int x, int y, int z) {
	if ((x + y > z) && (x + z > y) && (z + y > x)) {
		return true;
	} else {
		return false;
	}
}

void part1() {

	ifstream ifs("input/aoc3_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	int x, y, z, cnt = 0;
	while (ifs >> x && ifs >> y && ifs >> z)
		if (isTriangle(x, y, z))
			++cnt;	

	cout << "Svar på part 1: " << cnt << endl;
}

void part2() {
	
	ifstream ifs("input/aoc3_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	int data[3][3], cnt = 0;
	while (	ifs >> data[0][0] && ifs >> data[1][0] && ifs >> data[2][0] &&
			ifs >> data[0][1] && ifs >> data[1][1] && ifs >> data[2][1] &&	
			ifs >> data[0][2] && ifs >> data[1][2] && ifs >> data[2][2]) {
		if (isTriangle(data[0][0], data[0][1], data[0][2]))
			++cnt;
		if (isTriangle(data[1][0], data[1][1], data[1][2]))
			++cnt;
		if (isTriangle(data[2][0], data[2][1], data[2][2]))
			++cnt;
	}

	cout << "Svar på part 2: " << cnt << endl;
}

int main() {

	part1();
	part2();

	return 0;
}
