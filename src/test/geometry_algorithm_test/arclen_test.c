#include <stdio.h>
#include "../../lib/geometry_algorithm/geometry_algorithm.h"
#include "../../lib/geometry_algorithm/geodist.h"
#include "../test.h"

/**
 * @brief arclen_test 测试调用arclen的函数，计算地球上某两点的距离的函数
 */
void arclen_test() {

    double paris_lat = 49.010;
    double paris_lon = -2.548;

    double pers_lat = -31.940;
    double pers_lon = -115.967;

    double d = 0.0;
    if(geodist (paris_lat, paris_lon, pers_lat, pers_lon, &d) == 0){
        printf("%s\n", "get the distance is:");
        printf("%f", d);
    }

}
