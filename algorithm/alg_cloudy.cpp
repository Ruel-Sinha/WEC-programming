#include "../globals.h"

using namespace std;

building_return cloudy_failure(building_vector buildings) {
    vector<building> allBuildings = buildings.buildings;
    vector<energy_dist> buildingEnergyDists;
    
    for(int i = 0; i < allBuildings.size(); i++) {
        int load = allBuildings[i].load;

        if(grid_price < generator_price) {
            energy_dist dist = {0, 0, load};
            buildingEnergyDists.push_back(dist);
        } else {
            if(battery > 0) {
                if(battery <= load) {
                    energy_dist dist = {0, battery, load - battery};
                    battery = 0;
                    buildingEnergyDists.push_back(dist);
                } else {
                    energy_dist dist = {0, load, 0};
                    battery -= load;
                    buildingEnergyDists.push_back(dist);
                }
            } else {
                energy_dist dist = {0, 0, load};
                buildingEnergyDists.push_back(dist);
            }
        }
    }

    building_return dist_return = {buildingEnergyDists};

    return dist_return;
}