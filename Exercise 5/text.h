#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>

class Text {
public:
	using iterator = std::vector<std::string>::iterator;
	iterator begin() { return lines.begin(); }
    iterator end() { return lines.end(); }
	void addLine(const std::string& line) { lines.push_back(line); }
private:
	std::vector<std::string> lines;
};

#endif
