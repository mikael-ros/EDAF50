#include "palindrome.h"
#include <string>
#include <algorithm>
using std::string;
using std::reverse;

bool palindrome(string text)
{
	string reversed = text;
	reverse(reversed.begin(), reversed.end());
	return reversed == text;
}
