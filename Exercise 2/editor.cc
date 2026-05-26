#include "editor.h"

#include <string>

using std::string;

// right_par = [")","]","}"]
// left_par = ["(","[","{"]

// procedure find_left_par(p)
// 	if (p < length(text) and text[p] in right_par)  // If position is valid and is a right parenthesis
// 		count_right_par = 1                         // Number of right parenthesis encountered during travel

// 		for (i = p - 1; i > 0; i--)                     // Travel left-ward
// 			if (text[i] in right_par)               // If another right parenthesis
// 				count_right_par++                   // Count up, so we ignore corresponding parenthesis
// 			else if (text[i] in left_par)           // If left parenthesis
// 				count_right_par--                   // Decrement right parenthesis count (we have closed one)
// 				if (count_right_par == 0)           // If count has become 0, this is the corresponding left parenthesis
// 					return i                        // Return position
//	return string::npos                         	// Return invalid position marker
// end procedure

string::size_type Editor::find_left_par(string::size_type pos) const {
	string right_par = "])}";
	string left_par = "[({";

	if (pos < text.length() && right_par.find(text[pos]) != string::npos) {
		int count_right_par = 1;

		for (int i = pos - 1; i > 0; i--) {
			if (right_par.find(text[i]) != string::npos) {
				count_right_par++;
			} else if (left_par.find(text[i]) != string::npos) {
				count_right_par--;
				if (count_right_par == 0) {
					return i;
				}
			}
		}
	}
	return string::npos;
}
