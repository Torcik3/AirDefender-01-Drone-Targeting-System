#include "include/drone.h"

#include <cmath>
#include <iostream>
void Drone::applyForce(Vector2D force, double dt) {

    if (dt <= 0) return;

    double dragCoefficient = 0.5;
    double dragX = -dragCoefficient * velocity.x;
    double dragY = -dragCoefficient * velocity.y;

    double ax = (force.x+dragX) /mass;
    double ay = ((force.y+dragY) /mass);
    velocity.x+= ax * dt;
    velocity.y+= ay * dt;

    double absoluteMaxVelocity = 2000.0;
    double currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    if (currentSpeed > absoluteMaxVelocity) {
        velocity.x = (velocity.x / currentSpeed) * absoluteMaxVelocity;
        velocity.y = (velocity.y / currentSpeed) * absoluteMaxVelocity;
    }
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    //std::cout<<velocity.x<<" "<<velocity.y<<std::endl;
}
double Drone::distance(Vector2D positionComp) {
    double dx = positionComp.x - position.x;
    double dy = positionComp.y - position.y;
    return sqrt(dx*dx + dy*dy);
}
void Drone::update(const double &dt) {
    if (!target) return;
    double max_thrust = 30000.0;
    double dist = distance(target->getPosition());

    Vector2D relativeVelocity;
    relativeVelocity.x = velocity.x - target->getVelocity().x;
    relativeVelocity.y = velocity.y - target->getVelocity().y;

    double closingSpeed = std::sqrt(relativeVelocity.x * relativeVelocity.x + relativeVelocity.y * relativeVelocity.y);
    if (closingSpeed < 0.1) closingSpeed = 0.1;
    double dynamicT = dist / closingSpeed;
    if (dynamicT > 1) {
        dynamicT = 1;
    }
    else if (dynamicT<0.5) {
        dynamicT = 0.02;
    }
    else if (dynamicT<0.2) {
        dynamicT = 0.001;
    }
    Vector2D predictedTargetPos;
    predictedTargetPos.x = target->getPosition().x + target->getVelocity().x * dynamicT;
    predictedTargetPos.y = target->getPosition().y + target->getVelocity().y * dynamicT;

    Vector2D force;
    force.x = pidX.calculatePid(predictedTargetPos.x, position.x, dt);
    force.y = pidY.calculatePid(predictedTargetPos.y, position.y, dt);
    if (force.x > max_thrust) force.x = max_thrust;
    if (force.x < -max_thrust) force.x = -max_thrust;
    if (force.y > max_thrust) force.y = max_thrust;
    if (force.y < -max_thrust) force.y = -max_thrust;

std::cout<<dist<<std::endl;
    if (dist<100) {
        this->isDestroyed = true;
        target->isDestroyed= true;
    }

    applyForce(force, dt);
}