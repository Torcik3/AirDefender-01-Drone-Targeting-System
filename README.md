# AirDefender: Interceptor Drone PID Controller

A high-performance **C++20** PID controller specifically designed for interceptor drones to track and hit fast-moving incoming targets. Built from scratch with a custom dynamic memory engine and validated through automated testing.

## Key Features
* **Target Interception:** Tuned for aggressive yet stable convergence to intercept moving coordinates with zero steady-state error.
* **Custom Memory Engine** Replaced standard containers with a manual, dynamically allocated array engine.
* **Robust PID Logic:** Independent P, I, D components featuring **Integral Anti-Windup** to prevent overshoot during high-speed maneuvers.
* **Fully Tested:** Google Test cases covering edge cases, target tracking convergence.

## Quick Start
```bash
mkdir build && cd build
cmake .. && cmake --build .
./AirDefenderTests
```
