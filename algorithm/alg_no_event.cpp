#include "../globals.h"

building_return NoChange(building_vector a) {
  int size = sizeof(a.buildings);
  int solar_rem = 200;

  building_return bu(size);

  vector<building> allBuildings = a.buildings;

  size = allBuildings.size();

  for (int i = 0; i < size; i++) {
    if (allBuildings[i].isLectureHall == true) {
      if (grid_price > 1 && battery)
        battery
    } else {
      if (allBuildings[i].load < solar_rem) {
        bu.building_energy_dists[i].solar = allBuildings[i].load;
      }
    }
  }
  return bu;
}
