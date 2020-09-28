// normal_distribution example
#include <iostream>
#include <chrono>
#include <random>

int main()
{
  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::normal_distribution<double> distribution (0.0,1.0);

 	double randgen =  distribution(generator)

  return randgen;
}