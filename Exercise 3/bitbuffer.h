#ifndef BIT_BUFFER_H
#define BIT_BUFFER_H

#include <iostream>

class BitBuffer {
public:
	BitBuffer(std::ostream& out);
	void put(bool b);
private:
	std::ostream& os;    	// The output stream
	unsigned char byte;  	// The buffer of 8 bits
	unsigned int num_bits;	// The number of bits in the buffer
};

#endif
