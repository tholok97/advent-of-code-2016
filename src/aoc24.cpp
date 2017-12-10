#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <utility>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Node;
struct Edge;

struct Node {
	char name;
	pair<int, int> pos;
	vector<Edge> neighboors;
};

struct Edge {
	Node* node;
	int weight;
};

void printNodes(const vector<Node> &nodes) {

	for (const Node &n : nodes) {
		cout << n.name << ": (" << n.pos.first << ", " << n.pos.second << ")\n";
		for (Edge e : n.neighboors) {
			cout << '\t' << e.node->name << ": (" << e.node->pos.first << 
					", " << e.node->pos.second << ") --> " << e.weight << '\n';
		}
	}
}

void printNodes(vector<Node*> &nodes) {

	for (Node* n : nodes) {
		cout << n->name << ": (" << n->pos.first << ", " << 
				n->pos.second << ")\n";
		for (Edge e : n->neighboors) {
			cout << '\t' << e.node->name << ": (" << e.node->pos.first << 
					", " << e.node->pos.second << ") --> " << e.weight << '\n';
		}
	}
}

bool areNeighboors(Node &a, Node &b) {
	
	int x_diff = a.pos.first - b.pos.first;
	int y_diff = a.pos.second - b.pos.second;

	if (x_diff < 0)
		x_diff *= -1;

	if (y_diff < 0)
		y_diff *= -1;
	
	return (x_diff + y_diff < 2) ? true : false;

	return true;
}

vector<Node> nodesFromFile(string path) {

	vector<Node> nodes;

	ifstream ifs(path);
	if (!ifs) {
		cout << "ERROR" << endl;
		return nodes;
	}

	int name = 1;
	string line;
	int i = 0;	
	while (getline(ifs, line)) {
		for (size_t j = 0; j < line.length(); ++j) {
			if (line[j] != '#')
				nodes.push_back({line[j], {j, i}});
		}
		++i;
	}

	for (size_t i = 0; i < nodes.size(); ++i) {
		for (size_t j = i+1; j < nodes.size(); ++j) {	
			if (areNeighboors(nodes[i], nodes[j])) {
				nodes[i].neighboors.push_back({&nodes[j], 1});
				nodes[j].neighboors.push_back({&nodes[i], 1});
			}
		}
	}
						
	return nodes;
}

bool areEqual(const Node &a, const Node &b) {
	return a.pos == b.pos;
}

int search(Node &start, Node &end, vector<Node> &nodes) {

	queue<Node*> q;
	map<Node*, int> dist;

	q.push(&start);
	dist.insert(make_pair(&start, 0));

	Node* current = nullptr;
	while (!q.empty()) {
		current = q.front();
		q.pop();

		if (areEqual(*current, end))
			break;

		for (Edge &n : current->neighboors) {
			if (dist.find(n.node) == dist.end()) {
				dist.insert(make_pair(n.node, dist.at(current)+1));
				q.push(n.node);
			}
		}
	}

	return dist.at(current);
}

vector<Node*> condense(vector<Node> &nodes) {

	vector<Node*> interesting;
	map<Node*, vector<Edge>> newNeighboors;

	for (Node &n : nodes) {
		if (n.name != '.') {
			interesting.push_back(&n);
		}
	}

	for (size_t i = 0; i < interesting.size(); ++i) {
		for (size_t j = i+1; j < interesting.size(); ++j) {
			int shortestRoute = search(*interesting[i], *interesting[j], nodes);

			newNeighboors[interesting[i]].push_back({interesting[j], 
					shortestRoute});
			newNeighboors[interesting[j]].push_back({interesting[i], 
					shortestRoute});
		}
	}

	for (Node* n : interesting)
		n->neighboors = newNeighboors.at(n);
	
	return interesting;
}

int rec(Node* n, vector<Node*> toLookFor, int weight) {

	toLookFor.erase(find(toLookFor.begin(), toLookFor.end(), n));

	set<int> rets;

	//cout << string(4 - toLookFor.size(), ' ') << "Looking at: " << 
			//n->name << "... \n";

	if (toLookFor.size() == 0) {
		//cout << string(4 - toLookFor.size(), ' ') << "END: " << weight << '\n';
		return weight;
	}
	
	//cout << string(4 - toLookFor.size(), ' ') << "Size: " << 
			//toLookFor.size() << '\n';

	for (Edge e : n->neighboors) {
		if (find(toLookFor.begin(), toLookFor.end(), e.node) != 
				toLookFor.end()) {
			int r = rec(e.node, toLookFor, weight+e.weight);
			rets.insert(r);
			//cout << string(4 - toLookFor.size(), ' ') << r << '\n';
		}
	}
	//cout << endl;

	return *(rets.begin());
}

int shortestThroughAll(Node* from, vector<Node*> nodes) {
	
	return rec(from, nodes, 0);
}


int rec2(Node* n, vector<Node*> toLookFor, int weight) {

	toLookFor.erase(find(toLookFor.begin(), toLookFor.end(), n));

	set<int> rets;

	//cout << string(4 - toLookFor.size(), ' ') << "Looking at: " << 
			//n->name << "... \n";

	if (toLookFor.size() == 0) {
	
		int toZero;
		for (Edge e : n-> neighboors)
			if (e.node->name == '0')
				toZero = e.weight;


		weight += toZero;
		//cout << string(4 - toLookFor.size(), ' ') << "END: " << weight << '\n';
		return weight;
	}
	
	//cout << string(4 - toLookFor.size(), ' ') << "Size: " << 
			//toLookFor.size() << '\n';

	for (Edge e : n->neighboors) {
		if (find(toLookFor.begin(), toLookFor.end(), e.node) != 
				toLookFor.end()) {
			int r = rec2(e.node, toLookFor, weight+e.weight);
			rets.insert(r);
			//cout << string(4 - toLookFor.size(), ' ') << r << '\n';
		}
	}
	//cout << endl;

	return *(rets.begin());
}

int sTAAndReturn(Node* from, vector<Node*> nodes) {

	return rec2(from, nodes, 0);
}

int main() {

	vector<Node> nodes = nodesFromFile("input/aoc24_input.txt");

	vector<Node*> interesting = condense(nodes); // NB! peker til nodes

	Node* from = nullptr;

	for (Node* n : interesting)
		if (n->name == '0')
			from = n;


	//printNodes(interesting);
	
	cout << "Answer to part 1: " << 
			shortestThroughAll(from, interesting) << '\n';
	cout << "Answer to part 2: " << 
			sTAAndReturn(from, interesting) << '\n';
	
	return 0;
}
