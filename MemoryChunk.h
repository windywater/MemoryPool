#pragma once
#include <list>
using namespace std;

class MemoryChunk;

struct MemoryBlockHeader
{
	MemoryChunk* ownerChunk;
};

struct MemoryBlock
{
	MemoryBlockHeader header;	// 记录block所属的chunk
	// block被分配时，分配内存为placeholder地址，空间时则指向下一个block
	union
	{
		char placeholder;
		MemoryBlock* next;
	};
};

class MemoryChunk
{
public:
	MemoryChunk(size_t byteSize, size_t blockCount);
	~MemoryChunk();
	
	void* malloc();
	size_t getSize();
	static void free(void* memory);
	void report();
protected:
	void allocBlock();
	void freeBlock(MemoryBlock* block);
	void clear();
protected:
	std::list<MemoryBlock*> m_blocks;
	MemoryBlock* m_freeBlock;
	int m_byteSize;
};
