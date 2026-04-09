#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "src/include/PidController.h"
#include "vector/Vector.h"
#include "src/include/drone.h"
#include "src/include/target.h"
#include <mutex>
#include <thread>

void runSim(Drone& drone,Target& rocket, PidController& pidx, PidController& pidy, Vector<Vector2D>& historyDrone, Vector<Vector2D>& historyTarget) {

     double dt=0.001;
     double dist;
     double max_thrust = 30000.0;
     Vector2D temp;
     Vector2D force;
     Vector2D target;
    for (int i=0; i<20000; i++) {
        rocket.update(dt);
        dist=drone.distance(rocket.getPosition());
        double closingSpeed = drone.getVeloLength()+rocket.getVeloLength();
        if (dist< 5) {
            std::cout << "TARGET INTERCEPTED AT STEP " << i  << std::endl;
            std::cout << "distance:" << dist << std::endl;
            break;
        }

        double dynamicT=dist/closingSpeed;
        target.x=rocket.getPosition().x+rocket.getVelocity().x*dynamicT;
        target.y=rocket.getPosition().y+rocket.getVelocity().y*dynamicT;

        temp=drone.getPosition();
        force.x=pidx.calculatePid(target.x,temp.x, dt);
        force.y=pidy.calculatePid(target.y,temp.y, dt);


        if (force.x > max_thrust) force.x = max_thrust;
        if (force.x < -max_thrust) force.x = -max_thrust;
        if (force.y > max_thrust) force.y = max_thrust;
        if (force.y < -max_thrust) force.y = -max_thrust;

        drone.applyForce(force,dt);
        historyDrone.PushBack(drone.getPosition());
        historyTarget.PushBack(rocket.getPosition());
        //std::cout<<i<<" "<<force.x<<" "<<force.y<<std::endl;
        //std::cout<<drone.getVelocity().x<<" | "<<drone.getVelocity().y<<" | "<<rocket.getVelocity().x<<" | "<<rocket.getVelocity().y <<std::endl;
    }
}
void exportToTxt(const std::string& fileName,const Vector<Vector2D>& historyDrone , const Vector<Vector2D>& historyTarget) {

    std::ofstream file(fileName);
    if (file.is_open()) {
        file << "xd;yd;xt;yt\n";
        for (unsigned long long i = 0; i < historyDrone.Size(); i++) {
            file << historyDrone[i].x << ";" << historyDrone[i].y << ";" << historyTarget[i].x<< ";" << historyTarget[i].y <<"\n";
        }

        file.close();
        std::cout << "data save to trajectory.txt" << std::endl;
    } else {
        std::cerr << "file error" << std::endl;
    }

}

struct World {
   std::vector<std::shared_ptr<Drone>> drones;
    std::vector<std::shared_ptr<Target>> targets;
    std::mutex mtx;
    bool running=true;
};

void spawnTarget(World &world) {
    while (world.running) {
        {
            std::lock_guard<std::mutex> lock(world.mtx);
            std::shared_ptr<Target> target=std::make_shared<Target>(Vector2D(0,0),Vector2D(0,1000));
            world.targets.push_back(target);
        }

        std::cout<<"nowy dron"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}



int main() {
World world;
    std::thread t1(spawnTarget,std::ref(world));
    std::this_thread::sleep_for(std::chrono::seconds(5));
world.running=false;
    t1.join();
    std::cout << "Koniec programu Celow: " << world.targets.size() << std::endl;
    return 0;
}