#include "stdafx.h"
#include "WorkerQueue.h"

void WorkerQueue::Start()
{
  std::lock_guard<std::mutex> lock(mutex);
  exiting = false;
  if (thread.joinable())
  {
    throw std::runtime_error("WorkerQueue Thread already running when start was called.");
  }
  thread = std::thread([this]() {
    std::unique_lock<std::mutex> lock(mutex);
    while (!exiting)
    {
      if (queue.empty())
      {
        cv.wait(lock);
        continue;
      }
      auto job = queue.front();
      queue.pop();
      job();
    }
  });

}

void WorkerQueue::Stop()
{
  std::unique_lock<std::mutex> lock(mutex);
  exiting = true;
  lock.unlock();
  cv.notify_all();
  thread.join();
}

void WorkerQueue::Queue(std::function<void()> func)
{
  std::unique_lock<std::mutex> lock(mutex);
  queue.emplace(std::move(func));
  lock.unlock();
  cv.notify_all();
}
