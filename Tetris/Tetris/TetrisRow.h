#pragma once
#include <vector>
#include <queue>
#include <mutex>

#define USE_MY_NEW_DELETE 0

class TetrisRow
{
public:
	virtual ~TetrisRow() = default;

	virtual bool GetValue(int index) = 0;

	virtual void SetValue(int index, bool value) = 0;

	virtual bool AllTrue() = 0;

	virtual void ClearData() = 0;

#if USE_MY_NEW_DELETE
private:
	static std::queue<void*> free_ptr_queue;

	static std::mutex lock;

public:
	static void* operator new(size_t sz);

	static void operator delete(void* ptr);
	
	static void gc_clear();
#else
	static void gc_clear();
#endif

};