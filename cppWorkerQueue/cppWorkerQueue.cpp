// cppWorkerQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <thread>

#include "WorkerQueue.h"

using namespace std;

int main()
{
  cout << "Main thread is " << std::this_thread::get_id() << endl;
  WorkerQueue queue;
  queue.Start();

  queue.Queue([]() {
    std::cout << "The worker thread is " << std::this_thread::get_id() << endl; }
  );

  std::this_thread::sleep_for(std::chrono::seconds(3));
  queue.Stop();

  return 0;
}
