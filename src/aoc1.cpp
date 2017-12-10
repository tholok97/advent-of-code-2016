#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <utility>
#include <vector>

using namespace std;


int main() {

	enum Dir {NORTH, SOUTH, EAST, WEST};

	string input("L1, L5, R1, R3, L4, L5, R5, R1, L2, L2, L3, R4, L2, R3, R1, L2, R5, R3, L4, R4, L3, R3, R3, L2, R1, L3, R2, L1, R4, L2, R4, L4, R5, L3, R1, R1, L1, L3, L2, R1, R3, R2, L1, R4, L4, R2, L189, L4, R5, R3, L1, R47, R4, R1, R3, L3, L3, L2, R70, L1, R4, R185, R5, L4, L5, R4, L1, L4, R5, L3, R2, R3, L5, L3, R5, L1, R5, L4, R1, R2, L2, L5, L2, R4, L3, R5, R1, L5, L4, L3, R4, L3, L4, L1, L5, L5, R5, L5, L2, L1, L2, L4, L1, L2, R3, R1, R1, L2, L5, R2, L3, L5, L4, L2, L1, L2, R3, L1, L4, R3, R3, L2, R5, L1, L3, L3, L3, L5, R5, R1, R2, L3, L2, R4, R1, R1, R3, R4, R3, L3, R3, L5, R2, L2, R4, R5, L4, L3, L1, L5, L1, R1, R2, L1, R3, R4, R5, R2, R3, L2, L1, L5");

	istringstream iss(input);

	Dir dir = NORTH;
	int r = 0, c = 0;

	string cmd;
	while (iss >> cmd) {
		if (cmd.length() < 2) {
			cout << "ERROR";
			return 0;
		}

		char turn = cmd[0];
		int steps = stoi(string(++cmd.begin(), cmd.end()));	
		cout << turn << ": " << steps << endl;

		if (turn == 'L') {
			switch(dir) {
				case NORTH:		dir = WEST;		break;
				case EAST:		dir = NORTH;	break;
				case SOUTH:		dir = EAST;		break;
				case WEST:		dir = SOUTH;	break;
			}
		} else if (turn == 'R') {
			switch(dir) {
				case NORTH:		dir = EAST;		break;
				case EAST:		dir = SOUTH;	break;
				case SOUTH:		dir = WEST;		break;
				case WEST:		dir = NORTH;	break;
			}
		}
		
		switch(dir) {
			case NORTH:		c -= steps;		break;
			case EAST:		r += steps;		break;
			case SOUTH:		c += steps;		break;
			case WEST:		r -= steps;		break;
		}
	}

	if (r < 0)
		r *= -1;
	
	if (c < 0)
		c *= -1;
	
	int dist = r + c;


	cout << dist << endl;



	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";

	// PART 2
	

	iss.str(input);
	iss.clear();
	r = 0;
	c = 0;

	vector<pair<int, int>> vec;
	vec.push_back(make_pair(0, 0));

	while (iss >> cmd) {
		if (cmd.length() < 2) {
			cout << "ERROR";
			return 0;
		}

		char turn = cmd[0];
		int steps = stoi(string(++cmd.begin(), cmd.end()));	

		if (turn == 'L') {
			switch(dir) {
				case NORTH:		dir = WEST;		break;
				case EAST:		dir = NORTH;	break;
				case SOUTH:		dir = EAST;		break;
				case WEST:		dir = SOUTH;	break;
			}
		} else if (turn == 'R') {
			switch(dir) {
				case NORTH:		dir = EAST;		break;
				case EAST:		dir = SOUTH;	break;
				case SOUTH:		dir = WEST;		break;
				case WEST:		dir = NORTH;	break;
			}
		}

		for (int i = 0; i < steps; ++i) {
			switch (dir) {
				case NORTH:		c -= 1;		break;
				case EAST:		r += 1;		break;
				case SOUTH:		c += 1;		break;
				case WEST:		r -= 1;		break;
			}
		
			vec.push_back(make_pair(r, c));
		}
		
	}

	set<pair<int, int>> marked;

	for (int i = 0; i < vec.size(); ++i) {
		if (marked.find(vec[i]) != marked.end()) {
			cout << "answer is: " << vec[i].first << ",  " << vec[i].second << ": ";
			if (vec[i].first < 0)
				vec[i].first *= -1;
			if (vec[i].second < 0)
				vec[i].second *= -1;
			cout << (vec[i].first + vec[i].second);
		} else {
			marked.insert(vec[i]);
		}
	}

	if (r < 0)
		r *= -1;
	
	if (c < 0)
		c *= -1;

	cout << (r + c);

	

	return 0;
}
