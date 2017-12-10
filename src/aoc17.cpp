#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <queue>
#include "md5.h"

using namespace std;

typedef pair<int, int> Pos;

bool representsOpen(char c) {
	if (c >= 'b' && c <= 'f')
		return true;
	return false;
}

struct Node;
bool operator<(const Node &lhs, const Node &rhs);

struct Node {
	
	friend bool operator<(const Node &lhs, const Node &rhs);

	Pos position;
	string path;
	int distance;
	Node *parent;
	vector<char> openDirs;

	Node() = default;
	Node(Pos position, string path, Node *parent): position(position), path(path), 
			distance(path.size()), parent(parent) {
		string hash(md5(path));

		if (representsOpen(hash[0]))
			openDirs.push_back('U');
			
		if (representsOpen(hash[1]))
			openDirs.push_back('D');

		if (representsOpen(hash[2]))
			openDirs.push_back('L');

		if (representsOpen(hash[3]))
			openDirs.push_back('R');
	}

	void print() {
		cout << "POS: (" << position.first << ", " << position.second << 
				"), DIST: " << distance << ", PATH: " << path << ", DIRS: ";
		for (char dir : openDirs)
			cout << dir << ", ";
		cout << endl;
	}

	
};

bool operator<(const Node &lhs, const Node &rhs) {
	return lhs.distance < rhs.distance;
}

bool withinBounds(Pos position) {
	return (position.first >= 0 && position.first <= 3 && 
			position.second >= 0 && position.second <= 3);
}

void search(string initial, Pos position) {
	
	priority_queue<Node> pq;
	string minPath;
	pq.push(Node({0,0}, initial, nullptr));

	Node current;
	while (!pq.empty()) {
	
		current = pq.top();
		pq.pop();

		current.print();

		if (current.position == position) {
			string path(current.path.substr(initial.length(), 
					current.path.length() - initial.length()+1));
			if (minPath.empty() || path.size() < minPath.size())
				minPath = path;
			continue;
		}

		if (!minPath.empty() && current.distance > minPath.length() + initial.length())
			continue;

		for (char dir : current.openDirs) {
			//cout << "\tdir: " << dir;	
			Pos position;
			switch(dir) {
			case 'U':
				position.first = current.position.first-1;
				position.second = current.position.second;
				break;
			case 'D':
				position.first = current.position.first+1;
				position.second = current.position.second;
				break;
			case 'L':
				position.first = current.position.first;
				position.second = current.position.second-1;
				break;
			case 'R':
				position.first = current.position.first;
				position.second = current.position.second+1;
				break;
			default:
				cout << "DISASTER";
			}

			if (withinBounds(position)) {
				//cout << " -> added";
				pq.push(Node(position, current.path + dir, &current));
			}
			//cout << endl;
		}
	}

	cout << "minPath: " << minPath << endl;
}

void longest(string initial, Pos position) {
	
	priority_queue<Node> pq;
	string maxPath;
	pq.push(Node({0,0}, initial, nullptr));

	Node current;
	while (!pq.empty()) {
	
		current = pq.top();
		pq.pop();

		//current.print();		fjern for ekstra hackefaktor

		if (current.position == position) {
			string path(current.path.substr(initial.length(), 
					current.path.length() - initial.length()+1));
			if (path.size() > maxPath.size())
				maxPath = path;
			continue;
		}

		for (char dir : current.openDirs) {
			//cout << "\tdir: " << dir;	
			Pos position;
			switch(dir) {
			case 'U':
				position.first = current.position.first-1;
				position.second = current.position.second;
				break;
			case 'D':
				position.first = current.position.first+1;
				position.second = current.position.second;
				break;
			case 'L':
				position.first = current.position.first;
				position.second = current.position.second-1;
				break;
			case 'R':
				position.first = current.position.first;
				position.second = current.position.second+1;
				break;
			default:
				cout << "DISASTER";
			}

			if (withinBounds(position)) {
				//cout << " -> added";
				pq.push(Node(position, current.path + dir, &current));
			}
			//cout << endl;
		}
	}

	cout << "Longest path: " << maxPath.size() << endl;
}

void part1() {

	string initial = "dmypynyp";

	cout << "Svaret på part 1: ";
	search(initial, {3,3});

}

void part2() {
	
	string initial = "dmypynyp";
	
	cout << "Svaret på part 2: ";
	longest(initial, {3,3});		// uten cout fordi d blir veldig mye
}

int main() {

	part1();
	part2();

	return 0;
}
