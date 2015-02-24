#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "ctc2.h"

static unsigned char cmp(unsigned char *d1, unsigned char *d2, unsigned char maxLength) {
	unsigned char i;
	
	for(i = 0; i < maxLength; i++) {
		if(d1[i] != d2[i]) return i;
	}
	
	return maxLength;
}

static void cpy(unsigned char *destination, unsigned char *source, size_t sourceLength, size_t sourceModularLength) {
	unsigned int i;
	for(i = 0; i < sourceModularLength; i++) {
		destination[i] = source[i % sourceModularLength];
	}
}

/*
	unsigned char d[12] = "11abcdefabc";
	struct tag tag = getLongestMatch(d + 8, 3, d);
	printf("%d %d\n", tag.position, tag.length);
	// 6 3
*/

static struct tag getLongestMatch(unsigned char *data, unsigned char length, unsigned char *start) {
	struct tag best = { 0, 0 };
	
	unsigned char *i;
	for(i = start; i < data; i++) {
		unsigned char similarBytes = cmp(data, i, length);
		
		if(similarBytes > best.length) {
			best.position = data - i;
			best.length = similarBytes;
		}
	}
	
	return best;
}

size_t CTC2_Compress(unsigned char *destination, unsigned char *source, size_t length) {
	unsigned char write = destination != NULL;
	
	unsigned int i, j = 0;
	for(i = 0; i < length; i++) {
		if(write) destination[j] = source[i];
		j++;
		
		i++;
		if(!(i < length)) break;
		
		size_t maxLength = length - i;
		if(maxLength > CTC2_MAX_LENGTH) maxLength = CTC2_MAX_LENGTH;
		
		unsigned char *start = source + i - CTC2_LOOKAHEAD_LENGTH;
		if(start < source) start = source;
		
		struct tag match = getLongestMatch(source + i, maxLength, start);
		
		if(match.position) {
			if(write) memcpy(destination + j, &match, sizeof(struct tag));
			j += sizeof(struct tag);
			
			i += match.length - 1;
		}
		else {
			if(write) destination[j] = 0;
			j++;
			i--;
		}
	}
	
	return j;
}

size_t CTC2_Decompress(unsigned char *destination, unsigned char *source, size_t length) {
	unsigned char write = destination != NULL;
	
	unsigned int i, j = 0;
	for(i = 0; i < length; i++) {
		if(write) destination[j] = source[i];
		j++;
		
		i++;
		if(!(i < length)) break;
		
		if(source[i]) {
			struct tag tag;
			memcpy(&tag, source + i, sizeof(struct tag));
			i += sizeof(struct tag) - 1;
			
			if(write) cpy(destination + j, destination + j - tag.position, j, tag.length);
			j += tag.length;
		}
	}
	
	return j;
}
