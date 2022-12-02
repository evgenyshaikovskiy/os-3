#include "fork.h"

void Fork::unlock()
{
    mtx.unlock();
}

bool Fork::try_lock()
{
    return mtx.try_lock();
}