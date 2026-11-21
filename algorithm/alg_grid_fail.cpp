#include "../globals.h"
#include "../headers/alg_grid_fail.hpp"

using namespace std;

const double generator_price = 1.00;

building_return grid_failure(building_vector buildings) {
    vector<building> allBuildings = buildings.buildings;
    vector<energy_dist> buildingEnergyDists;
    int solar_energy = 200;

    // last hour; use up all the battery first
    if(hour == 23) {
        for(int i = 0; i < allBuildings.size(); i++) {
            int load = allBuildings[i].load;
            bool isLectureHall = allBuildings[i].isLectureHall;
            
            if(isLectureHall) {
                if(battery >= load) {
                    buildingEnergyDists.push_back(energy_dist{0, load, 0});
                    battery -= load;
                }else {
                    buildingEnergyDists.push_back(energy_dist{0, battery, 0});
                    battery = 0;
                }
            } else {
                if(solar_energy >= load) {
                    buildingEnergyDists.push_back(energy_dist{load, 0, 0});
                    solar_energy -= load;
                }else {
                    int loadRem = load - solar_energy;

                    if(battery >= loadRem) {
                        buildingEnergyDists.push_back(energy_dist{solar_energy, loadRem, 0});
                        battery -= loadRem;
                    } else {
                        buildingEnergyDists.push_back(energy_dist{solar_energy, battery, 0});
                        battery = 0;
                    }
                }
            }
        }

        return building_return{buildingEnergyDists};
    }

    for(int i = 0; i < allBuildings.size(); i++) {
        int load = allBuildings[i].load;
        int lecture = allBuildings[i].isLectureHall;

        // if solar is available, use solar
        if(solar_energy >= 0 && !allBuildings[i].isLectureHall) {
            if (solar_energy <= load) { // not enough solar
                if (battery <= load - solar_energy) {// not enough solar and battery
                    energy_dist dist = {solar_energy, battery, 0}; // give as much energy as poissble
                    battery = 0;
                    buildingEnergyDists.push_back(dist);
                } else{ // consume all solar and some battery
                    energy_dist dist = {solar_energy, load - solar_energy, 0};
                    battery -= load - solar_energy;
                    buildingEnergyDists.push_back(dist);
                }
            } else{ // consume all solar
                energy_dist dist = {load, 0, 0};
                solar_energy -= load;
                buildingEnergyDists.push_back(dist);
            }
        } else {
            //consume the battery
            if(battery > 0) {
                if(battery <= load) { // battery not enough
                    energy_dist dist = {0, battery, 0}; // give as much energy as possible
                    battery = 0;
                    buildingEnergyDists.push_back(dist);
                } else { // consume all from battery
                    energy_dist dist = {0, load, 0};
                    battery -= load;
                    buildingEnergyDists.push_back(dist);
                }
            }
        }
    }

    building_return dist_return = {buildingEnergyDists};

    return dist_return;
}