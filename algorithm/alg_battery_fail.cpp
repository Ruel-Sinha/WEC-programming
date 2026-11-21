#include "../globals.h"
#include "../headers/alg_battery_fail.hpp"

using namespace std;

const double generator_price = 1.00;

building_return grid_failure(building_vector buildings) {
    vector<building> allBuildings = buildings.buildings;
    vector<energy_dist> buildingEnergyDists;
    int solar_energy = 200;

    for(int i = 0; i < allBuildings.size(); i++) {
        int load = allBuildings[i].load;
        if (allBuildings[i].isLectureHall) {
            energy_dist dist = {0, 0, load};
            buildingEnergyDists.push_back(dist);
        }
        else if (solar_energy <= load) { // not enough solar
            energy_dist dist = {solar_energy, 0, load - solar_energy};
            buildingEnergyDists.push_back(dist);
        } else{ // consume all solar
            energy_dist dist = {load, 0, 0};
            solar_energy -= load;
            buildingEnergyDists.push_back(dist);
        }
    }

    building_return dist_return = {buildingEnergyDists};

    return dist_return;
}