#include "MemoryChunk.h"
#include <iostream>

MemoryChunk::MemoryChunk(size_t byteSize, size_t blockCount)
{
	m_byteSize = byteSize;
	m_freeBlock = NULL;
	for (size_t i = 0; i < blockCount; i++)
		allocBlock();
}

void MemoryChunk::allocBlock()
{
	char* mem = new char[sizeof(MemoryBlockHeader)+m_byteSize];	// 预留一个头的空间
	MemoryBlock* block = (MemoryBlock*)mem;
	block->header.ownerChunk = this;
	m_blocks.push_back(block);
	block->next = m_freeBlock;
	m_freeBlock = block;
}

size_t MemoryChunk::getSize()
{
	return m_byteSize;
}

MemoryChunk::~MemoryChunk()
{
	clear();
}

void* MemoryChunk::malloc()
{
	if (!m_freeBlock)
		allocBlock();

	void* freeMem = (void*)&m_freeBlock->placeholder;
	m_freeBlock = m_freeBlock->next;
	return freeMem;
}

void MemoryChunk::freeBlock(MemoryBlock* block)
{
	block->next = m_freeBlock;
	m_freeBlock = block;
}

/*static*/ void MemoryChunk::free(void* memory)
{
	// 找到头部，即block所属的chunk
	MemoryBlock* block = (MemoryBlock*)((char*)memory - sizeof(MemoryBlockHeader));
	block->header.ownerChunk->freeBlock(block);
}

void MemoryChunk::clear()
{
	for (auto block : m_blocks)
		delete block;

	m_blocks.clear();
}

void MemoryChunk::report()
{
	MemoryBlock* freeBlock = m_freeBlock;
	size_t freeBlockCount = 0;
	while (freeBlock)
	{
		freeBlockCount++;
		freeBlock = freeBlock->next;
	}

	std::cout << getSize() << " bytes chunk: total " << m_blocks.size() 
		<< ", free " << freeBlockCount << std::endl;
}