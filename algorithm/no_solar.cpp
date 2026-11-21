#include "../globals.h"
#include "../headers/no_solar.hpp"

energy_dist no_solar_energy_dist(int load) {
    // if grid is cheaper, always use grid
    if(grid_price < 1.00) {
        energy_dist dist = {0, 0, load};
        return dist;
    } else {
        //consume all the battery first
        if(battery > 0) {
            if(battery <= load) { // battery not enough
                energy_dist dist = {0, battery, load - battery};
                battery = 0;
                return dist;
            } else { // consume all from battery
                energy_dist dist = {0, load, 0};
                battery -= load;
                return dist;
            }
        } else { // nothing in battery, still uses grid
            energy_dist dist = {0, 0, load};
            return dist;
        }
    }
}