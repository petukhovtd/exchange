#include "timer.h"

Timer::DiffType Timer::Now()
{
  return Clock ::now().time_since_epoch().count();
}

void Timer::Start()
{
  diff = Now();
}

void Timer::Stop()
{
  diff = Now() - diff;
}
