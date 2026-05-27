#include "crypto.h"

#include <string>
#include <random>

using std::string;

string Crypto::encrypt(const string& text, unsigned int key) {
	srand(key); // set the seed
	
	string enc_text = "";
	for (char c : text)
	{
		int random_num = rand() % 256; // Generate a random number between 0 and 256

		char enc_c = c + random_num;
		enc_c %= 256;
		enc_text += enc_c;
	}
	return enc_text;
}

string Crypto::decrypt(const string& crypt, unsigned int key) {
	srand(key); // set the seed
	
	string decrypt_text = "";

	for (char c : crypt)
	{
		int random_num = rand() % 256;

		char dec_c = c - random_num;
		dec_c %= 256;
		decrypt_text += dec_c;
	}
	return decrypt_text;
}
