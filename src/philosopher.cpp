#include "philosopher.h"
#include <iostream>
#include <ctime>
#include <mutex>
#include <unistd.h>

static std::mutex log_mtx;

void Philosopher::set_left_fork(Fork *left_fork)
{
  this->left_fork = left_fork;
}

void Philosopher::set_right_fork(Fork *right_fork)
{
  this->right_fork = right_fork;
}

Fork *Philosopher::get_left_fork()
{
  return this->left_fork;
}

Fork *Philosopher::get_right_fork()
{
  return this->right_fork;
}

std::string Philosopher::get_name()
{
  return this->name;
}

void Philosopher::think()
{
  std::cout << this->name << " is thinking now.\n";
  usleep(this->think_time_ms * 1000);
}

void Philosopher::eat()
{
  std::cout << this->name << " is eating now.\n";
  usleep(this->eat_time_ms * 1000);
}

void Philosopher::grab_forks()
{
  std::cout << this->name << " tries to take forks.\n";

  std::clock_t start_time = std::clock() * 1000;

  while (true)
  {
    if (this->left_fork->try_lock())
    {
      if (!this->right_fork->try_lock())
      {
        this->left_fork->unlock();

        // next try
        continue;
      }

      std::cout << this->name << " was waiting to get forks for " << ((std::clock() * 1000. - start_time) / CLOCKS_PER_SEC) << " ms\n";
      return;
    }
  }
}

void Philosopher::release_forks()
{
  std::cout << this->name << " released his forks.\n";
  this->left_fork->unlock();
  this->right_fork->unlock();
}