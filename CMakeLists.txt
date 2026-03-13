cmake_minimum_required(VERSION 4.1)
project(drone_pidcontroler)

set(CMAKE_CXX_STANDARD 20)

add_executable(drone_pidcontroler main.cpp
        src/drone.cpp
        src/PidController.cpp
        src/target.cpp
        src/include/target.h
)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(AirDefenderTests test/test_pid.cpp src/PidController.cpp src/drone.cpp)

target_link_libraries(AirDefenderTests gtest_main)

include(GoogleTest)
gtest_discover_tests(AirDefenderTests)