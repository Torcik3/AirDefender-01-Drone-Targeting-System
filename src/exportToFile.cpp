

#include <fstream>
#include "include/exportToFile.h"

void exportToTxt(const std::string& fileName,const Vector<Vector2D>& historyDrone , const Vector<Vector2D>& historyTarget) {

    std::ofstream file(fileName);
    if (file.is_open()) {
        file << "xd;yd;xt;yt\n";
        for (unsigned long long i = 0; i < historyDrone.Size(); i++) {
            file << historyDrone[i].x << ";" << historyDrone[i].y << ";" << historyTarget[i].x<< ";" << historyTarget[i].y <<"\n";
        }

        file.close();
        std::cout << "data save to trajectory.txt" << std::endl;
    } else {
        std::cerr << "file error" << std::endl;
    }

}