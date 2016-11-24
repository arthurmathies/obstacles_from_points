#include "obstacles_from_points.h"

bool ObstaclesFromPoints::initialize() {
    points = readChannel<lms::math::polyLine2f>("POINTS");
    centerLine = readChannel<lms::math::polyLine2f>("CENTER_LINE");
    obstacles =
        writeChannel<street_environment::EnvironmentObjects>("OBSTACLES");
    return true;
}

bool ObstaclesFromPoints::deinitialize() { return true; }

void ObstaclesFromPoints::configsChanged() {}

bool ObstaclesFromPoints::cycle() {
    obstacles->objects.clear();
    if (points->points().size() == 0) {
        return true;
    }

    std::vector<const lms::math::vertex2f*> validPoints =
        impl->cullValidPoints(*points, *centerLine);
    if (validPoints.size() == 0) {
        return true;
    }

    impl->fillObstacles(validPoints, *obstacles);
    return true;
}
