#include "hybrid.h"

Hybrid::Hybrid(Robo *robot):
    mRobot(robot),
    allSpace(3, Interval()),
    searchSpace(3, Interval()),
    logRealPosition("../resultados/logGPSPosition.csv"),
    logBoxes("../resultados/logHybridContractors.csv"),
    logParticles("../resultados/logHybridParticles.csv")
{
    /******************************************
     *                                        *
     *        Initialize the log files        *
     *                                        *
     ******************************************/
    //logBoxes << "#minx;maxx;miny;maxy;minz;maxz\n";
    //logParticles << "#melhor.pose.x;melhor.pose.y;melhor.pose.z;melhor.ypr.x;melhor.ypr.y;melhor.ypr.z;pior.pose.x;pior.pose.y;pior.pose.z;pior.ypr.x;pior.ypr.y;pior.ypr.z;media.pose.x;media.pose.y;media.pose.z;media.ypr.x;media.ypr.y;media.ypr.z;\n";

    allSpace[2] &= Interval::NEG_REALS;
    searchSpace[2] &= Interval::NEG_REALS;
}

Hybrid::~Hybrid()
{
    cout << "Deleting hybrid method" << endl;
    logBoxes.close();
    logParticles.close();
}


void Hybrid::findWhereIAm()
{
    this->createParticles();


    /**************************************************
     *                                                *
     *         Move the box and the particles         *
     *                                                *
     **************************************************/
    this->moveParticles();
    this->moveCaixa();

    /*************************************************
     *                                               *
     *    Reduce the box according to the readings   *
     *                                               *
     *************************************************/
    contractors.clear();

    this->contractByDepth();
    this->contractByDistance();
    this->contractByGPS();
    //this->contractByAngleOfPinger(); //Need to implement atan2 at IBEX.
    this->contractBySonarLocalization();

    //try
    //{
        //this->contractAllQIntersection();//with CtcQInter
        this->contractAll();
    //}catch(EmptyBoxException e)
    //{
    //    cout << "EMPTY BOX!!!" << endl;
    //    searchSpace = allSpace;
    //}


    /******************************************************************
     *                                                                *
     *  Improve the localization with particle filter inside the box  *
     *                                                                *
     ******************************************************************/
    this->discardParticlesOutsideBox();

    if (mRobot->getLandmarks().size() > 0)
    {
        this->weighParticles();
        this->resamplingParticles();
    }

    this->statistics();
    this->log();

    mRobot->setPose(avgParticle.pose);
}


void Hybrid::createParticles()
{
    if(this->population.size()==0 && !searchSpace.is_unbounded())
    {
        cout << "    Create particles" << endl;
        this->particleFilter.criarPopulacao(this->searchSpace, this->population, mRobot->getGyrocompass());
    }
}

void Hybrid::moveParticles()
{
    cout << "    Move particles" << endl;
    xyz velocity = mRobot->getLinearVelocity();
    xyz deltaHeading = mRobot->getDeltaHeading();

    for(int index=0;index<population.size();index++)
    {
        population[index].modeloMovimento2(velocity.x,velocity.y,velocity.z,
                                           deltaHeading.x ,deltaHeading.y,deltaHeading.z,mRobot->getElapsedTime());
    }
}

