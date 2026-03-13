#include "include/drone.h"

#include <cmath>


void Drone::applyForce(Vector2D force, double dt) {

    if (dt <= 0) return;
    double g =9.81;
    double dragCoefficient = 0.5;
    double dragX = -dragCoefficient * velocity.x;
    double dragY = -dragCoefficient * velocity.y;

    double ax = (force.x+dragX) /mass;
    double ay = ((force.y+dragY) /mass)-g;
    velocity.x+= ax * dt;
    velocity.y+= ay * dt;

    position.x += velocity.x * dt;
    position.y += (velocity.y * dt);
}

double Drone::distance(Vector2D positionComp) {
    double dx = positionComp.x - position.x;
    double dy = positionComp.y - position.y;
    return sqrt(dx*dx + dy*dy);
}
