#pragma once
#include <mutex>

class Fork
{
public:
  void unlock();
  bool try_lock();

private:
  std::mutex mtx;
};