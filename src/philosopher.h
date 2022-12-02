#pragma once
#include <string>
#include <utility>
#include <stdlib.h>
#include "fork.h"

class Philosopher
{
private:
  std::string name;
  size_t think_time_ms;
  size_t eat_time_ms;
  Fork *left_fork{}, *right_fork{};

public:
  Philosopher(std::string name, size_t think_time, size_t eat_time)
      : name(std::move(name)),
        think_time_ms(think_time),
        eat_time_ms(eat_time)
  {
  }

  void set_left_fork(Fork *left_fork);
  void set_right_fork(Fork *right_fork);

  Fork *get_left_fork();
  Fork *get_right_fork();

  void think();
  void eat();
  std::string get_name();

  void grab_forks();
  void release_forks();
};