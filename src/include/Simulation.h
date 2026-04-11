
#ifndef DRONE_PIDCONTROLER_SIMULATION_H
#define DRONE_PIDCONTROLER_SIMULATION_H
#include <thread>

#include "World.h"


class Simulation {
private:
    World world;
    std::thread t1;
    std::thread t2;

    void spawnTarget();
    void spawnDrone();
public:
    Simulation()=default;
    void start();
    void run();
    void stop();

};


#endif //DRONE_PIDCONTROLER_SIMULATION_H