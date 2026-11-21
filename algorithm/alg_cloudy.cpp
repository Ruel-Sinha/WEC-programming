#include "../globals.h"
#include "../headers/no_solar.hpp"
#include "../headers/alg_cloudy.hpp"

using namespace std;

extern const double generator_price;

building_return cloudy_failure(building_vector buildings) {
    vector<building> allBuildings = buildings.buildings;
    vector<energy_dist> buildingEnergyDists;

    if(hour == 23) {
        for(int i = 0; i < allBuildings.size(); i++) {
            int load = allBuildings[i].load;

            if(battery >= load) {
                buildingEnergyDists.push_back(energy_dist{0, load, 0});
                battery -= load;
            } else {
                buildingEnergyDists.push_back(energy_dist{0, battery, load - battery});
                battery = 0;
            }
        }

        return building_return{buildingEnergyDists};
    }
    
    for(int i = 0; i < allBuildings.size(); i++) {
        int load = allBuildings[i].load;

        buildingEnergyDists.push_back(no_solar_energy_dist(load));
    }

    building_return dist_return = {buildingEnergyDists};

    return dist_return;
}