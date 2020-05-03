#pragma once
#include <Windows.h>

namespace my {

	class lock_guard;

	class mutex
	{
		friend class lock_guard;
	public:
		mutex();
		~mutex();
	private:
		CRITICAL_SECTION sec;
	};

	class lock_guard
	{
	public:
		lock_guard(mutex& _lock);
		~lock_guard();
	private:
		mutex* lock = nullptr;
	};
}