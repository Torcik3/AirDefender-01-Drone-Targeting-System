#pragma once
#include "Vector2D.h"
#include <cmath>

class Target {
    public:
    Vector2D position;
    Vector2D velocity;
    bool isTargeted=false;
    bool isDestroyed=false;

public:
    Target(Vector2D position, Vector2D velocity): position(position), velocity(velocity) {};
    void update(double dt);
    Vector2D getPosition() const {return position;}
    Vector2D getVelocity() const {return velocity;}
    double getVeloLength() const { return sqrt(velocity.x*velocity.x + velocity.y*velocity.y); }
    bool getIsDestroyed() const { return isDestroyed; }
    bool getIsTargeted() const { return isTargeted; }
};


