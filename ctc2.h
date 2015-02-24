#pragma once

#define POSITION_BITS 12
#define LENGTH_BITS 4

#define CTC2_LOOKAHEAD_LENGTH ((int)pow(2.0, (POSITION_BITS)) - 1)
#define CTC2_MAX_LENGTH ((int)pow(2.0, (LENGTH_BITS)) - 1)

// sizeof(struct tag) = 2
struct __attribute__ ((__packed__)) tag {
	unsigned short length: LENGTH_BITS;
	unsigned short position: POSITION_BITS;
};

// You can pass NULL as the destination of any compression / decompression function to get the size of the data after compression / decompression.

size_t CTC2_Compress(unsigned char *destination, unsigned char *source, size_t length);
size_t CTC2_Decompress(unsigned char *destination, unsigned char *source, size_t length);
