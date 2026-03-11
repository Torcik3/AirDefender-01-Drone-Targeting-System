#include "drone.h"

void Drone::applyForce(Vector2D force, double dt) {

    if (dt <= 0) return;

    double ax = force.x /mass;
    double ay = force.y /mass;
    velocity.x+= ax * dt;
    velocity.y+= ay * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}


