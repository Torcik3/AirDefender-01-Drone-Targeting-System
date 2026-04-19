cmake_minimum_required(VERSION 4.1)
project(drone_pidcontroler)

set(CMAKE_CXX_STANDARD 20)

add_executable(drone_pidcontroler main.cpp
        src/drone.cpp
        src/PidController.cpp
        src/target.cpp
        src/Simulation.cpp
        src/Visualizer.cpp
)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(AirDefenderTests test/test_pid.cpp src/PidController.cpp src/drone.cpp
        src/include/Vector2D.h
        src/Simulation.cpp
        src/include/Simulation.h
        src/include/World.h
        src/exportToFile.cpp
        src/include/exportToFile.h
        src/Visualizer.cpp
        src/include/Visualizer.h
        src/include/MathUtils.h)

target_link_libraries(AirDefenderTests gtest_main)
target_link_libraries(drone_pidcontroler PRIVATE sfml-graphics sfml-window sfml-system)

include(GoogleTest)
gtest_discover_tests(AirDefenderTests)