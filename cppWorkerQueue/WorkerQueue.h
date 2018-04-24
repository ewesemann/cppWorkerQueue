#pragma once
#include <queue>
#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>

class WorkerQueue
{
  mutable std::mutex mutex;
  mutable std::condition_variable cv;
  std::queue<std::function<void()>> queue;
  std::thread thread;
  bool exiting = false;
public:
  WorkerQueue() = default;
  void Start();
  void Stop();
  void Queue(std::function<void()> func);
};

