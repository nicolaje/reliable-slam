#ifndef MORSEDATAPARSER_H
#define MORSEDATAPARSER_H
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include "robot.h"

/**
 * @brief The MORSEDataParser class parses a .csv generated after a MORSE simulation
 *via my logging tool. It is not intended to be a clean csv parser, it is just suited
 *for my specific needs, as I know exactly where/how to find data in my files.
 */
class MORSEDataParser
{
public:
    MORSEDataParser(QString data_file, int nbRobots, int nbLandmarks);
    vector<Robot> nextRecord();
    bool hasDataLeft();
private:
    QFile* file;
    int nbRobots;
    int nbLandmarks;
};

#endif // MORSEDATAPARSER_H
