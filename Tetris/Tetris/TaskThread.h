#pragma once
#include <functional>
#include <queue>
#include <mutex>

typedef std::function<void()> StdClosure;

// 一个简单的消息队列实现
class TaskThread
{
public:
	TaskThread() = default;
	TaskThread(bool start);
	~TaskThread();
	
	void Start();
	void Wait();

	void PostTask(const StdClosure& task);
	void NotifyNoMoreTask();

protected:
	void Run();

private:
	bool no_more_task_ = false;
	std::queue<StdClosure> tasks_queue_;
	std::mutex lock_;
	std::condition_variable cv;
	std::thread current_;
};

