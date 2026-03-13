//
// Created by torcik on 11.03.2026.
//

#include "include/target.h"

void Target::update(double dt) {
    position.x=position.x+velocity.x*dt;
    position.y=position.y+velocity.y*dt;
}
