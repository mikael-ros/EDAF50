#include <string>
#include <iostream>
#ifdef USE_ALGORITHM
#include <algorithm>
#endif

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
 * Returns true if the string s is a palindrome (that is, it
 * reads the same both forwards and backwards).
 */

#ifndef USE_ALGORITHM
bool is_palindrome(const string& s) {
	string::size_type first = 0;
	string::size_type last = s.size() - 1;
	while (last > first  && s[first] == s[last]) {
		first++;
		last--;
	}
	return last <= first;
}
#else
// with the standard algorithm std::equals, it becomes a one-liner:
bool is_palindrome(const string& s) {
    return std::equal(s.begin(), s.end(), s.rbegin());
}
#endif

int main() {
	cout << "Type a word: ";
	string word;
	while (cin >> word) {
		cout << word << " is ";
		if (!is_palindrome(word)) {
			cout << "not ";
		}
		cout << "a palindrome" << endl;
		cout << "Type another word: ";
	}
}
