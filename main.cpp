#include "src/include/Simulation.h"
#include "src/include/Visualizer.h"

int main() {

    Simulation sim;
    sim.start();
    std::thread physicsLoop(&Simulation::run, &sim);
    Visualizer vis;
    vis.run(sim.getWorld());
    sim.stop();

    if (physicsLoop.joinable()) {
        physicsLoop.join();
    }
    return 0;
}
