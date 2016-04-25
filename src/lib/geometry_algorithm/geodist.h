
#ifndef GEODIST_H
#define GEODIST_H

/**
  * 地球半径，
  */
#define EARTH_RADIUS 3440.065

/**
 * @brief geodist 计算2个经纬度表示的地球上的两个地点之间的距离
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @param d  返回的距离
 * @return
 */
int geodist(double lat1,
            double lon1,
            double lat2,
            double lon2,
            double *d);

#endif
