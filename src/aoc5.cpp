#include <iostream>
#include <climits>
#include "md5.h"

using namespace std;

void part1() {
	
	string door_id = "ugkcyxxp";
	string password;

	int i = 0;
	while (password.length() < 8) {

		string hash = md5(door_id + to_string(i));
		if (hash.substr(0, 5) == "00000") {
			password += hash[5];
			cout << hash[5];
		}
		++i;
	}

	cout << "\nSvaret på part 1: " << password << endl;
}

bool validPosition(char c) {
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
			c == '6' || c == '7') {
		return true;
	} else {
		return false;
	}
}

void part2() {

	string door_id = "ugkcyxxp";
	string password(8, '-');
	int num_discovered = 0;

	cout << "cracker passord... [" << door_id << "]\n\n" << password << endl;

	int i = 0;
	while (num_discovered < 8) {

		if (i == INT_MAX)
			cout << "LIMIT" << endl;

		string hash = md5(door_id + to_string(i));
		if (hash.substr(0, 5) == "00000" && validPosition(hash[5])) {
			
			int pos = hash[5] - '0';
			if (password[pos] == '-') {
				password[pos] = hash[6];
				++num_discovered;
				cout << password << endl;
			}
		}
		++i;
	}

	cout << "\nPassordet er: " << password << endl;
}

int main() {

	//part1();
	part2();

	return 0;
}
