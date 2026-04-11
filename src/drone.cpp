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
void Drone::update(const double &dt) {
    if (!target) return;
    double max_thrust = 30000.0;
    double dist = distance(target->getPosition());
    double closingSpeed = getVeloLength() + target->getVeloLength();
    if (closingSpeed < 0.1) closingSpeed = 0.1;
    double dynamicT = dist / closingSpeed;
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


    if (dist< 5) {
        this->isDestroyed = true;
        target->isDestroyed= true;
    }

    applyForce(force, dt);
}