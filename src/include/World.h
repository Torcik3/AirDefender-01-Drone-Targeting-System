#include "../../vector/Vector.h"
#include <mutex>
#include "drone.h"

#ifndef DRONE_PIDCONTROLER_WORLD_H
#define DRONE_PIDCONTROLER_WORLD_H

struct World {
    Vector<std::shared_ptr<Drone>> drones;
    Vector<std::shared_ptr<Target>> targets;
    std::mutex mtx;
    bool running=true;
};

#endif //DRONE_PIDCONTROLER_WORLD_H