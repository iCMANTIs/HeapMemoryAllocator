#include "BitArray.h"
#include <intrin.h> // for _BitScanForward() and _BitScanForward64()
#include <stdio.h>

BitArray::BitArray(int size)
{
    this->size = size;
    int numInts = (size + 31) / 32; // number of integers needed to store the bits
    data = new unsigned int[numInts];
    for (int i = 0; i < numInts; i++)
    {
        data[i] = 0;
    }
}

BitArray::~BitArray()
{
    delete[] data;
}

void BitArray::setBit(int index)
{
    data[index / 32] |= (1 << (index % 32));
}

void BitArray::clearBit(int index)
{
    data[index / 32] &= ~(1 << (index % 32));
}

void BitArray::setAllBits()
{
    int numInts = (size + 31) / 32;
    for (int i = 0; i < numInts; i++)
    {
        data[i] = ~0;
    }
}

void BitArray::clearAllBits()
{
    int numInts = (size + 31) / 32;
    for (int i = 0; i < numInts; i++)
    {
        data[i] = 0;
    }
}

bool BitArray::isBitSet(int index)
{
    return (data[index / 32] & (1 << (index % 32))) != 0;
}

int BitArray::findFirstSetBit()
{
    int numInts = (size + 31) / 32;
    for (int i = 0; i < numInts; i++)
    {
        if (data[i] != 0)
        {
            // use _BitScanForward() to find the first set bit
            unsigned long index;
            _BitScanForward(&index, data[i]);
            return i * 32 + index;
        }
    }
    return -1; // no set bits found
}

int BitArray::findFirstClearBit()
{
    int numInts = (size + 31) / 32;
    for (int i = 0; i < numInts; i++)
    {
        if (data[i] != ~0)
        {
            // use _BitScanForward() to find the first clear bit
            unsigned long index;
            _BitScanForward(&index, ~data[i]);
            return i * 32 + index;
        }
    }
    return -1; // no clear bits found
}

int BitArray::findArea(int n)
{
    int numInts = (size + 31) / 32;
    int count = 0; // counter for clear bits found
    int start = -1; // index of the start of the area
    for (int i = 0; i < numInts; i++)
    {
        if (data[i] == ~0)
        {
            count = 0; // reset the counter
            start = -1; // reset the start index
            continue;
        }
        // use _BitScanForward() to find the first clear bit
        unsigned long index;
        _BitScanForward(&index, ~data[i]);
        if (count == 0)
        {
            // found the start of a new clear bit area
            start = i * 32 + index;
        }
        count++;
        if (count == n)
        {
            // found an area with enough clear bits
            return start;
        }
        // check for set bits within the current integer
        for (int j = index + 1; j < 32; j++)
        {
            if (data[i] & (1 << j))
            {
                // found a set bit, reset the counter and start index
                count = 0;
                start = -1;
                break;
            }
            count++;
            if (count == n)
            {
                // found an area with enough clear bits
                return start;
            }
        }
    }
    return -1; // no area with enough clear bits found
}


