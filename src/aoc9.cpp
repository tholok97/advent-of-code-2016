#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void part1() {

	fstream ifs("aoc9_input.txt");
	if (!ifs) {
		cout <<	"ERROR";
		return;
	}

	int length = 0;

	char c;
	while (ifs >> c) {
		if (c == '(') {
			int a, b;
			ifs >> a;
			ifs.ignore();
			ifs >> b;
			ifs.ignore(a + 1);

			length += a * b;
		} else {
			++length;
		}
	}

	cout << "Svaret på part 1: " << length << endl;
}

long long declength(ifstream &ifs, int n, int tab) {
	long long length = 0, i = 0;	// long long fordi d blir ENORME tall
	char c;
	while ((i < n || n < 0) && ifs >> c) {
		if (c == '(') {
			int a, b;
			ifs >> a;
			ifs.ignore();
			ifs >> b;
			ifs.ignore();

			cout << string(tab, '\t') << "-> (" << a << ", " << b  << 
					"):" << endl;
			
			length += declength(ifs, a, tab + 1) * b;

			cout << string(tab, '\t') << "SEGMENT LENGTH: " << length << endl;

			// supersketchy måte å finne antall siffer i a og b på :p
			i += 1 + to_string(a).length() + 1 + to_string(b).length() + 1 + a;
		} else if (c != ' ') {
			cout << string(tab, '\t') << "char: " << c << endl;
			++length;
			++i;
		}
	}

	cout << string(tab, '\t') << "<- RETURNING LENGTH: " << length << endl;
	return length;
}

void part2() {

	ifstream ifs("input/aoc9_input.txt");
	if (!ifs) {
		cout <<	"ERROR";
		return;
	}

	long long length = declength(ifs, -1, 0);

	cout << "Svaret på part 2: " << length << endl;
}

int main() {

	part1();
	part2();

	return 0;
}
