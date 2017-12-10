#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

struct Bin;
struct Bot;
class Swarm;

struct Bin {
	vector<int> values;
	void receive(int v) {
		values.push_back(v);
	}
	void print() {
		cout << "\tValues: ";
		for (int v : values)
			cout << v << ' ';
		cout << endl;
	}
};

struct Bot {
	vector<int> values;
	int low_target, high_target;
	bool low_bin, high_bin;
	Swarm *parent;
	
	Bot(int lt, int ht, bool lb, bool hb, Swarm *prnt): low_target(lt), high_target(ht), 
			low_bin(lb), high_bin(hb), parent(prnt) { }

	void receive(int v) {
		values.push_back(v);
	}
	bool full() {
		return values.size() == 2;
	}
	bool empty() {
		return values.empty();
	}
	void give();
	bool has(int a, int b) {
		if (values.size() == 2)
			if ((a == values[0] && b == values[1]) || (a == values[1] && b == values[0]))
				return true;
		return false;
	}
	void print() {
		cout << "\t\tValues: ";
		for (int v : values)
			cout << v << ' ';
		cout << "\n\t\tLow_target:\t" << low_target;
		if (low_bin)
			cout << " (BIN)";
		cout << "\n\t\tHigh_target:\t" << high_target;
		if (high_bin)
			cout << " (BIN)";
		cout << endl;
	}
};

class Swarm {
private:
	map<int, Bot> bots;
	map<int, Bin> bins;

	map<int, Bot> tmp;

public:
	void addBot(int id, int lt, int ht, bool lb, bool hb) {
		bots.insert(make_pair(id, Bot(lt, ht, lb, hb, this)));

		if (lb)
			bins.insert(make_pair(lt, Bin()));

		if (hb)
			bins.insert(make_pair(ht, Bin()));
	}
	void give(int id, int v) {
		bots.at(id).receive(v);		
	}
	void callback(int id, int v, bool bin) {
		if (bin) {
			bins.at(id).receive(v);
		} else {
			tmp.at(id).receive(v);
		}
	}
	void step() {
		tmp = bots;

		for (auto &bot : bots) {
			if (bot.second.full()) {
				bot.second.give();
				tmp.at(bot.first).values.clear();
			}
		}

		bots = tmp;
	}
	int check(int v1, int v2) {
		for (auto bot : bots)
			if (bot.second.has(v1, v2))
				return bot.first;
		return -1;
	}
	bool empty() {
		for (auto bot : bots)
			if (!bot.second.empty())
				return false;
		return true;
	}
	void print() {
		cout << "Bots:" << endl;
		for (auto bot : bots) {
			cout << "\tBot: " << bot.first << endl;
			bot.second.print();
		}
		cout << "Bins:" << endl;
		for (auto &bin : bins) {
			cout << "Bin: " << bin.first << endl;
			bin.second.print();
		}
	}
};

void part1() {
	
	ifstream ifs("input/aoc10_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	Swarm swarm;

	vector<pair<int, int>> valuesToAdd;
	string line;
	while (getline(ifs, line)) {

		istringstream iss(line);
		
		string cmd;
		iss >> cmd;

		if (cmd == "bot") {
			int botNr, low, high;
			bool lb = false, hb = false;

			iss >> botNr;
			iss >> cmd >> cmd >> cmd >> cmd;
			if (cmd == "output")
				lb = true;
			iss >> low;
			iss >> cmd >> cmd >> cmd >> cmd;
			if (cmd == "output")
				hb = true;
			iss >> high;
			
			swarm.addBot(botNr, low, high, lb, hb);
		} else {

			int value, botNr;
			iss >> value;
			iss >> cmd >> cmd >> cmd;
			iss >> botNr;

			valuesToAdd.push_back(make_pair(botNr, value));
		}
	}

	for (auto p : valuesToAdd) {
		swarm.give(p.first, p.second);
	}
	
	// swarm er ferdiglaget!

	int goal = -1;
	int i = 0;
	while (!swarm.empty()) {
		if (goal < 0)
			goal = swarm.check(17,61);
		swarm.step();
		++i;
	}

	swarm.print();

	cout << "kjørte: " << i << "ganger.." << endl;

	cout << "\n\nSVARET PÅ PART 1: " << goal << endl;
	cout << "SARET PÅ PART 2: output 0, 1 og 2 * sammen" << endl;

}


int main() {

	part1();

	return 0;
}

void Bot::give() {
		int lower, higher;
		if (values[0] < values[1]) {
			lower = values[0];
			higher = values[1];
		} else {
			lower = values[1];
			higher = values[0];
		}

		parent->callback(low_target, lower, low_bin);
		parent->callback(high_target, higher, high_bin);

		values.clear();
}
