

#ifndef DRONE_PIDCONTROLER_VECTOR2D_H
#define DRONE_PIDCONTROLER_VECTOR2D_H


class Vector2D {
public:
    double x,y;
public:
    Vector2D() : x(0), y(0) {};
    Vector2D(const double x,const double y) : x(x), y(y) {};
};


#endif //DRONE_PIDCONTROLER_VECTOR2D_H