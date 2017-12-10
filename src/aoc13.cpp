#include <iostream>
#include <vector>
#include "Dijkstra.h"

using namespace std;

vector<bool> binRep(int num) {
	vector<bool> bin;	// om den er reverse har ingenting å si her

	while (num > 0) {
		bin.push_back(num % 2);
		num /= 2;
	}

	return bin;
}

bool legal(int x, int y) {

	int num = x*x + 3*x + 2*x*y + y + y*y + 1364; // equation + fav number
	
	int count = 0;
	for (bool bit : binRep(num))
		if (bit)
			++count;
	
	return count % 2 == 0;
}

void part1() {
	
	vector<vector<bool>> grid;

	for (size_t i = 0; i < 250; ++i) {
		grid.push_back(vector<bool>());
		for (size_t j = 0; j < 250; ++j) {
			grid[i].push_back(legal(j, i));	
		}
	}

	auto dij = gridToDijkstra(grid);

	if (dij) {
		auto path = dij.findPath({1,1}, {39, 31});
		cout << "Svaret på part 1: " << path.size()-1 << endl;
	}
}

int main() {

	part1();		// løsning på 1 var dijkstra på generert grid. 
	// løsning på 2 var samme men med en maks søkedybde

	return 0;
}
