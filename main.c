/**
 * This program implements a simple set data structure where each value can be
 * stored and interpreted as either 1 or 0. With this data structure a number 0
 * through n-1 can be represented as the presence of a single bit within the bit
 * map.
 *
 * Storing 1,000,000 integers in an array would require 4,000,000 bytes,
 * assuming 32-bit integers.
 *
 * Using the bit map data structure 1,000,000 integers can be stored in
 * 1,000,000 / 8 = 125,000 bytes.
 *
 * BITSPERBYTE is the number of bits in a uint8_t type since that is how the bit
 * map array is implemented, this could be changed to 32 if using uint32_t for
 * example.
 *
 * BITSSHIFT is the number of bits to right shift a number to divide by the
 * number of BITSPER type. In this case a right shift of 3 is the equivilent of
 * dividing by 8.
 *
 * SETMASK is used to perform a modulus operation. The value of SETMASK is
 * BITSPER-1 which sets all of the bits in the size of the type to 1.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BITSPERBYTE 8
#define BITSSHIFT 3
#define SETMASK 0x07

#define SetBitMapValue(Array, Value) (Array[Value >> BITSSHIFT] |= (1 << (Value & SETMASK)))
#define GetBitMapValueSet(Array, Value) (Array[Value >> BITSSHIFT] & (1 << (Value & SETMASK)))
#define UnsetBitMapValue(Array, Value) (Array[Value >> BITSSHIFT] &= ~(1 << (Value & SETMASK)))

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Sorts numbers in ascending order from 0 to N-1\n");
		printf("Usage: %s <max>\n", argv[0]);
		return 1;
	}

	int32_t MaxValue = atoi(argv[1]);
	if(MaxValue < 0)
	{
		fprintf(stderr, "Maximum range cannot be negative.\n");
		return 2;
	}

	uint8_t *BitMap = (uint8_t *)malloc(1 + (MaxValue / BITSPERBYTE));
	if(BitMap == NULL)
	{
		fprintf(stderr, "Could not allocate enough space for bit map.\n");
		return 3;
	}
	
	for(int32_t Index = 0; Index < 1 + (MaxValue / BITSPERBYTE); ++Index)
	{
		BitMap[Index] = 0;
	}

	int32_t Number = 0;
	while(scanf("%d", &Number) != EOF)
	{
		if((Number < 0) ||
		   (Number >= MaxValue))
		{
			continue;
		}

		SetBitMapValue(BitMap, Number);
	}

	for(int32_t Value = 0; Value < MaxValue; ++Value)
	{
		if(GetBitMapValueSet(BitMap, Value))
		{
			printf("%d\n", Value);
		}
	}

	return 0;
}
