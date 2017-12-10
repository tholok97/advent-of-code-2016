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
	Register(): reg({12,0,0,0}) { }		// part 1 samme men med 7 ikke 12
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

bool validcpy(string s) {
	istringstream iss(s);
	string rs;
	iss >> rs >> rs >> rs;
	return !isnum(rs);
}

bool validincdec(string s) {
	istringstream iss(s);
	string rs;
	iss >> rs >> rs;
	return !isnum(rs);
}

void part1() {
	
	ifstream ifs("input/aoc23_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	Register reg;
	vector<string> vec;

	string line;
	while (getline(ifs, line)) {
		vec.push_back(line);
	}

	set<int> broken;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (broken.find(i) != broken.end()) {
			cout << "FOUND BROKEN: " << vec[i] << endl;
			continue;
		}

		//reg.print();

		//cout << ">> " << vec[i] << '\n';
		
		istringstream iss(vec[i]);	

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

			/*
			//cout << "cpy ";
			char c;
			iss >> c;

			if (isdigit(c)) {

				int value = int(c - '0');
				
				while (iss >> c && isdigit(c)) {
					value *= 10;
					value += int(c - '0');
				}

				//cout << value << " " << c;
				
				reg.cpy(value, c); // from = to.. :p
			} else {
				char from = c;
				iss >> c;

				//cout << from << " " << c;
				reg.cpy(from, c);
			}
			*/
		} else if (cmd == "inc") {
			char c;
			iss >> c;
			//cout << "inc " << c;
			reg.inc(c);
		} else if (cmd == "dec") {
			char c;
			iss >> c;
			//cout << "dec " << c;
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


		} else if (cmd == "tgl") {

			int tglPos;

			iss >> cmd;
			if (isnum(cmd)) {
				tglPos = stoi(cmd) + i;	
			} else {
				tglPos = reg.get(cmd[0]) + i;
			}

			cout << "Tgling "  << tglPos << " (is " << vec.size() << " long). ";
			if (tglPos >= 0 && tglPos < vec.size()) {
				// endre vec[tglPos]
				string &tglCmd = vec[tglPos];
				cout << tglCmd << " -> ";
				if (tglCmd.substr(0,3) == "inc") {
					tglCmd = "dec" + tglCmd.substr(3);
				} else if (tglCmd.substr(0,3) == "dec") {
					tglCmd = "inc" + tglCmd.substr(3);
				} else if (tglCmd.substr(0,3) == "tgl") {
					tglCmd = "inc" + tglCmd.substr(3);
					if (!validincdec(tglCmd))
						broken.insert(tglPos);
				} else if (tglCmd.substr(0,3) == "jnz") {
					tglCmd = "cpy" + tglCmd.substr(3);
					if (!validcpy(tglCmd))
						broken.insert(tglPos);//Invalid cmd
				} else {
					tglCmd = "jnz" + tglCmd.substr(3);
				}
				cout << tglCmd;
			}
			cout << '\n';
		}

		//cout << endl;
		//reg.print();
	}
	 
	cout << "Svaret på part 2: " << reg.get('a') << endl;
}

int main() {

	part1();	// part 2 samme som part 1 men med 7 ikke 12

	return 0;
}
