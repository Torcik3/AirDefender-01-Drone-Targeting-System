#pragma once

#include "drone.h"
class Target {
    public:
    Vector2D position;
    Vector2D velocity;

    Target(Vector2D position, Vector2D velocity): position(position), velocity(velocity) {};
    void update(double dt);
    Vector2D getPosition() const {return position;}
    Vector2D getVelocity() const {return velocity;}
    double getVeloLength() const { return sqrt(velocity.x*velocity.x + velocity.y*velocity.y); }
};


