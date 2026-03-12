#include <iostream>
#include <fstream>
#include "PidController.h"
#include "vector/Vector.h"
#include "drone.h"
#include "target.h"

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
        force.y=pidy.calculatePid(target.y,temp.y, dt)+drone.getMass()*9.81;


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

int main() {

    Drone drone(90,Vector2D(0.0,0.0));
    PidController pidx(300.0, 0.5, 300.0, 5000.0);
    PidController pidy(300.0, 0.5, 300.0, 5000.0);
    Vector<Vector2D> historyDrone;
    Vector<Vector2D> historyTarget;
    Target rocket(Vector2D(15000,1000),Vector2D(-1000,0));

    runSim(drone,rocket,pidx,pidy,historyDrone,historyTarget);
    exportToTxt("trajectory.txt", historyDrone, historyTarget);

    return 0;
}