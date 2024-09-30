## malloc

In this implementation, a global FixedSizeAllocator object is used to manage memory by pre-allocating a large block of memory and returning a portion of it when the malloc() function is called.

During the implementation process, it was discovered that the creation of std::vector objects resulted in calls to the custom malloc() and free() functions. Therefore, the malloc() and free() functions were moved to the main.cpp file and were marked as static to make them visible only within that file. This allows the FixedSizeAllocator object to be used to manage memory for the std::vector objects as well as any other allocations made through the malloc() function.

## FixedSizeAllocator

Since the memory is being allocated from a global variable, a to_malloc member variable and a set() method were added to the FixedSizeAllocator class to specify the size of the memory needed for each alloc() call. The to_malloc variable is set using the set() method and passed as an argument to the findArea() method of the BitArray object, which searches for a contiguous area of clear bits that is large enough to accommodate the requested number of blocks. The alloc() method then sets the corresponding bits in the BitArray and returns a pointer to the start of the area.

## BitArray

For the BitArray class, I implemented a method called findArea() that can find a contiguous area of n or more clear bits within the array. This method uses a nested loop to search for clear bits within each integer of the data array, and it uses the _BitScanForward() function to quickly find the first clear bit in an integer.

The implementation of the findArea() method can be found in the BitArray.cpp file. To use the method, you can call it on a BitArray object and pass in the desired number of clear bits as an argument. It will return the index of the first clear bit in the contiguous area, or -1 if no such area was found.