#include <inttypes.h>

#include "FixedSizeAllocator.h"
#include <stdio.h>

//#if 0
//void * __cdecl malloc(size_t i_size)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("malloc %zu\n", i_size);
//	return _aligned_malloc(i_size, 4);
//}
//
//void __cdecl free(void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	return _aligned_free(i_ptr);
//}
//
//void * operator new(size_t i_size)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("new %zu\n", i_size);
//	return _aligned_malloc(i_size, 4);
//}
//
//void operator delete(void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	return _aligned_free(i_ptr);
//}
//
//void * operator new[](size_t i_size)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("new [] %zu\n", i_size);
//	return _aligned_malloc(i_size, 4);
//}
//
//void operator delete [](void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	return _aligned_free(i_ptr);
//}
//#endif
/*
void* operator new(size_t i_size)
{
	static FixedSizeAllocator allocator(i_size, 10);
	void* ptr = allocator.alloc();
	if (ptr == nullptr)
	{
		printf("error\n");
		throw std::bad_alloc();
	}
	return ptr;
}


void* operator new[](size_t i_size)
{
	static FixedSizeAllocator allocator(i_size, 10);
	void* ptr =  allocator.alloc();
    if (ptr == nullptr)
    {
        throw std::bad_alloc();
    }
    return ptr;
}
}
*/
extern FixedSizeAllocator allocator;
void operator delete [](void* i_ptr)
{
	int index = (int)((char*)i_ptr -(char*)allocator.getbuffer());
	if (index > 0 && index < 1024 * 1024) {
		allocator.free(i_ptr);
	}
}

void operator delete(void* i_ptr)
{
	int index = (int)((char*)i_ptr - (char*)allocator.getbuffer());
	if (index > 0 && index < 1024 * 1024) {
		allocator.free(i_ptr);
	}
}