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

        std::cout<<"nowy target"<<std::endl;
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