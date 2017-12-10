#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

typedef set<string> Floor;		// set<(pair<char, enum>?)>
typedef vector<Floor> Board;	// burde være std::array
typedef pair<int, Board> State;

bool validBoard(Board b) {

	for (Floor floor : b) {
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

vector<string> calcMoves(Floor floor) {
	
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


set<State> equivStates(State state) {

	State original = state;
	
	vector<pair<string, string>> pairs;
	size_t distrubution[] = {state.second[0].size(), state.second[1].size(),
			state.second[2].size(), state.second[3].size()};

	for (Floor &floor : state.second) {

		set<pair<string, string>> floorPairs;
		for (string object : floor) {

			string match = object.substr(0,1) + 
					((object[1] == 'G') ? "M" : "G");
			if (floor.find(match) != floor.end()) {
				if (floorPairs.find(make_pair(match, object)) == floorPairs.end())
					floorPairs.insert(make_pair(object, match));
			}
		}
		for (pair<string, string> aPair : floorPairs) {

			floor.erase(aPair.first);	
			floor.erase(aPair.second);	
			pairs.push_back(aPair);
		}
	}


	set<State> equivs;

	sort(pairs.begin(), pairs.end());
	do {

		State equiv = state;
		vector<pair<string, string>> box = pairs;

		for (size_t i = 0; i < 4; ++i) {
			Floor &floor = equiv.second[i];
			while (floor.size() < distrubution[i]) {
				floor.insert(box.back().first);
				floor.insert(box.back().second);
				box.pop_back();
			}
		}

		equivs.insert(equiv);
	} while (next_permutation(pairs.begin(), pairs.end()));

	equivs.erase(original);
	
	return equivs;
}

bool equivExcists(State state, set<State> &states) {

	for (State equiv : equivStates(state))
		if (states.find(state) != states.end())
			return true;
	return false;
}

set<State> generateNeighboors(State state) {

	set<State> neighboors;
	
	for (string move : calcMoves(state.second[state.first])) {
		if (state.first > 0) {
			State neighboor = doMove(state, move, -1);
			if (validState(neighboor))
				neighboors.insert(neighboor);
		}
		if (state.first < 3) {
			State neighboor = doMove(state, move, +1);
			if (validState(neighboor))
				neighboors.insert(neighboor);
		}
	}

	return neighboors;
}

int shortestRoute(State start, State end) {

	State current;					// noden som evalueres.
	std::map<State, int> dist;		// distanse fra start til [node]	
	set<State> discovered;
	
	dist[start] = 0;	// distansen fra start til seg selv er 0;
	
	current = start;	// vi begynner med å evaluere start
	
	int counter = 0;
	while (current != end) {

		if (++counter == 50) {
			counter = 0;
			cout << "dist: " << dist.size() << ", discovered: " << 
					discovered.size() << ", current dist: " << 
					dist[current] << endl;
		}

		// generer naboer
		// legg til nye i dist
		// gå igjennom naboene og oppdater dist
		for (State neighboor : generateNeighboors(current)) {
			if (dist.find(neighboor) != dist.end()) {
				// prøv å oppdatere
				int tentDist = dist[current] + 1;
				if (tentDist < dist[neighboor])
					dist[neighboor] = tentDist;
			} else {
				// garantert ubesøkt, lag	
				if (!equivExcists(neighboor, discovered)) {
					dist.insert(make_pair(neighboor, dist[current]+1));
					discovered.insert(neighboor);
				}
			}
		}
		
		dist.erase(current);

		auto lowestIt = min_element(dist.begin(), dist.end(), 
				[](pair<State, int> a, pair<State, int> b) 
				{ return a.second < b.second; });

		if (lowestIt != dist.end()) {
			current = lowestIt->first;
		} else {
			cout <<	"FANT IKKE MISNTE";
			return -1;
		}
	}

	return dist[current];
}


int main() {
	
	State start(0, Board(4));

	/*
	start.second[0].insert("1M");
	start.second[0].insert("2M");
	start.second[1].insert("1G");
	start.second[2].insert("2G");
	*/

	start.second[0].insert("1M");
	start.second[0].insert("1G");
	start.second[0].insert("6G");
	start.second[0].insert("6M");
	start.second[0].insert("7M");
	start.second[0].insert("7G");

	start.second[1].insert("2G");
	start.second[1].insert("3G");
	start.second[1].insert("4G");
	start.second[1].insert("5G");

	start.second[2].insert("2M");
	start.second[2].insert("3M");
	start.second[2].insert("4M");
	start.second[2].insert("5M");

	State end(3, Board(4));

	/*
	end.second[3].insert("1G");
	end.second[3].insert("1M");
	end.second[3].insert("2G");
	end.second[3].insert("2M");
	*/

	end.second[3].insert("1M");
	end.second[3].insert("1G");
	end.second[3].insert("2G");
	end.second[3].insert("3G");
	end.second[3].insert("4G");
	end.second[3].insert("5G");
	end.second[3].insert("2M");
	end.second[3].insert("3M");
	end.second[3].insert("4M");
	end.second[3].insert("5M");
	end.second[3].insert("6G");
	end.second[3].insert("6M");
	end.second[3].insert("7G");
	end.second[3].insert("7M");

	cout << "Start: " << endl;
	print(start);

	cout << "\nEnd: " << endl;
	print(end);

	cout << shortestRoute(start, end) << endl;	

	return 0;
}
