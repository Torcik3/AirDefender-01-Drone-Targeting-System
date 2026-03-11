cmake_minimum_required(VERSION 4.1)
project(drone_pidcontroler)

set(CMAKE_CXX_STANDARD 20)

add_executable(drone_pidcontroler main.cpp
        drone.cpp

        PidController.cpp

)


