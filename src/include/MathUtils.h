
#ifndef DRONE_PIDCONTROLER_MATHUTILS_H
#define DRONE_PIDCONTROLER_MATHUTILS_H
#include <cmath>
#include "Vector2D.h"
namespace MathUtils {

    inline Vector2D pointsOnCircle(const Vector2D &center, const double &radius, const double &angle) {
     Vector2D result(0,0);
        result.x = center.x+radius*std::sin(angle);
        result.y = center.y+radius*std::cos(angle);

        return result;
    }

    inline Vector2D calVelToPoint(const Vector2D &spawn,const Vector2D &target,const double &velo) {
        Vector2D result(0,0);
        Vector2D vecVelo(target.x-spawn.x,target.y-spawn.y);
      double length= std::sqrt(vecVelo.x*vecVelo.x+vecVelo.y*vecVelo.y);
        if (length>0) {
             result.x = vecVelo.x/length*velo;
            result.y = vecVelo.y/length*velo;
            }
        else {
            result.x=0;
            result.y=0;
            }
        return result;
    }

}



#endif