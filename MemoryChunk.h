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
	MemoryBlockHeader header;	// ��¼block������chunk
	// block������ʱ�������ڴ�Ϊplaceholder��ַ���ռ�ʱ��ָ����һ��block
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
