   #include <iostream>
   #include <vector>
   #include <utility>
   #include <set>
   #include "md5.h"
   
   using namespace std;
   
   // search for triplet in string s and return the char. if no triplet is found:
   // return '\0'
    char triplet(string s) {
    	for (size_t i = 0; i < s.size()-2; ++i)
    		if (s[i] == s[i+1] && s[i] == s[i+2])
    			return s[i];
    	return '\0';
    }

    // search for five char c's next to each other in string s. true if success
    bool fiveOf(char c, string s) {
    	for (size_t i = 0; i < s.size()-4; ++i)
    		if (s.substr(i, 5) == string(5, c))
    			return true;
    	return false;
    }

    // hash the string s int n times and return the hash
    string doHash(string s, int n) {
    	for (int i = 0; i < n; ++i)
    		s = md5(s);
    	
    	return s;
    }

    void part2() {
    
    	string salt = "yjdafjpo";

    	// vector of the potential keys found. a pair of int and char. 
    	//  int: what index the key was found at and
    	//  char: the char of the key
    	vector<pair<int, char>> check;
    
    	int numKey = -1;			// -1 until the 64th key is found
    	
    	int i = 0;		// i: is incremented every run through the loop
    	int keys = 0;	// keys: number of keys found
    	while (numKey == -1) {		// while the 64th key is not found
    		
    		string hash = doHash(salt + to_string(i), 2017);	// calculate hash
    		char c = triplet(hash);		// look for triplet
    		if (c != '\0') {			// if triplet found
    			check.push_back(make_pair(i, c));	// add potential key
    			//cout << "Found key at " << i << endl;
    		}
    
    		// set of iterators to elements we want to erase from the vector
    		set<decltype(check.begin())> toErase;			
    
    		// for every potential key in check
    		for (size_t j = 0; j < check.size(); ++j) {
    
    			// p is the the j'th element in check
    			auto p = check[j];
    
    			// if we are within range of where the matching key should be
    			if (p.first < i && i < p.first + 1000) {
    
    				// look for five of the potential key's char
    				if (fiveOf(p.second, hash)) {
    					
    					// found it! add key to set of potential keys to be erased
    					toErase.insert(check.begin() + i);
    					++keys;	// increment keys
    					cout << "Confirmed key nr. " << keys << " (" << 
    							p.first << ") at: " << i << endl;
    					if (keys == 64)	// if this is the 64th key:
    						numKey = p.first;	// set numkey to the index where
    					}						//  the key was first found
    				}							//  (This terminates the loop)
    		}

    		for (auto p : toErase)	// erase all found keys from the vector
    			check.erase(p);
    
    		++i;	// increment i
    	}
    
    	cout << "Answer to part 2: " << numKey << endl;	// print answer
    }
    
    int main() {
    
    	part2();
    
    	return 0;
    }
