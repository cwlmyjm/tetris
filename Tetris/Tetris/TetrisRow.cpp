#include "TetrisRow.h"

#if USE_MY_NEW_DELETE

std::queue<void*> TetrisRow::free_ptr_queue;

std::mutex TetrisRow::lock;

// 先检查free_ptr_queue是否有已经不适使用的空间。
// 如果没有，使用正常流程分配空间。
// 如果有，则直接使用该空间。
void* TetrisRow::operator new(size_t sz)
{
	std::lock_guard<std::mutex> lock_(lock);
	if (free_ptr_queue.empty())
	{
		void* ptr = malloc(sz);
		return ptr;
	}
	else
	{
		void* ptr = free_ptr_queue.front();
		free_ptr_queue.pop();
		ptr = realloc(ptr, sz);
		return ptr;
	}
}

// 删除的内存，保存到free_ptr_queue待用。
void TetrisRow::operator delete(void* ptr)
{
	std::lock_guard<std::mutex> lock_(lock);
	free_ptr_queue.push(ptr);
}

// 程序退出时，调用gc_clear清理所有不再使用的内存。
void TetrisRow::gc_clear()
{
	std::lock_guard<std::mutex> lock_(lock);
	while (!free_ptr_queue.empty())
	{
		void* ptr = free_ptr_queue.front();
		free_ptr_queue.pop();
		free(ptr);
	}
}
#else
void TetrisRow::gc_clear()
{
};
#endif
