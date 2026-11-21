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
  vector<building> building;
  building_vector(size_t n) : building(n) {};
};

extern const double generator_price;

// output:

struct energy_dist {
  int solar;
  int battery;
  int grid;
};

struct building_return {
  vector<int> energy_dist;
  int generator = 0;

  building_return(size_t n) : energy_dist(n) {};
};

// persisiting variables:

extern int battery = 0;   // 0 to 100 units

extern int hour = 0;      // 0 to 24