/*
 * MorseCode: translates letters a-z to/from Morse code. The code
 * definitions are in the file morse.def.
 */
#ifndef MORSECODE_H
#define MORSECODE_H

#include <string>
#include <vector>


using namespace std;

class MorseCode {
public:
	MorseCode();
	string encode(const string& text) const;
	string decode(const string& code) const;
private:
	vector<string> definitions;
};

#endif
