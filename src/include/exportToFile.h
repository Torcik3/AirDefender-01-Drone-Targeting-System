

#ifndef DRONE_PIDCONTROLER_EXPORTTOFILE_H
#define DRONE_PIDCONTROLER_EXPORTTOFILE_H
#include <iostream>
#include "Vector2D.h"
#include "../../vector/Vector.h"

class exportToFile {
    void exportToTxt(const std::string& fileName,const Vector<Vector2D>& historyDrone , const Vector<Vector2D>& historyTarget);
};


#endif //DRONE_PIDCONTROLER_EXPORTTOFILE_H