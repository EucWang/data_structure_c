#include "geodist.h"
#include "geometry_algorithm.h"

static void getSPointFromLatLon(double lat, double lon, SPoint *p) {
    p->rho = EARTH_RADIUS;
    p->theta = -1.0 * DEG2RAD(lon);
    p->phi = (DEG2RAD(-1.0 * lat)) + DEG2RAD(90.0);
    return;
}

/**
 * @brief geodist 计算2个经纬度表示的地球上的两个地点之间的距离
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @param d  返回的距离, 海里单位
 * @return
 */
int geodist(double lat1,
            double lon1,
            double lat2,
            double lon2,
            double *d) {

    if (lat1 < -90.0 || lat1 > 90.0 || lat2 < -90.0 || lat2 > 90.0 ) {
        return -1;
    }
    if (lon1 < -180.0 || lon1 > 180.0 || lon2 < -180.0 || lon2 > 180.0 ) {
        return -1;
    }

    SPoint p1, p2;

    //将经纬度转成球座标点
    getSPointFromLatLon (lat1, lon1, &p1);
    getSPointFromLatLon (lat2, lon2, &p2);

    arclen (&p1, &p2, d);
    return 0;
}

