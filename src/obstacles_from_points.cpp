#include "obstacles_from_points.h"

#include <lms/math/vertex.h>

bool ObstaclesFromPoints::initialize() {
    pointCloud = readChannel<lms::math::PointCloud2f>("POINT_CLOUD");
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    culledPointCloud =
        writeChannel<lms::math::PointCloud2f>("CULLED_POINT_CLOUD");
    obstacles = writeChannel<street_environment::BoundedObstacles>("OBSTACLES");

    impl =
        std::unique_ptr<ObstaclesFromPointsImpl>(new ObstaclesFromPointsImpl);
    configureImpl();
    return true;
}

bool ObstaclesFromPoints::deinitialize() { return true; }

void ObstaclesFromPoints::configsChanged() { configureImpl(); }

bool ObstaclesFromPoints::cycle() {
    if (pointCloud->points().size() == 0) {
        return true;
    }
    impl->cullValidPoints(*pointCloud, *centerLine, *culledPointCloud);
    if (culledPointCloud->points().size() == 0) {
        return true;
    }
    obstacles->clear();
    impl->fillObstacles(*culledPointCloud, *obstacles);
    return true;
}

void ObstaclesFromPoints::configureImpl() {
    impl->setLaneWidthMeter(config().get<float>("laneWidthMeter", 0.4));
    impl->setObstacleDistanceThreshold(
        config().get<float>("obstacleDistanceThreshold", 0.05));
    impl->setObstaclePointThreshold(
        config().get<int>("obstaclePointThreshold", 10));
}
