# AirDefender: Interceptor Drone Simulation System

AirDefender is a multi-threaded simulation engine written in C++20. In this project, interceptor drones track and destroy targets. They use custom PID controllers to fly accurately. I built the entire system from scratch. It features custom memory management, safe multi-threading, and automated tests.

## Key Features

**Multi-Threaded Architecture:** The project uses `std::thread` to run tasks in the background. The radar spawns targets, and the defense system sends drones. At the same time, the main physics engine runs at 60 FPS.

**Custom memery structure:** I replaced standard C++ containers with a custom `Vector` class. It uses "Swap and Pop" algorithm. 

**Thread-Safe Memory:** The simulation uses `std::mutex` and lock guards. They protect the data when multiple threads work at the same time. 

**Robust PID Logic:** The drones use custom Proportional, Integral, and Derivative math. It includes an Anti-Windup feature. This stops the drones from overshooting at high speeds.

**Fully Tested:** The code is secured with Google Test. The test suite checks PID limits, math errors (like `dt = 0`), and target tracking accuracy.

## Quick Start

```bash
mkdir build && cd build
cmake .. && cmake --build .
./drone_pidcontroler
