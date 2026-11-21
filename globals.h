#include <stdbool.h>
#include <vector>

using namespace std;

extern int grid_price;
/*
0 - no event
1 - cloudy weather
2 - generator failture
3 - battery failture
4 - grid failture
*/
extern int random_event;
extern bool forecast;

struct building {
  bool isLectureHall;
  int load;
};

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
