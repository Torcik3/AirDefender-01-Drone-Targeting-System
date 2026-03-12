#include "PidController.h"

double PidController::calculatePid(double setpoint, double currentValue, double dt ) {

    if (dt <= 0.0) return 0.0;

    double error = setpoint - currentValue;
    double p,i,d;

    integralError+= error * dt;

    if (integralError > maxIntegral) integralError = maxIntegral;
    if (integralError < -maxIntegral) integralError = -maxIntegral;

    p = error * Kp;
    d = (error-preError)*Kd/dt;
    i = Ki*integralError;
    preError=error;

    return p + i + d;
}


void PidController::reset() {
    preError = 0.0;
    integralError = 0.0;
}