void Hybrid::moveCaixa()
{
    cout << "    Move boxes" << endl;
    double elapsedTime = mRobot->getElapsedTime();
    xyz linearVelocity = mRobot->getLinearVelocity();

    Interval velocityX = Interval (linearVelocity.x*elapsedTime-SIGMA_FACTOR_VEL*STD_VEL_DOPPLER,linearVelocity.x*elapsedTime+SIGMA_FACTOR_VEL*STD_VEL_DOPPLER);
    Interval velocityY = Interval (linearVelocity.y*elapsedTime-SIGMA_FACTOR_VEL*STD_VEL_DOPPLER,linearVelocity.y*elapsedTime+SIGMA_FACTOR_VEL*STD_VEL_DOPPLER);
    Interval velocityZ = Interval (linearVelocity.z*elapsedTime-SIGMA_FACTOR_VEL*STD_VEL_DOPPLER,linearVelocity.z*elapsedTime+SIGMA_FACTOR_VEL*STD_VEL_DOPPLER);

    xyz gyrocompass = mRobot->getGyrocompass();
    Interval phi  (gyrocompass.x-(SIGMA_FACTOR_ORI*STD_ORIENTATION),gyrocompass.x+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
    Interval theta(gyrocompass.y-(SIGMA_FACTOR_ORI*STD_ORIENTATION),gyrocompass.y+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
    Interval psi  (gyrocompass.z-(SIGMA_FACTOR_ORI*STD_ORIENTATION),gyrocompass.z+(SIGMA_FACTOR_ORI*STD_ORIENTATION));

    Interval J[6][6];
    J[0][0]= cos(psi)*cos(theta);
    J[0][1]=-sin(psi)*cos(phi)+cos(psi)*sin(theta)*sin(phi);
    J[0][2]= sin(psi)*sin(phi)+cos(psi)*sin(theta)*cos(phi);
    J[1][0]= sin(psi)*cos(theta);
    J[1][1]= cos(psi)*cos(theta)+sin(phi)*sin(theta)*sin(psi);
    J[1][2]=-cos(psi)*sin(phi)+sin(theta)*sin(psi)*cos(phi);
    J[2][0]=-sin(theta);
    J[2][1]= cos(theta)*sin(phi);
    J[2][2]= cos(theta)*cos(phi);

    searchSpace[0] += velocityX*J[0][0]+velocityY*J[0][1]+velocityZ*J[0][2];
    searchSpace[1] += velocityX*J[1][0]+velocityY*J[1][1]+velocityZ*J[1][2];
    searchSpace[2] += velocityX*J[2][0]+velocityY*J[2][1]+velocityZ*J[2][2];

    searchSpace &= allSpace;
}

void Hybrid::contractAllQIntersection()
{
    int NumberOfMeasurementsToBeDiscarded = (int)round(contractors.size()*0.1);//10%
    int NumberOfMeasurementsToBeUsed = contractors.size()-NumberOfMeasurementsToBeDiscarded;//number of correct measurement

    cout << "    Discarded measures = " << NumberOfMeasurementsToBeDiscarded << endl;
    CtcQInter qIntersection(contractors.size(),Array<Ctc>(contractors),NumberOfMeasurementsToBeUsed);
    CtcFixPoint fixPoint(qIntersection);
    fixPoint.contract(this->searchSpace);
    qIntersection.contract(this->searchSpace);
}

void Hybrid::contractAll()
{
    CtcCompo composition(contractors);
    CtcFixPoint fixPoint(composition);
    fixPoint.contract(this->searchSpace);
}

void Hybrid::contractByDistance()
{
    if (mRobot->isLandmarkTooOld())
    {
        cout << "Only old data about landmark information" << endl;
        return;
    }

    cout << "    Contract boxes by distance" << endl;
    QVector <Landmark> landmarks = mRobot->getLandmarks();
    int numberOfLandmarks = landmarks.size();

    if (numberOfLandmarks == 0)
        return ;

    Interval boundX[numberOfLandmarks];
    Interval boundY[numberOfLandmarks];
    Interval boundZ[numberOfLandmarks];
    Interval boundD[numberOfLandmarks];

    // TODO: Maybe consider the surface robot position as a box (not a point)
    for (int index=0; index<numberOfLandmarks; index++)
    {
        boundX[index]=Interval(landmarks[index].posicao.x);
        boundY[index]=Interval(landmarks[index].posicao.y);
        boundZ[index]=Interval(landmarks[index].posicao.z);
        boundD[index]=landmarks[index].dist;
    }

    Variable x(3);

    for(int contractorIndex=0; contractorIndex<numberOfLandmarks; contractorIndex++)
    {
        Function *constraintFunction = new Function(x,((sqrt(sqr(x[0]-boundX[contractorIndex])+sqr(x[1]-boundY[contractorIndex])+sqr(x[2]-boundZ[contractorIndex])) - boundD[contractorIndex])));
        contractors.push_back(new CtcFwdBwd(*constraintFunction));
    }
}

void Hybrid::contractByDepth()
{
    cout << "    Contract boxes by depth" << endl;
    Interval depthBox(mRobot->getDeep() - ERRO_DEEP,mRobot->getDeep() + ERRO_DEEP);

    Variable x(3);
    Function *constraintFunctionDepth = new Function(x,(x[2]-depthBox));

    contractors.push_back(new CtcFwdBwd(*constraintFunctionDepth));
}

void Hybrid::contractByGPS()
{
    cout << "    Contract boxes by GPS" << endl;

    if (mRobot->isGPSTooOld())
    {
        cout << "        Only old data about GPS information" << endl;
        return;
    }

    xyz gps = mRobot->getGPS();
    double bounds[3][2] = {
        {gps.x - ERRO_GPS, gps.x + ERRO_GPS},
        {gps.y - ERRO_GPS, gps.y + ERRO_GPS},
        {gps.z - ERRO_GPS, gps.z + ERRO_GPS}
    };

    Variable x(3);
    IntervalVector gpsBox(3,bounds);
    Function *constraintFunctionGPS = new Function(x,(x-gpsBox));
    contractors.push_back(new CtcFwdBwd(*constraintFunctionGPS));
}

void Hybrid::contractByAngleOfPinger()
{
    if (mRobot->isLandmarkTooOld())
        return;

    cout << "    Contract boxes by angle of the pinger" << endl;
    QVector <Landmark> landmarks = mRobot->getLandmarks();
    int numberOfLandmarks = landmarks.size();

    if (numberOfLandmarks == 0)
        return ;

    Interval boundX[numberOfLandmarks];
    Interval boundY[numberOfLandmarks];
    Interval boundZ[numberOfLandmarks];
    Interval boundA[numberOfLandmarks];

    for (int index=0; index<numberOfLandmarks; index++)
    {
        boundX[index]=Interval(landmarks[index].posicao.x);
        boundY[index]=Interval(landmarks[index].posicao.y);
        boundZ[index]=Interval(landmarks[index].posicao.z);
        boundA[index]=landmarks[index].angle.x;
    }

    Variable x(3);

    //Need to implement atan2 at IBEX.
    for(int contractorIndex=0; contractorIndex<numberOfLandmarks; contractorIndex++)
    {
        Function *constraintFunction = new Function(x,
                                                    (atan2(boundY[contractorIndex] - x[1],boundX[contractorIndex] - x[0]) - boundA[contractorIndex]));

        contractors.push_back(new CtcFwdBwd(*constraintFunction));
    }
}

void Hybrid::contractBySonarLocalization()
{
}

void Hybrid::discardParticlesOutsideBox()
{
    cout << "    Resampling particles: Discard" << endl;
    QVector <Particula> populationAux;
    std::swap(population,populationAux);

    for(int index=0;index<populationAux.size();index++)
    {
        double posicao[]= {
            populationAux[index].pose.x,
            populationAux[index].pose.y,
            populationAux[index].pose.z};

        xyz gyrocompass = mRobot->getGyrocompass();

        if (searchSpace.contains(Vector(3,posicao)))
        {
            population.push_back(populationAux[index]);
        }
        else
        {
            Particula newParticle;
            newParticle.pose.x = newParticle.fRand(searchSpace[0]);
            newParticle.pose.y = newParticle.fRand(searchSpace[1]);
            newParticle.pose.z = newParticle.fRand(searchSpace[2]);

            newParticle.yawPitchRoll.x = newParticle.fRandCentred(gyrocompass.x,SIGMA_FACTOR_ORI*STD_ORIENTATION);
            newParticle.yawPitchRoll.y = newParticle.fRandCentred(gyrocompass.y,SIGMA_FACTOR_ORI*STD_ORIENTATION);
            newParticle.yawPitchRoll.z = newParticle.fRandCentred(gyrocompass.z,SIGMA_FACTOR_ORI*STD_ORIENTATION);

            newParticle.id = index;
            population.push_back(newParticle);
        }
    }

    populationAux.clear();
}

void Hybrid::weighParticles()
{
    cout << "    Resampling particles: Weight" << endl;
    double normalizador = 0.;

    for(int index=0;index<population.size();index++)
    {
        normalizador += population[index].calcularPeso(mRobot->getLandmarks());
    }

    for(int index=0;index<population.size();index++)
    {
        population[index].peso /= normalizador;
    }
}

void Hybrid::resamplingParticles()
{
    cout << "    Resampling particles: Resampling" << endl;
    particleFilter.roleta(population);
}

void Hybrid::statistics()
{
    cout << "    Computing the statistics" << endl;
    worstParticle.peso=-1;bestParticle.peso=-1;

    double weightedAverageX, weightedAverageY, weightedAverageZ, weightedAverageHeadingX, weightedAverageHeadingY, weightedAverageHeadingZ, totalWeight;
    weightedAverageX = weightedAverageY = weightedAverageZ = weightedAverageHeadingX = weightedAverageHeadingY = weightedAverageHeadingZ = totalWeight = 0.;

    for(int index=0;index<population.size();index++)
    {
        if(population[index].peso < worstParticle.peso || worstParticle.peso==-1)
        {
            worstParticle=population[index];
        }

        if(population[index].peso > bestParticle.peso || bestParticle.peso==-1)
        {
            bestParticle=population[index];
        }

        weightedAverageX  += population[index].pose.x*population[index].peso;
        weightedAverageY  += population[index].pose.y*population[index].peso;
        weightedAverageZ  += population[index].pose.z*population[index].peso;

        weightedAverageHeadingX += population[index].yawPitchRoll.x*population[index].peso;
        weightedAverageHeadingY += population[index].yawPitchRoll.y*population[index].peso;
        weightedAverageHeadingZ += population[index].yawPitchRoll.z*population[index].peso;

        totalWeight += population[index].peso;
    }

    if(totalWeight == 0)
        totalWeight = 1; //Just to avoid the division by zero
    avgParticle.pose.x=weightedAverageX/totalWeight;
    avgParticle.pose.y=weightedAverageY/totalWeight;
    avgParticle.pose.z=weightedAverageZ/totalWeight;
    avgParticle.yawPitchRoll.x=weightedAverageHeadingX/totalWeight;
    avgParticle.yawPitchRoll.y=weightedAverageHeadingY/totalWeight;
    avgParticle.yawPitchRoll.z=weightedAverageHeadingZ/totalWeight;
}

void Hybrid::log()
{
    logParticles
            << Dados::stringalizar(bestParticle.pose.x) << ";"
            << Dados::stringalizar(bestParticle.pose.y) << ";"
            << Dados::stringalizar(bestParticle.pose.z) << ";"
            << Dados::stringalizar(bestParticle.yawPitchRoll.x) << ";"
            << Dados::stringalizar(bestParticle.yawPitchRoll.y) << ";"
            << Dados::stringalizar(bestParticle.yawPitchRoll.z) << ";"
            << Dados::stringalizar(worstParticle.pose.x) << ";"
            << Dados::stringalizar(worstParticle.pose.y) << ";"
            << Dados::stringalizar(worstParticle.pose.z) << ";"
            << Dados::stringalizar(worstParticle.yawPitchRoll.x) << ";"
            << Dados::stringalizar(worstParticle.yawPitchRoll.y) << ";"
            << Dados::stringalizar(worstParticle.yawPitchRoll.z) << ";"
            << Dados::stringalizar(avgParticle.pose.x) << ";"
            << Dados::stringalizar(avgParticle.pose.y) << ";"
            << Dados::stringalizar(avgParticle.pose.z) << ";"
            << Dados::stringalizar(avgParticle.yawPitchRoll.x) << ";"
            << Dados::stringalizar(avgParticle.yawPitchRoll.y) << ";"
            << Dados::stringalizar(avgParticle.yawPitchRoll.z) << ";"
            << "\n";

    logBoxes
            << Dados::stringalizar(searchSpace[0].lb()) << ";"
            << Dados::stringalizar(searchSpace[0].ub()) << ";"
            << Dados::stringalizar(searchSpace[1].lb()) << ";"
            << Dados::stringalizar(searchSpace[1].ub()) << ";"
            << Dados::stringalizar(searchSpace[2].lb()) << ";"
            << Dados::stringalizar(searchSpace[2].ub()) << ";"
            << "\n";

    xyz position = mRobot->getTruePose();
    QVector<Landmark> landmarks = mRobot->getLandmarks();
    logRealPosition
            << Dados::stringalizar(position.x) << ";"
            << Dados::stringalizar(position.y) << ";"
            << Dados::stringalizar(position.z) << ";"
            << Dados::stringalizar(landmarks[0].posicao.x) << ";"
            << Dados::stringalizar(landmarks[0].posicao.y) << ";"
            << Dados::stringalizar(landmarks[0].posicao.z) << ";"
            << "\n";

}
