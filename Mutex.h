#pragma once
#ifdef WIN32
#include <Windows.h>
typedef CRITICAL_SECTION MutexType;
#else
#include <pthread.h>
typedef pthread_mutex_t MutexType;
#endif

class Mutex
{
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
protected:
	MutexType m_mutex;
};

