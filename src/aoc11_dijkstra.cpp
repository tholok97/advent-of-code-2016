#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "Dijkstra.h"

using namespace std;

typedef vector<set<string>> Board;
typedef pair<int, Board> State;

void addWithDistrubution(set<State> &states, vector<string> pieces, 
		vector<int> distrubution) {
	
	cout << "\tFilling with distrubution:\t";
	for (int i : distrubution)
		cout << i << '\t';
	cout << endl;
	
	vector<string> box = pieces;

	sort(distrubution.begin(), distrubution.end());
	do {	

		sort(box.begin(), box.end());
		do {

			Board board(4);
			
			int mov = 0;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < distrubution[i]; ++j) {
					board[i].insert(box[box.size()-1-mov]);
					++mov;
				}
			}

			for (int i = 0; i < 4; ++i) {
				states.insert(make_pair(i, board));
			}

		} while (next_permutation(box.begin(), box.end()));
	} while (next_permutation(distrubution.begin(), distrubution.end()));

	cout << "\t...filled" << endl;
}

void fillStates(set<State> &states, vector<string> pieces) {

	// hardkodet :/ :)
	addWithDistrubution(states, pieces, {0,0,0,4});
	addWithDistrubution(states, pieces, {0,0,1,3});
	addWithDistrubution(states, pieces, {0,0,2,2});
	addWithDistrubution(states, pieces, {0,1,1,2});
	addWithDistrubution(states, pieces, {1,1,1,1});
}

bool validBoard(Board b) {

	for (set<string> floor : b) {
		for (string p1 : floor) {
			if (p1[1] == 'M') {
				bool matchFound = false;
				for (string p2 : floor) {
					if (p2[0] == p1[0] && p2[1] == 'G') {
						matchFound = true;	
					}
				}
				if (!matchFound) {
					for (string p3 : floor) {
						if (p3[0] != p1[0] && p3[1] == 'G') {
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

bool validState(State state) {

	Board board = state.second;
	
	if (board[state.first].empty())
		return false;

	return validBoard(board);
}

vector<string> calcMoves(set<string> floor) {
	
	vector<string> pieces(floor.begin(), floor.end());
	vector<string> moves;
	
	for (size_t i = 0; i < pieces.size(); ++i) {
		moves.push_back(pieces[i] + "..");
		for (size_t j = i+1; j < pieces.size(); ++j) {
			moves.push_back(pieces[i] + pieces[j]);
		}
	}

	return moves;	
}

void print(State state) {

	int floor = state.first;
	Board board = state.second;
	for (size_t i = 0; i < board.size(); ++i) {
		cout << "F" << i << ":";
		if (floor == i) {
			cout << "<\t";
		} else {
			cout << "\t";
		}
		for (string s : board[i]) {
			cout << s << ' ';
		}
		cout << endl;
	}	
	cout << endl;
}

State doMove(State state, string move, int diff) {

	string p1 = move.substr(0,2);
	string p2 = move.substr(2,2);

	state.second[state.first].erase(p1);
	state.second[state.first+diff].insert(p1);

	if (p2 != "..") {
		state.second[state.first].erase(p2);
		state.second[state.first+diff].insert(p2);
	}

	state.first += diff;

	return state;
}

bool areEqual(State a, State b) {

	if (a.first != b.first)
		return false;
	
	for (size_t i = 0; i < 4; ++i)
		if (a.second[i] != b.second[i])
			return false;

	return true;	
}

void part1() {

	vector<string> pieces = {"1G", "1M", "2G", "2M"};
	vector<string> box = pieces;
	set<State> states;

	cout << "Generating board permutations..." << endl;

	fillStates(states, pieces);

	cout << "...board permutations generated" << endl;
	cout << "Before validation:\t" << states.size() << endl;

	set<State> validones;
	for (State state : states)
		if (validState(state))
			validones.insert(state);
	
	states = validones;

	cout << "After validation:\t" << states.size() << endl;

	auto neighboor = [](State a, State b) -> int {

		int floorDiff = b.first - a.first;

		if (abs(floorDiff) == 1) {
			Board ab = a.second;
			Board bb = b.second;
			vector<string> moves = calcMoves(ab[a.first]);	
			
			for (string move : moves) {
				State tmp = doMove(a, move, floorDiff);
				if (areEqual(tmp, b)) {
					return true;
				}
			}
		}

		return false;
	};

	State start(0, Board(4));

	start.second[0].insert("1M");
	start.second[0].insert("2M");
	start.second[1].insert("1G");
	start.second[2].insert("2G");

	State end(3, Board(4));

	end.second[3].insert("1M");
	end.second[3].insert("1G");
	end.second[3].insert("2M");
	end.second[3].insert("2G");

	cout << "Building graph..." << endl;
	
	Dijkstra<State> dij(states, neighboor);
	
	cout << "...graph built" << endl;
	cout << "Looking for path..." << endl;

	auto path = dij.findPath(start, end);

	cout << "...done looking" << endl;

	if (dij) {
		cout << "Path found is " << (path.size()-1) << " long" << endl;
	} else {
		cout << "ERROR" << endl;
	}
}

int main() {

	part1();

	return 0;
}
