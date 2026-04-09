#pragma once
#include <cmath>
#include <memory>

#include "target.h"


class Drone {
private:
    double mass;
    Vector2D position;
    Vector2D velocity;
    std::shared_ptr<Target> target;

public:
    Drone(double mass,Vector2D position): mass(mass), position(position), velocity(0.0, 0.0){}
    void applyForce(Vector2D force, double dt);
    Vector2D getPosition() const { return position; }
    Vector2D getVelocity() const { return velocity; }
    double getMass() const { return mass; }
    double getVeloLength() const { return sqrt(velocity.x*velocity.x + velocity.y*velocity.y); }
    double distance(Vector2D position);
    void setTarget(const std::shared_ptr<Target> &target) {this->target = target;}
    std::shared_ptr<Target> getTarget() const { return target; }



};
