#include "headers/charge_battery.hpp"
#include "globals.h"
#include <cmath>

#ifndef GENERATOR_FAIL
#define GENERATOR_FAIL 2
#endif

#ifndef CLOUDY
#define CLOUDY true
#endif

// returns the amount to charge the generator by if it is/isn't cloudy
int chargeBattery(const bool forecast, const int event, const struct building_vector building_struct) {

    if (hour < 12) {

        int num_buildings = (building_struct.buildings).size()
        int num_lectures = 0;
        int num_non_lectures = 0;

        for (int i = 0; i < num_buildings; i++) {

            if (((building_struct.buildings)[i]).isLectureHall) {
                lecture_demand[hour] += ((building_struct.buildings)[i]).load;
                num_lectures++;
            } else {
                non_lecture_demand[hour] += ((building_struct.buildings)[i]).load;
                num_non_lectures++;
            }
        }
    }

    if (event == GENERATOR_FAIL) {
        return 0;
    }



    int estimate_need_lecture;
    int estimate_need_non_lecture;

    if (hour == 0) {
        estimate_need_lecture = lecture_demand[0] + (((65 * num_lectures) - lecture_demand[0]) / 11);
        estimate_need_non_lecture = non_lecture_demand[0] + (((65 * num_non_lectures) - non_lecture_demand[0]) / 11);
    } else {
        estimate_need_lecture = (2 * lecture_demand[hour]) - lecture_demand[hour - 1];
        estimate_need_non_lecture = (2 * non_lecture_demand[hour]) - non_lecture_demand[hour - 1];
    }

    int charge_to;
    if ((hour < 20) || ((hour < 23) && (forecast == CLOUDY))) {
        charge_to = estimate_need_lecture + estimate_need_non_lecture;
    } else {
        charge_to = estimate_need_lecture;
    }

    if (hour > 19) {
        double chance_grid_cheaper = ((double) 4) / ((double) 15);   // chance that the grid is cheaper and there is no battery failure on a given day
        double cumulative = std::pow(chance_grid_cheaper, (24 - hour));
        double chance_battery_needed = 1 - cumulative;
        charge_to *= (int)
    }

    charge_to = (100 < charge_to) ? (100) : (charge_to);


    
}