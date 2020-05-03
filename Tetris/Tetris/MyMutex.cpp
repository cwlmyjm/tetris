#include "MyMutex.h"

namespace my {

	mutex::mutex()
	{
		InitializeCriticalSection(&sec);
	}

	mutex::~mutex()
	{
		DeleteCriticalSection(&sec);
	}

	lock_guard::lock_guard(mutex& _lock)
		: lock(&_lock)
	{
		EnterCriticalSection(&lock->sec);
	}

	lock_guard::~lock_guard()
	{
		LeaveCriticalSection(&lock->sec);
	}
}