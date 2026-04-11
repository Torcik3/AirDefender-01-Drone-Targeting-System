
#include "include/Simulation.h"
#include <iostream>
#include <thread>
#include "../vector/Vector.h"
#include <chrono>

void Simulation::spawnTarget() {
    while (world.running) {
        {
            std::lock_guard<std::mutex> lock(world.mtx);
            std::shared_ptr<Target> target=std::make_shared<Target>(Vector2D(0,0),Vector2D(0,1000));
            world.targets.PushBack(target);
        }

        std::cout<<"nowy target"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}
void Simulation::spawnDrone() {
    PidController pidx(300.0, 0.5, 300.0, 5000.0);
    PidController pidy(300.0, 0.5, 300.0, 5000.0);

    while (world.running) {
        {
            std::lock_guard<std::mutex> lock(world.mtx);
            if (world.targets.Size()>world.drones.Size()) {

                std::shared_ptr<Drone> drone=std::make_shared<Drone>(90, Vector2D(0.0,0.0),pidx,pidy);
                for (const auto& t: world.targets) {
                    if (t->isTargeted==false) {
                        drone->setTarget(t);
                        break;
                    }

                }
                world.drones.PushBack(drone);
                std::cout<<"nowy drone"<<std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
void Simulation::start() {

    t1=std::thread(&Simulation::spawnTarget,this);
    t2=std::thread(&Simulation::spawnDrone,this);
    std::cout<<"radar on"<<std::endl;

}
void Simulation::run() {
    auto lastTime=std::chrono::high_resolution_clock::now();

    while (world.running) {
        {
            auto currentTime=std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed=currentTime-lastTime;
            lastTime=currentTime;

            {
                std::lock_guard<std::mutex> lock(world.mtx);

                for (const auto &t:world.targets) {
                        t->update(elapsed.count());
                }
                for (const auto &d:world.drones) {
                        d->update(elapsed.count());
                }

                for (unsigned long long i=0;i<world.targets.Size();) {
                    if (world.targets[i]->isDestroyed==true) {
                        world.targets[i]=world.targets[world.targets.Size()-1];
                        world.targets.PopBack();
                        std::cout<<"target destroyed"<<std::endl;
                    }
                    else {i++;}
                }

                for (unsigned long long i=0;i<world.drones.Size();) {
                    if (world.drones[i]->getIsDestroyed()==true) {
                        world.drones[i]=world.drones[world.drones.Size()-1];
                        world.drones.PopBack();
                    }
                    else {i++;}
                }

            }
            std::this_thread::sleep_for(std::chrono::milliseconds(16));

        }
    }
}
void Simulation::stop() {
    world.running=false;
}
