#include "../globals.h"

building_return NoChange(building_vector buildings) {
  vector<building> allBuildings = buildings.buildings;
  vector<energy_dist> buildingEnergyDists;

  for(int i = 0; i < allBuildings.size(); i++) {
    building curBuilding = allBuildings[i];
    bool isLectureHall = curBuilding.isLectureHall;
    int load = curBuilding.load;

    if(isLectureHall) {
      
    }
  }
}
