#include "MemorySystem.h"

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager and FixedSizeAllocators
	//if (i_pHeapMemory == nullptr || i_sizeHeapMemory == 0)
	//{
	//	return false;
	//}

	//HeapManager* pHeapManager = HeapManager::Create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	//if (pHeapManager == nullptr)
	//{
	//	return false;
	//}

	//// Create FixedSizeAllocators here, as needed
	//const size_t blockSize = 32;
	//const unsigned int numBlocks = 1024;

	//FixedSizeAllocator* pAllocator = pHeapManager->CreateFixedSizeAllocator(blockSize, numBlocks);

	return true;
}

void Collect()
{
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	// Destroy your HeapManager and FixedSizeAllocators
}

