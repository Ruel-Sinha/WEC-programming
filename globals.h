#include <vector>
#include<stdbool.h>

using namespace std;

extern int grid_price;
/*
0 - no event
1 - cloudy weather
2 - generator failture
3 - battery failture
4 - grid failture
*/
extern int random_event;
extern bool forecast;

struct building {
    bool isLectureHall;
    int load;
};
