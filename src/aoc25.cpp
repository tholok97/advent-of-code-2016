#include <iostream>
#include <set>
#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Register {
private:
	array<int, 4> reg;
public:
	Register(int a, int b, int c, int d): reg({a,b,c,d}) { }		// part 1 samme men med 7 ikke 12
	void print() {
		for (size_t i = 0; i < 4; ++i)
			cout << reg[i] << '\t';
		cout << endl;
	}
	int get(char regChar) {
		return reg[regChar - 'a'];
	}
	void cpy(int value, char regChar) {
		reg[regChar - 'a'] = value;
	}
	void cpychar(char fromRegChar, char toRegChar) {
		reg[toRegChar - 'a'] = reg[fromRegChar - 'a'];
	}

	void inc(char regChar) {
		++reg[regChar - 'a'];
	}

	void dec(char regChar) {
		--reg[regChar - 'a'];
	}
};

bool isnum(string s) {
	for (char c : s)
		if (!isdigit(c) && c != '-')
			return false;
	return true;
}


int main() {
	
	ifstream ifs("input/aoc25_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return -1;
	}

	vector<string> instr;

	string line;
	while (getline(ifs, line))
		instr.push_back(line);
	
	int initial = 1;
	while (true) {
		
			
		Register reg(++initial,0,0,0);
		int stored = 1;
		int numStored = 0;
		bool success = false;

		cout << "Prøver igjen (" << initial << ")\n";

		for (size_t i = 0; i < instr.size(); ++i) {

			istringstream iss(instr[i]);

			string cmd;
			iss >> cmd;

			if (cmd == "cpy") {
				int value;
				iss >> cmd;

				if (isnum(cmd)) {
					value = stoi(cmd);
				} else {
					value = reg.get(cmd[0]);
				}

				char c;
				iss >> c;

				reg.cpy(value, c);
			} else if (cmd == "inc") {
				char c;
				iss >> c;
				reg.inc(c);
			} else if (cmd == "dec") {
				char c;
				iss >> c;
				reg.dec(c);
			} else if (cmd == "jnz") {

				int mov;
				bool test;

				iss >> cmd;
				if (isnum(cmd)) {
					test = stoi(cmd);
				} else {
					test = reg.get(cmd[0]);
				}

				iss >> cmd;
				if (isnum(cmd)) {
					mov = stoi(cmd);
				} else {
					mov = reg.get(cmd[0]);
				}

				if (test) {
					i += --mov;
				}
			} else if (cmd == "out") {
				
				int signal;
				iss >> cmd;

				if (isnum(cmd)) {
					signal = stoi(cmd);
				} else {
					signal = reg.get(cmd[0]);
				}

				if (signal != 0 && signal != 1)
					break;

				if (signal == stored)
					break;

				++numStored;
				
				if (numStored > 100) {
					success = true;
					break;
				}

				stored = signal;	

				cout << "\tout: " << signal << endl;
			} else {
				cout << "CMD ERROR" << endl;
			}
		}
		if (success)
			break;
	}

	cout << "Answer: " << initial << endl;

	return 0;
}
