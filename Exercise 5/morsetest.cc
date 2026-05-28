#include "morsecode.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
	MorseCode mc;

	cout << " --- text to code to text--- " << endl;
	string text = "a man, a plan, a canal - panama";
	cout << text << endl;
	string text_encoded = mc.encode(text);
	cout << text_encoded << endl;
	string text_decoded = mc.decode(text_encoded);
	cout << text_decoded << endl;

	cout << endl;

	cout << " --- code to text to code --- " << endl;
	string code = ".... . .-.. .-.. --- .-- --- .-. .-.. -..";
	cout << code << endl;
	string code_decoded = mc.decode(code);
	cout << code_decoded << endl;
	string code_recoded = mc.encode(code_decoded);
	cout << code_recoded << endl;
}
