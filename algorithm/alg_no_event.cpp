#include "../globals.h"

building_return NoChange(building_vector a[]) {
  size = sizeof(a.building);
  solar_rem = 200;

  building_return bu(size);

  for (int i = 0; i < size; i++) {
    if (a[i].isLectureHall == true) {
    } else {
      if (a[i].load < solar_rem) {
        bu[i].energy_dist
      }
    }
  }
}
