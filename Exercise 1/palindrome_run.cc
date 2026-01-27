#include <iostream>
#include "palindrome.h"
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
		cout << argv[i] << " palindrome?: " << palindrome(argv[i]) << endl;		

	return 0; // Not necessary, but good practice
}

