#include "bitbuffer.h"

#include <iostream>

BitBuffer::BitBuffer(std::ostream& out) : os(out), num_bits(0) {}

void BitBuffer::put(bool b) {
    byte = (byte << 1) | b; // Shift byte leftward by 1, add b as least significant

    if (++num_bits == 8)    // If we have reached the size of a byte
    {
        os.put(byte);       // Put in stream
        num_bits = 0;       // Reset
    }
}
