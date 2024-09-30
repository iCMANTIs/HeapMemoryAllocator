#pragma once
#include <iostream>
#include <vector>
#include <inttypes.h>
#include"BitArray.h"
#include <map>
class FixedSizeAllocator
{
public:
    FixedSizeAllocator(int i_size, int i_block_count);
    ~FixedSizeAllocator();
    void* alloc();
    void free(void* i_ptr);
    void set(size_t);
    void* getbuffer();
private:
    int to_malloc;
    int size;
    int block_count;
    BitArray* bit_array;
    char* buffer;
    std::map<int, int> mp;
};