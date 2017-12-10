#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Screen {
private:
	bool pixels[6][50] = {};
public:
	void rect(int r, int c) {
		for (int i = 0; i < c; ++i) {
			for (int j = 0; j < r; ++j) {
				pixels[i][j] = true;
			}
		}
	}
	void rotr(int r, int n) {
		int tmp[50] = { 0 };

		for (int i = 0; i < 50; ++i) {
			tmp[(i+n)%50] = pixels[r][i];
		}

		for (int i = 0; i < 50; ++i) {
			pixels[r][i] = tmp[i];
		}
	}
	void rotc(int c, int n) {	
		int tmp[6] = { 0 };

		for (int i = 0; i < 6; ++i) {
			tmp[(i+n)%6] = pixels[i][c];
		}

		for (int i = 0; i < 6; ++i) {
			pixels[i][c] = tmp[i];
		}
	}
	int num_on() {
		int num = 0;
		for (int i = 0; i < 6; ++i)
			for (int j = 0; j < 50; ++j)
				if (pixels[i][j])
					++num;

		return num;
	}
	void print() {
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 50; ++j) {
				if (j % 5 == 0)
					cout << ' ';
				cout << char(pixels[i][j] ? 219 : 176);
			}
			cout << endl;
		}
	}
};

void part1() {
	
}

int main() {

	ifstream ifs("input/aoc8_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return 0;
	}

	Screen scr;

	string line;
	while (getline(ifs, line)) {
		scr.print();				// fjern for SPEED AND POWER
		cout << endl;
		istringstream iss(line);

		string operation;
		iss >> operation;

		if (operation == "rect") {
			int a, b;
			iss >> a;
			iss.ignore();
			iss >> b;

			scr.rect(a, b);
		} else {
			iss >> operation;
			if (operation == "row") {
				int a, b;
				iss.ignore(3);
				iss >> a;
				iss.ignore(4);
				iss >> b;

				scr.rotr(a, b);
			} else if (operation == "column") {
				int a, b;
				iss.ignore(3);
				iss >> a;
				iss.ignore(4);
				iss >> b;

				scr.rotc(a, b);
			}
		}
	}

	cout << "Svaret på part 1: " << scr.num_on() << endl;
	cout << "Svaret på part 2: " << endl;
	scr.print();

	return 0;
}
