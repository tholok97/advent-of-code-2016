#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

void part1() {
	
	// åpne fil
	ifstream ifs("input/aoc4_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	// totalen av id'ene til korrekte rom
	int totId = 0;

	// les inn rommene linje for linje
	string line;
	while (getline(ifs, line)) {
	
		map<char, int> numOfChar;		// bokstav -> antall av bokstav
		istringstream iss(line);
		vector<string> segments;		// segmenter avskilt av - i line

		string segment;
		while (getline(iss, segment, '-'))
			segments.push_back(segment);

		string lastSegment = segments.back();	// pop siste segment inn
		segments.pop_back();					// i lastSegment

		for (string s : segments)
			for (char c : s)
				++numOfChar[c];		// bygg map

		// sorterer sorted:
		vector<pair<char, int>> sorted;
		for (auto p : numOfChar)						// bygger vector fra map
			sorted.push_back({p.first, p.second});

		// alfabetisk
		sort(sorted.begin(), sorted.end(), [](const pair<char, int> &p1, 
				const pair<char, int> &p2) { return p1.first < p2.first; });

		// etter antall (alfabetisk beholdes ved ==)
		stable_sort(sorted.begin(), sorted.end(), [](const pair<char, int> &p1,
				const pair<char, int> &p2) { return p1.second > p2.second; });

		// bygger id og checksum
		string idString;
		string checksum;
		int id;
		
		int i = 0;
		while (lastSegment[i] != '[')			// finner id
			idString += lastSegment[i++];
		
		id = stoi(idString);					
		checksum = lastSegment.substr(++i, 5);		// finner checksum

		// sjekker sorted opp mot checksum, og øker tot
		if (sorted.size() > 4 &&	sorted[0].first == checksum[0] &&
									sorted[1].first == checksum[1] &&	
									sorted[2].first == checksum[2] &&	
									sorted[3].first == checksum[3] &&	
									sorted[4].first == checksum[4]) {
			totId += id;
		}

		/* DEBUG
		cout << id << ", " << checksum << endl;
		*/	

		/* DEBUG
		cout << "Map:\n";
		for (auto p : numOfChar)
			cout << "\t" << p.first << ": " << p.second << "\n";
		cout << endl;
		*/

		/* DEBUG
		cout << "Segments: ";
		for (string s : segments)
			cout << s << ", ";

		cout << "(" << lastSegment << ")" << endl;
		*/
	}


	cout << "Svar på part 1: " << totId << endl;
}

char shift(char c) {
	if (int(c) < 122) {
		return ++c;
	} else {
		return 'a';
	}
}

char shiftN(char c, int n) {
	n %= 26;
	for (int i = 0; i < n; ++i) {
		c = shift(c);	
	}
	return c;
}

void part2() {
	
	// åpne fil
	ifstream ifs("input/aoc4_input.txt");
	if (!ifs) {
		cout << "ERROR";
		return;
	}

	// les inn rommene linje for linje
	string line;
	while (getline(ifs, line)) {
	
		map<char, int> numOfChar;		// bokstav -> antall av bokstav
		istringstream iss(line);
		vector<string> segments;		// segmenter avskilt av - i line

		string segment;
		while (getline(iss, segment, '-'))
			segments.push_back(segment);

		string lastSegment = segments.back();	// pop siste segment inn
		segments.pop_back();					// i lastSegment

		for (string s : segments)
			for (char c : s)
				++numOfChar[c];		// bygg map

		// sorterer sorted:
		vector<pair<char, int>> sorted;
		for (auto p : numOfChar)						// bygger vector fra map
			sorted.push_back({p.first, p.second});

		// alfabetisk
		sort(sorted.begin(), sorted.end(), [](const pair<char, int> &p1, 
				const pair<char, int> &p2) { return p1.first < p2.first; });

		// etter antall (alfabetisk beholdes ved ==)
		stable_sort(sorted.begin(), sorted.end(), [](const pair<char, int> &p1,
				const pair<char, int> &p2) { return p1.second > p2.second; });

		// bygger id og checksum
		string idString;
		string checksum;
		int id;
		
		int i = 0;
		while (lastSegment[i] != '[')			// finner id
			idString += lastSegment[i++];
		
		id = stoi(idString);					
		checksum = lastSegment.substr(++i, 5);		// finner checksum

		// printer dekryptert navn + id hvis rommet er gyldig
		if (sorted.size() > 4 &&	sorted[0].first == checksum[0] &&
									sorted[1].first == checksum[1] &&	
									sorted[2].first == checksum[2] &&	
									sorted[3].first == checksum[3] &&	
									sorted[4].first == checksum[4]) {
			string cleartext;
			for (string s : segments) {
				for (char c : s)					// dekrypter
					cleartext += shiftN(c, id);
				cleartext += ' ';
			}
			
			// fjern mellomrom på slutten
			cleartext = cleartext.substr(0, cleartext.length()-1);
			
			cout << cleartext << " (" << id << ")" << endl;
		}
	}

	cout << "svar på part 2: 501 (fant svaret ved å lete gjennom lista etter "
			"navn som hadde med nord polen å gjøre :)" << endl;
}

int main() {

	part1();
	part2();

	return 0;
}
