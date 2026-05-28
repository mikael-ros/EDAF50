#include <bits/stdc++.h>
#include "morsecode.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::toupper;
using std::istringstream;
using namespace std;

MorseCode::MorseCode() {
	ifstream Definitions("morse.def");

	string definition;
	while (getline (Definitions, definition)) {
		definitions.push_back(definition.substr(2,definition.length()-1));
	}
}

string MorseCode::encode(const string& text) const {
	string encoded_text;

	for (char letter : text) {
		int index = toupper(letter) - 'A';

		if (index <= 26 && index >= 0) // if valid
			encoded_text += definitions[index] + ' ';
	}

	return encoded_text;
}

string MorseCode::decode(const string& code) const {
	string decoded_text;
	istringstream code_stream(code);

	string current_block;
	while (getline(code_stream, current_block, ' ')) // Continue until end, split by space
	{
		auto index = find(definitions.begin(), definitions.end(), current_block);

		if (index != definitions.end()) {
		
			char d = index - definitions.begin() + 'A'; // Retrieve index and cast as char

			decoded_text += d;
		}
	}

	return decoded_text;
}
