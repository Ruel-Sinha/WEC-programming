#include "../globals.h"
#include "../headers/no_solar.hpp"

using namespace std;

building_return cloudy_failure(building_vector buildings) {
    vector<building> allBuildings = buildings.buildings;
    vector<energy_dist> buildingEnergyDists;
    
    for(int i = 0; i < allBuildings.size(); i++) {
        int load = allBuildings[i].load;

        buildingEnergyDists.push_back(no_solar_energy_dist(load))
    }

    building_return dist_return = {buildingEnergyDists};

    return dist_return;
}