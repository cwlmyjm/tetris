#include "TaskThread.h"

TaskThread::TaskThread(bool start)
{
	if (start)
	{
		Start();
	}
}

TaskThread::~TaskThread()
{
}

void TaskThread::Start()
{
	auto run = std::bind(&TaskThread::Run, this);
	current_ = std::thread(run);
}

void TaskThread::Wait()
{
	current_.join();
}

void TaskThread::PostTask(const StdClosure& task)
{
	std::unique_lock<std::mutex> lock(lock_);
	tasks_queue_.emplace(task);
	cv.notify_one();
}

void TaskThread::NotifyNoMoreTask()
{
	auto task = [&]() {
		no_more_task_ = true;
	};
	PostTask(task);
}

void TaskThread::Run()
{
	while (!no_more_task_)
	{
		StdClosure task;
		{
			std::unique_lock<std::mutex> lock(lock_);
			cv.wait(lock, [&]() {
				return tasks_queue_.size();
			});
			task = std::move(tasks_queue_.front());
			tasks_queue_.pop();
		}

		if (task)
		{
			task();
		}
	}
}
