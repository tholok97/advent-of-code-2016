#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

size_t posOf(char c, string &s) {
	for (size_t i = 0; i < s.length(); ++i)
		if (s[i] == c)
			return i;
	return -1;
}

void swapPos(string &s, size_t a, size_t b) {

	char save = s[a];
	s[a] = s[b];
	s[b] = save;
}

void swapLet(string &s, char a, char b) {

	size_t posA = posOf(a, s);	
	size_t posB = posOf(b, s);	

	char save = s[posA];
	s[posA] = s[posB];
	s[posB] = save;
}

void rotateLeft(string &s, int n) {

	n %= s.length();

	for (int i = 0; i < n; ++i) {
		char save = s[0];
		for (size_t j = 0; j < s.length()-1; ++j) {
			s[j] = s[j+1];
		}
		s[s.length()-1] = save;
	}
}

void rotateRight(string &s, int n) {
	
	n %= s.length();

	for (int i = 0; i < n; ++i) {
		char save = s[s.length()-1];
		for (size_t j = s.length()-1; j > 0; --j) {
			s[j] = s[j-1];
		}
		s[0] = save;
	}
}

void rotateBasedOn(string &s, char c) {

	size_t pos = posOf(c, s);	
	if (pos >= 4)
		++pos;
	rotateRight(s, 1+pos);
}

void rrotateBasedOn(string &s, char c) {
	
	size_t nowPos = posOf(c, s);
	if (nowPos <= 4) {						// TODO når?
		nowPos += s.length();		// funker når c er stor nok, og ikke ellers
		nowPos %= s.length()*2;
	}

	size_t pos = nowPos - 1;

	pos /= 2;
	
	if (pos / 2 >= 5)
		--pos;

	cout << "nowpos: " << nowPos << ", pos: " << pos << endl;
	size_t toMove = nowPos - pos;		// TODO >= 4  ->  ++pos ?

	rotateLeft(s, toMove);
}

void reversePos(string &s, size_t a, size_t b) {
	
	reverse(s.begin()+a, s.begin()+b+1);
}

void movePos(string &s, size_t a, size_t b) {

	char save = s[a];
	s.erase(a, 1);
	s.insert(b, string(1, save));
}

void part1() {

	string p{"abcdefgh"};

	/*
	swapPos(p, 4, 0);
	swapLet(p, 'd', 'b');
	reversePos(p, 0, 4);
	rotateLeft(p, 1);
	movePos(p, 1, 4);
	movePos(p, 3, 0);
	rotateBasedOn(p, 'b');
	rotateBasedOn(p, 'd');

	cout << p << endl;
	*/


	ifstream ifs{"input/input/aoc21_input.txt"};
	if (!ifs) {
		cout << "ERROR" << endl;
		return;
	}


	string line;
	while (getline(ifs, line)) {
		istringstream iss(line);
		
		string cmd;
		iss >> cmd;
		if (cmd == "swap") {
			iss >> cmd;
			if (cmd == "position") {
				size_t a, b;
				iss >> a;
				iss >> cmd >> cmd;
				iss >> b;
				
				swapPos(p, a, b);
			} else {
				char a, b;
				iss >> a;
				iss >> cmd >> cmd;
				iss >> b;

				swapLet(p, a, b);
			}
		} else if (cmd == "rotate") {
			iss >> cmd;
			if (cmd == "left") {
				int n;
				iss >> n;

				rotateLeft(p, n);
			} else if (cmd == "right") {
				int n;
				iss >> n;

				rotateRight(p, n);
			} else {
				iss >> cmd >> cmd >> cmd >> cmd;
				char c;
				iss >> c;

				rotateBasedOn(p, c);
			}
		} else if (cmd == "reverse") {
			iss >> cmd;
			size_t a, b;
			iss >> a;
			iss >> cmd;
			iss >> b;

			reversePos(p, a, b);
		} else if (cmd == "move") {
			iss >> cmd;
			size_t a, b;
			iss >> a;
			iss >> cmd >> cmd;
			iss >> b;

			movePos(p, a, b);
		}
	}

	cout << "Answer to part 1: " << p << endl;
}

void part2() {
	

	/*
		PGA string av lengde 8 er det ikke egt nødvendig å finne ut hvordan 
		prosedyren fungerer baklengs. En enklere løsning ville vært å bare 
		brute-force alle mulige passord av lengde 8 til vi fant en som ble til
		det scramblede passordet................ :p
	*/

	string p{"fbgdceah"};

	ifstream ifs{"input/aoc21_input.txt"};
	if (!ifs) {
		cout << "ERROR" << endl;
		return;
	}

	vector<string> lines;

	string line;
	while (getline(ifs, line))
		lines.push_back(line);	

	reverse(lines.begin(), lines.end());

	map<pair<string, char>, string> revOfThing;

	string thing = p;
	sort(thing.begin(), thing.end());
	do {
		for (char c : p) {
			string rev = thing;
			rotateBasedOn(rev, c);		// :p
			revOfThing.insert(make_pair(make_pair(rev, c), thing));
		}
	} while (next_permutation(thing.begin(), thing.end()));



	for (string line : lines) {
		istringstream iss(line);
		
		string cmd;
		iss >> cmd;
		if (cmd == "swap") {
			iss >> cmd;
			if (cmd == "position") {
				size_t a, b;
				iss >> a;
				iss >> cmd >> cmd;
				iss >> b;
				
				swapPos(p, a, b);
			} else {
				char a, b;
				iss >> a;
				iss >> cmd >> cmd;
				iss >> b;

				swapLet(p, a, b);
			}
		} else if (cmd == "rotate") {
			iss >> cmd;
			if (cmd == "left") {
				int n;
				iss >> n;

				rotateRight(p, n);
			} else if (cmd == "right") {
				int n;
				iss >> n;

				rotateLeft(p, n);
			} else {
				iss >> cmd >> cmd >> cmd >> cmd;
				char c;
				iss >> c;

				p = revOfThing.at(make_pair(p, c));
			}
		} else if (cmd == "reverse") {
			iss >> cmd;
			size_t a, b;
			iss >> a;
			iss >> cmd;
			iss >> b;

			reversePos(p, a, b);
		} else if (cmd == "move") {
			iss >> cmd;
			size_t a, b;
			iss >> a;
			iss >> cmd >> cmd;
			iss >> b;

			movePos(p, b, a);
		}
	}

	cout << "Answer to part 2: " << p << endl;
}

int main() {

	part1();
	part2();



	return 0;
}
