#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Keypad {

private:

	int pad[3][3] = {	{1,2,3},
						{4,5,6},
						{7,8,9}};
	int r, c;

public:

	Keypad(): r(1), c(1) { }

	int getValue() {
		return pad[r][c];
	}

	void up() {
		if (r > 0)
			r -= 1;
	}
	void down() {
		if (r < 2)
			r += 1;
	}
	void left() {
		if (c > 0)
			c -= 1;
	}
	void right() {
		if (c < 2)
			c += 1;
	}
};

class Keypad2 {

private:

	char pad[5][5] = {	{'X','X','1','X','X'},
						{'X','2','3','4','X'},
						{'5','6','7','8','9'},
						{'X','A','B','C','X'},
						{'X','X','D','X','X'}};
	int r, c;

public:

	Keypad2(): r(2), c(0) { }

	char getValue() {
		return pad[r][c];
	}

	void up() {
		if (r > 0 && pad[r-1][c] != 'X')
			r -= 1;
	}
	void down() {
		if (r < 4 && pad[r+1][c] != 'X')
			r += 1;
	}
	void left() {
		if (c > 0 && pad[r][c-1] != 'X')
			c -= 1;
	}
	void right() {
		if (c < 4 && pad[r][c+1] != 'X')
			c += 1;
	}
};

void doPart1() {

	// åpne filen
	ifstream ifs("input/aoc2Input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	// klargjør keypad
	Keypad kp;

	// vector av vectorer av kommandoer
	vector<vector<char>> commands;

	// les inn i commands
	string line;
	while (getline(ifs, line)) {

		commands.push_back(vector<char>());
		istringstream iss(line);	

		char c;
		while (iss >> c)
			commands[commands.size()-1].push_back(c);
	}

	// gjør commands
	for (auto cmds : commands) {
		for (char c : cmds) {
			switch (c) {
			case 'U':	kp.up();					break;
			case 'D':	kp.down();					break;
			case 'L':	kp.left();					break;
			case 'R':	kp.right();					break;
			default:	cout << "ERROR" << endl;	break;
			}
		}
		cout << kp.getValue() << ' ';
	}
}

void doPart2() {

	// åpne filen
	ifstream ifs("input/aoc2Input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	// klargjør keypad
	Keypad2 kp;

	// vector av vectorer av kommandoer
	vector<vector<char>> commands;

	// les inn i commands
	string line;
	while (getline(ifs, line)) {

		commands.push_back(vector<char>());
		istringstream iss(line);	

		char c;
		while (iss >> c)
			commands[commands.size()-1].push_back(c);
	}

	// gjør commands
	for (auto cmds : commands) {
		for (char c : cmds) {
			switch (c) {
			case 'U':	kp.up();					break;
			case 'D':	kp.down();					break;
			case 'L':	kp.left();					break;
			case 'R':	kp.right();					break;
			default:	cout << "ERROR" << endl;	break;
			}
		}
		cout << kp.getValue() << ' ';
	}
}

int main() {

	cout << "svar på part 1: ";
	doPart1();
	cout << endl;
	
	cout << "svar på part 2: ";
	doPart2();
	cout << endl;
	
	return 0;
}
