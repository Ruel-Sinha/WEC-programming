#include charge_generator.hpp

#ifndef GENERATOR_FAIL
#define GENERATOR_FAIL 2
#endif

#ifndef CLOUDY
#define CLOUDY true
#endif

// returns the amount to charge the generator by if it is/isn't cloudy
int chargeGenerator(bool forecast, int event, struct building_vector buildings, ) {




    if (event == GENERATOR_FAIL) {
        return 0;
    }

    

    if (forecast == CLOUDY) {

    } else {

    }
    
}