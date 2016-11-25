#ifndef OBSTACLES_FROM_POINTS_IMPL_H
#define OBSTACLES_FROM_POINTS_IMPL_H

#include <vector>

#include <lms/math/point_cloud.h>
#include <lms/math/polyline.h>
#include <lms/math/vertex.h>
#include <street_environment/bounding_box.h>

class ObstaclesFromPointsImpl {
   public:
    std::vector<const lms::math::vertex2f*> cullValidPoints(
        const lms::math::PointCloud2f& pointCloud,
        const lms::math::polyLine2f& centerLine);

    void fillObstacles(const std::vector<const lms::math::vertex2f*>& points,
                       street_environment::BoundedObstacles& obstacles);

    void setLaneWidthMeter(float laneWidthMeter) {
        m_laneWidthMeter = laneWidthMeter;
    }
    void setObstacleDistanceThreshold(float obstacleDistanceThreshold) {
        m_obstacleDistanceThreshold = obstacleDistanceThreshold;
    }
    void setObstaclePointThreshold(unsigned obstaclePointThreshold) {
        m_obstaclePointThreshold = obstaclePointThreshold;
    }

   private:
    ////////////////////////////// Config Values ///////////////////////////////
    float m_laneWidthMeter;
    float m_obstacleDistanceThreshold;
    unsigned m_obstaclePointThreshold;
};

#endif  // OBSTACLES_FROM_POINTS_IMPL_H
