#pragma once
class BitArray
{
public:
    BitArray(int size);
    ~BitArray();
    void setBit(int index);
    void clearBit(int index);
    void setAllBits();
    void clearAllBits();
    bool isBitSet(int index);
    int findFirstSetBit();
    int findFirstClearBit();
    int findArea(int);
    void* getdata();
private:
    int size;
    unsigned int* data;
};

