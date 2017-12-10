#include <iostream>
#include <vector>
#include <set>
#include <cstddef>
#include <string>
#include <climits>

using namespace std;

typedef vector<set<string>> Board;

int times = 2;
char tab = ' ';
int minimum = 80;

print(Board b, int current, int depth) {
	for (size_t i = 0; i < b.size(); ++i) {
		cout << string(depth*times, tab) << "F" << i << " |";
		if (current == i) {
			cout << "<\t";
		} else {
			cout << "\t";
		}
		for (string piece : b[i])
			cout << piece << ' ';
		cout << string(depth*times, tab) << endl;
	}
			
}

bool validBoard(Board b) {
	for (set<string> floor : b) {
		for (string p1 : floor) {
			if (p1[1] == 'M') {
				//cout << "FOUND M " << p1 << ", looking for matching G" << endl;
				// let etter matchende generatorer
				bool matchFound = false;
				for (string p2 : floor) {
					if (p2[0] == p1[0] && p2[1] == 'G') {
						//cout << "\tFOUND MATCHING G " << endl;
						matchFound = true;	
					}
				}
				if (!matchFound) {
					//cout << "\tDIDN'T FIND MATCHING G, looking for G'S.." << endl;
					for (string p3 : floor) {
						if (p3[0] != p1[0] && p3[1] == 'G') {
							//cout << "FOUND G " << p3 << " .... DISASTER" << endl;
							return false;
						}
					}
					//cout << "\tNO G'S FOUND :D" << endl;
				}
			}
		}
	}

	return true;
}

bool goalBoard(Board b) {
	for (size_t i = 0; i < b.size()-1; ++i)
		if (!b[i].empty())
			return false;
	return true;
}

Board doMove(string move, Board b, size_t from) {
	char direction = move[0];		
	string p1 = move.substr(1,2);
	string p2 = move.substr(3,2);

	//cout << "move (" << direction << ") with " << p1 << " and " << p2 << endl;

	if (direction == '+') {	
		b[from].erase(p1);
		b[from+1].insert(p1);

		if (p2 != "..") {
			b[from].erase(p2);
			b[from+1].insert(p2);
		}
	} else {
		b[from].erase(p1);
		b[from-1].insert(p1);

		if (p2 != "..") {
			b[from].erase(p2);
			b[from-1].insert(p2);
		}
	}

	return b;
}

int step(Board board, int from, int steps, set<Board> visited) {

	if (steps > minimum-1)
		return -1;

	visited.insert(board);

	vector<string> moves;

	vector<string> pieces;
	for (string piece : board[from]) {
		pieces.push_back(piece);
	}

	for (size_t i = 0; i < pieces.size(); ++i) {
		moves.push_back("+" + pieces[i] + "..");
		moves.push_back("-" + pieces[i] + "..");
		for (size_t j = i+1; j < pieces.size(); ++j) {
			moves.push_back("+" + pieces[i] + pieces[j]);
			moves.push_back("-" + pieces[i] + pieces[j]);
		}
	}

	//cout << string(steps*times, tab) << "Moves: " << endl;
	for (string move : moves) {
		//cout << string(steps*times, tab) << '\t' << move << endl; 

	}
	//print(board, from, steps);
		
	vector<int> routes;
	for (string move : moves) {
		if (!((move[0] == '+' && from > 2) || move[0] == '-' && from < 1)) {

			Board tmp = doMove(move, board, from);
			if (validBoard(tmp) && visited.find(tmp) == visited.end()) {
				//cout << string(steps*times, tab) << "Trying move: " << move << endl;
				if (goalBoard(tmp)) {
					//cout << string(steps*times, tab) << "FOUND THE GOAL (" << steps << ")" << endl;		
					//print(tmp, 3, steps);
					minimum = steps;
					cout << "minimum: " << minimum << endl;
					return steps;
				} else {
					// søk dypere
					char c;
					//cin >> c;
					int ret = -1;
					if (move[0] == '+') {
						ret = step(tmp, from+1, steps+1, visited);
					} else {
						ret = step(tmp, from-1, steps+1, visited);
					}
					if (ret != -1) {
						routes.push_back(ret);
					}
				}
			}
		}
	}
	
	if (!routes.empty()) {
		int min = routes[0];
		for (int route : routes)
			if (route < min)
				min = route;
		return min;
	} else {
		return -1;
	}
}



void part1() {


	Board board(4);

	board[0].insert("1M");
	board[0].insert("1G");

	board[1].insert("2G");
	board[1].insert("3G");
	board[1].insert("4G");
	board[1].insert("5G");

	board[2].insert("2M");
	board[2].insert("3M");
	board[2].insert("4M");
	board[2].insert("5M");

	set<Board> visited;
	
	while (step(board, 0, 1, visited) == -1) {
		++minimum;	
		visited.clear();
		cout << "trying with min: " << minimum << endl;
	}

	cout << "Steps: " << step(board, 0, 1, visited);
}

int main() {

	part1();

	return 0;
}
