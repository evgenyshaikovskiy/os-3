#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include "src/philosopher.h"

static std::vector<Philosopher> philosophers;

void init_philosopher(const std::string &name, int think_time_ms, int eat_time_ms)
{
    std::cout << "Initializing philosopher " << name << "\n";
    Philosopher philosopher = Philosopher(name, think_time_ms, eat_time_ms);
    philosophers.push_back(philosopher);

    if (philosophers.size() == 1)
    {
        philosophers[0].set_left_fork(new Fork());
        philosophers[0].set_right_fork(new Fork());

        return;
    }

    std::vector<Philosopher>::iterator philosopher_iterator = philosophers.end();

    (philosopher_iterator - 1)->set_left_fork((philosopher_iterator - 2)->get_left_fork());
    (philosopher_iterator - 1)->set_right_fork(new Fork());
}

void launch(size_t index)
{
    while (1)
    {
        philosophers[index].think();
        philosophers[index].grab_forks();
        philosophers[index].eat();
        philosophers[index].release_forks();
    }
}

void start_dinner(size_t time_ms)
{
    std::vector<std::thread> p_threads;
    for (size_t i = 0; i < philosophers.size(); i++)
    {
        p_threads.push_back(std::thread(launch, i));
    }

    std::thread timer(usleep, time_ms * 1000);
    timer.join();

    for (std::thread &th : p_threads)
    {
        th.detach();
    }

    std::cout << "dinner is finished\n";
}

int main(int, char **)
{
    std::cout << "Start of program\n";

    init_philosopher("Saint Thomas Aquinas", 1, 2);
    init_philosopher("Aristotle", 2, 3);
    init_philosopher("René Descartes", 3, 5);

    start_dinner(100);
}
