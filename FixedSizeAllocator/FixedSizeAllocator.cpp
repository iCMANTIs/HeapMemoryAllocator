#include "FixedSizeAllocator.h"]
#include <assert.h>
FixedSizeAllocator::FixedSizeAllocator(int i_size, int i_block_count)
{
    size = i_size;
    block_count = i_block_count;
    bit_array = new BitArray(block_count);
    buffer = new char[size * block_count];
}

FixedSizeAllocator::~FixedSizeAllocator()
{
#ifdef _DEBUG
    int outstanding = 0;
    for (int i = 0; i < block_count; i++)
    {
        if (bit_array->isBitSet(i))
            outstanding++;
    }
    if (outstanding > 0)
        printf("FixedSizeAllocator destroyed with %d outstanding allocations\n", outstanding);
#endif
    delete bit_array;
    delete[] buffer;
}

void* FixedSizeAllocator::getbuffer() {
    return buffer;
}

void FixedSizeAllocator::set(size_t n) {
    to_malloc = n;
}

void* FixedSizeAllocator::alloc()
{
  /*  int index = bit_array->findFirstClearBit();
    assert(bit_array->isBitSet(index) == 0);*/
    int index = bit_array->findArea(to_malloc);
    //std::cout << bit_array->isBitSet(index) << std::endl;
    if (index == -1)
    {
        return nullptr;
    }
    //printf("alloc  index:%d  tomalloc:%d \n", index, to_malloc);
    mp[index] = to_malloc;
    for (int i = index; i < index + to_malloc; i ++)
        bit_array->setBit(i);
    //std::cout << bit_array->isBitSet(index) << std::endl;
    return &buffer[index];
}

void FixedSizeAllocator::free(void* i_ptr)
{
    if (i_ptr == NULL)
        return;
    int index = (int)((char*)i_ptr - buffer) / size;
    //printf("free  index:%d  tomalloc:%d \n", index, mp[index]);
    if (mp[index] == 0 || !bit_array->isBitSet(index))
    {
        //printf("Trying to free invalid memory\n");
    }
    else
    {
        for (int i = index, j = index + mp[index]; i < j; i++)
            bit_array->clearBit(i);
    }
    mp[index] = 0;
}
