#include "MemoryPool.h"
#include <iostream>

MemoryPool::MemoryPool()
{
	initChunks();
}

MemoryPool::~MemoryPool()
{
	clear();
}

void MemoryPool::initChunks()
{
	for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2)
	{
		MemoryChunk* chunk = new MemoryChunk(size, 1000);
		m_chunks.push_back(chunk);
	}
}

void MemoryPool::clear()
{
	for (auto chunk : m_chunks)
		delete chunk;

	m_chunks.clear();
}

void* MemoryPool::malloc(size_t size)
{
	m_mutex.lock();
	MemoryChunk* chunk = matchChunk(size);
	void* memory = chunk->malloc();
	m_mutex.unlock();

	return memory;
}

MemoryChunk* MemoryPool::matchChunk(size_t size)
{
	for (size_t i = 0; i < m_chunks.size(); i++)
	{
		MemoryChunk* chunk = m_chunks.at(i);
		if (chunk->getSize() >= size)
			return chunk;
	}

	MemoryChunk* chunk = new MemoryChunk(size, 1);
	m_chunks.push_back(chunk);
	return chunk;
}

void MemoryPool::free(void* memory)
{
	m_mutex.lock();
	MemoryChunk::free(memory);
	m_mutex.unlock();
}

void MemoryPool::report()
{
	for (auto chunk : m_chunks)
		chunk->report();
}