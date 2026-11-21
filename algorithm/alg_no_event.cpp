#include "../globals.h"
#include "../headers/no_solar.hpp"
#include "../headers/alg_no_event.hpp"

extern const double generator_price;

building_return NoChange(building_vector buildings) {
  vector<building> allBuildings = buildings.buildings;
  vector<energy_dist> buildingEnergyDists;
  int solarRem = 200; // 200 units of solar

  if(hour == 23) {
    for(int i = 0; i < allBuildings.size(); i++) {
      bool isLectureHall = allBuildings[i].isLectureHall;
      int load = allBuildings[i].load;

      if(isLectureHall) {
        if(battery >= load) {
          buildingEnergyDists.push_back(energy_dist{0, load, 0});
          battery -= load;
        } else {
          int loadRem = load - battery;
          buildingEnergyDists.push_back(energy_dist{0, battery, loadRem});
          battery = 0;
        }
      } else {
        if(solarRem >= load) {
          buildingEnergyDists.push_back(energy_dist{load, 0, 0});
          solarRem -= load;
        } else {
          int loadRem = load - solarRem;
          if(battery >= loadRem) {
            buildingEnergyDists.push_back(energy_dist{solarRem, loadRem, 0});
            battery -= loadRem;
          } else {
            loadRem -= battery;
            buildingEnergyDists.push_back(energy_dist{solarRem, battery, loadRem});
            loadRem = 0;
          }

          solarRem = 0;
        }
      }
    }

    return building_return{buildingEnergyDists};
  }

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
            buildingEnergyDists.push_back(energy_dist{solarRem, 0, loadRem});
          } else {
            if(battery >= loadRem) {
              buildingEnergyDists.push_back(energy_dist{solarRem, loadRem, 0});
              battery -= loadRem;
            } else {
              loadRem -= battery; // grid after using all the battery
              buildingEnergyDists.push_back(energy_dist{solarRem, battery, loadRem});
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