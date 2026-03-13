
#pragma once

class PidController {
private:
    double Kp, Ki, Kd;
    double maxIntegral;
    double preError;
    double integralError;
public:
    PidController(double Kp, double Ki, double Kd, double maxIntegral): Kp(Kp), Ki(Ki), Kd(Kd), preError(0.0), integralError(0.0), maxIntegral(maxIntegral) {}
    double calculatePid(double setpoint, double currentValue, double dt );
    void reset();
};

