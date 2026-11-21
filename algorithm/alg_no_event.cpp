#include "../globals.h"
#include "../headers/no_solar.hpp"
#include "../headers/alg_no_event.hpp"

const double generator_price = 1.00;

building_return NoChange(building_vector buildings) {
  vector<building> allBuildings = buildings.buildings;
  vector<energy_dist> buildingEnergyDists;
  int solarRem = 200; // 200 units of solar

  for (int i = 0; i < allBuildings.size(); i++) {
    building curBuilding = allBuildings[i];
    bool isLectureHall = curBuilding.isLectureHall;
    int load = curBuilding.load;

    if (isLectureHall) {
      buildingEnergyDists.push_back(no_solar_energy_dist(load));
    }else {
      if(solarRem <= 0) {
        buildingEnergyDists.push_back(no_solar_energy_dist(load));
      } else {
        if(solarRem >= load) {
          buildingEnergyDists.push_back(energy_dist{load, 0, 0});
          solarRem -= load;
        } else {
          int loadRem = load - solarRem; // remaining load after solar
          if(grid_price <= generator_price) {
            buildingEnergyDists.push_back(energy_dist(solarRem, loadRem, 0));
          } else {
            if(battery >= loadRem) {
              buildingEnergyDists.push_back(energy_dist(solarRem, 0, loadRem));
              battery -= loadRem;
            } else {
              loadRem -= battery; // after using all the battery
              buildingEnergyDists.push_back(energy_dist(solarRem, loadRem, battery));
            }
          }
          solarRem = 0;
        }
      }
    }

  }

  return building_return(buildingEnergyDists);
}

/*
grid failure


*/