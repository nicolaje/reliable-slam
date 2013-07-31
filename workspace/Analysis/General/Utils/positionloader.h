#ifndef POSITIONLOADER_H
#include <QString>
#include <vector>
#include <eigen3/Eigen/Eigen>
#include <ibex/ibex.h>
#define POSITIONLOADER_H

class PositionLoader
{
public:
    /**
     * @brief PositionLoader loads a .pos file containing the true landmarks positions.
     * @param data_file
     */
    PositionLoader(QString data_file);
    /**
     * @brief getLandmarksAsVector returns the vector of the true 3D vectors of the landmarks on the map.
     * @return
     */
    std::vector<Eigen::Vector3d> getLandmarksAsVector();
    /**
     * @brief getLandmarksAsIntervalVector returns the IntervalVector of the true 3D vectors of the landmarks on the map,
     * with a width/length/height passed as arguments.
     * @param errorX
     * @param errorY
     * @param errorZ
     * @return
     */
    std::vector<ibex::IntervalVector> getLandmarksAsIntervalVector(double errorX, double errorY, double errorZ);
    /**
     * @brief getLandmarksNB returns the number of landmarks.
     * @return the number of landmarks.
     */
    int getLandmarksNB();
private:
    std::vector<Eigen::Vector3d> landmarks;
};

#endif // POSITIONLOADER_H
