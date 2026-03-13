#include <gtest/gtest.h>
#include "../src/include/PidController.h"
#include "../src/include/drone.h"
#include <cmath>

class PidControllerFixture : public ::testing::Test {
protected:
    PidController pid{0.0, 0.0, 1.5,100};
};

class DroneFixture : public ::testing::Test {
    protected:
    Drone drone{1,Vector2D(0.0,0.0)};
};

TEST_F(PidControllerFixture, DerivativeActionReactsToRateOfChange) {

    double dt = 1.0;
    EXPECT_DOUBLE_EQ(pid.calculatePid(2.0,0,dt), 3.0);

    EXPECT_DOUBLE_EQ(pid.calculatePid(4.0,0, dt), 3.0);

    EXPECT_DOUBLE_EQ(pid.calculatePid(3.0,0, dt), -1.5);

    EXPECT_DOUBLE_EQ(pid.calculatePid(3.0,0, dt), 0.0);
}

TEST(PidControllerTest, OutputIsSaturatedWithinLimits) {

    PidController pid(0, 2, 0.0, 100.0);
    double dt = 1;

    pid.calculatePid(50.0, 0.0, dt);

    pid.calculatePid(50.0, 0.0, dt);

    pid.calculatePid(50.0, 0.0, dt);

    EXPECT_DOUBLE_EQ(pid.calculatePid(0.0, 0.0, dt), 200.0);
}

TEST(PidControllerTest, HandlesZeroDeltaTimeSafely) {

    PidController pid(1.0, 1.0, 1.0, 100.0);

    double dt = 0.0;

    double result = pid.calculatePid(10.0, 0.0, dt);

    EXPECT_FALSE(std::isnan(result));
}

TEST_F(DroneFixture, DroneSimulation) {
    double force;
    double dt = 0.1;

    double previousError = std::abs(10 - drone.getPosition().x);
    PidController pid(1.0, 1.0, 1.0, 100.0);
    for (int i=1;i<10;i++) {
        force=pid.calculatePid(10,drone.getPosition().x,0.1);
        drone.applyForce(Vector2D(force,0),0.1);
        double currentError = std::abs(10 - drone.getPosition().x);
        EXPECT_LT(currentError,previousError);
    }

}
