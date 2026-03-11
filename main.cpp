#include <iostream>
#include "PidController.h"
#include "vector/Vector.h"
#include "drone.h"
#include <fstream>
#include <iostream>

int main() {
Drone drone(1.0,Vector2D(0.0,0.0));
    PidController pidx(10,0.1,5,100);
    PidController pidy(10,0.1,5,100);

    Vector<Vector2D> history;
    Vector2D target(50.0,50.0);
    Vector2D temp;
    Vector2D force;
    double dt=0.01;
    for (int i=0; i<10000; i++) {

        temp=drone.getPosition();
        force.x=pidx.calculatePid(target.x,temp.x, dt);
        force.y=pidy.calculatePid(target.y,temp.y, dt);

    drone.applyForce(force,dt);
        history.PushBack(drone.getPosition());
    }

    std::ofstream file("trajectory.txt");

    if (file.is_open()) {
        file << "x,y\n";
        for (unsigned long long i = 0; i < history.Size(); i++) {
            file << history[i].x << "," << history[i].y << "\n";
        }

        file.close();
        std::cout << "data save to trajectory.csv" << std::endl;
    } else {
        std::cerr << "file error" << std::endl;
    }


    return 0;
}