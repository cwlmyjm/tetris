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
	std::lock_guard<std::mutex> lock(lock_);
	tasks_queue_.emplace(task);
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
			std::lock_guard<std::mutex> lock(lock_);
			if (tasks_queue_.empty())
			{
				continue;
			}
			task = std::move(tasks_queue_.front());
			tasks_queue_.pop();
		}

		if (task)
		{
			task();
		}
	}
}
