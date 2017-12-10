#include <iostream>
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
	Register(): reg({0,0,1,0}) { }
	void print() {
		cout << "Reg:" << endl;
		for (size_t i = 0; i < 4; ++i)
			cout << '\t' << char('a' + i) << ":\t" << reg[i] << endl;
		cout << endl;
	}
	int get(char regChar) {
		return reg[regChar - 'a'];
	}
	void cpy(int value, char regChar) {
		reg[regChar - 'a'] = value;
	}
	void cpy(char fromRegChar, char toRegChar) {
		reg[toRegChar - 'a'] = reg[fromRegChar - 'a'];
	}

	void inc(char regChar) {
		++reg[regChar - 'a'];
	}

	void dec(char regChar) {
		--reg[regChar - 'a'];
	}
};

void part1() {
	
	ifstream ifs("input/aoc12_input.txt");
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

	for (size_t i = 0; i < vec.size(); ++i) {
		
		//reg.print();

		//cout << vec[i] << "\n\t";
		
		istringstream iss(vec[i]);	

		string cmd;
		iss >> cmd;

		if (cmd == "cpy") {
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
			
			//cout << "jnz ";
			char c;
			iss >> c;

			if (isdigit(c)) {
				int test = int(c - '0'), mov;
				
				iss >> mov;

				//cout << test << " " << mov;
				
				if (test) {
					i += --mov;
				}
			} else {
				int mov;
				iss >> mov;

				//cout << c << " " << mov;

				if (reg.get(c)) {
					i += --mov;
				}
			}
		}

		//cout << endl;
	}
	 
	cout << "Svaret på part 2: " << reg.get('a'); 
	// utregninga for 1 og 2 er prikk lik, bare med {0,0,1,0} som startverdier
}

int main() {

	part1();

	return 0;
}
