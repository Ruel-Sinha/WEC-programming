#ifndef STRUCT_H
#define STRUCT_H

#include <vector>

struct energy_dist {
  int solar;
  int battery;
  int grid;
};

struct building_return {
  std::vector<int> energy_dist;
  int generator = 0;

  building_return(size_t n) : energy_dist(n) {};
};

#endif
