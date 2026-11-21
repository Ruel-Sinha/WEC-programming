#include<globals.h>

using namespace std;

void cloudy_failure(building_vector buildings) {
    vector<building> allBuildings = buildings.building;
    int totalLoad = 0;
    
    for(int i = 0; i < allBuildings.size(); i++) {
        totalLoad += allBuildings[i].load;
    }

    if(grid_price < generator_price) {
        
    }   
}