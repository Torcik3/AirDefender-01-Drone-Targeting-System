#pragma once

class Vector2D {
public:
    double x,y;
    Vector2D() : x(0), y(0) {};
    Vector2D(double x,double y) : x(x), y(y) {};

};

class Drone {
private:
    double mass;
    Vector2D position;
    Vector2D velocity;
public:
    Drone(double mass,Vector2D position): mass(mass), position(position), velocity(0.0, 0.0){}
    void applyForce(Vector2D force, double dt);

    Vector2D getPosition() const { return position; }
    Vector2D getVelocity() const { return velocity; }

};
