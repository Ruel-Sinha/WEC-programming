#include <stdbool.h>
#include <vector>

using namespace std;

// input:

extern double grid_price;
/*
0 - no event
1 - cloudy weather
2 - generator failture
3 - battery failture
4 - grid failture
*/
extern int random_event;

extern bool forecast;   // 1 == cloudy

struct building {
  bool isLectureHall;
  int load;
};

struct building_vector {
  vector<building> buildings;
  building_vector(size_t n) : buildings(n) {};
};

extern const double generator_price;

// output:

struct energy_dist {
  int solar;
  int battery;
  int grid;
};

struct building_return {
  vector<energy_dist> building_energy_dists;
  int generator = 0;

  building_return(size_t n) : building_energy_dists(n) {};
};

// persisiting variables:

extern int battery = 0;   // 0 to 100 units

extern int hour = 0;      // 0 to 24