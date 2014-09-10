#include "hibrido.h"

Hibrido::Hibrido(Robo *robot):
    mRobot(robot),
    ambienteInicial(3, Interval()), //definir a caixa que representa o ambiente inicial
    searchSpace(3, Interval()),
    logRealPosition("../resultados/logGPSPosition.csv"),
    logBoxes("../resultados/logHybridContractors.csv"),
    logParticles("../resultados/logHybridParticles.csv")
{
    //**************************************************
    //*        inicializa arquivos de log              *
    //**************************************************
    //logBoxes << "#minx;maxx;miny;maxy;minz;maxz\n";
    //logParticles << "#melhor.pose.x;melhor.pose.y;melhor.pose.z;melhor.ypr.x;melhor.ypr.y;melhor.ypr.z;pior.pose.x;pior.pose.y;pior.pose.z;pior.ypr.x;pior.ypr.y;pior.ypr.z;media.pose.x;media.pose.y;media.pose.z;media.ypr.x;media.ypr.y;media.ypr.z;\n";

    ambienteInicial[2] &= Interval::NEG_REALS;
    searchSpace[2] &= Interval::NEG_REALS;
}

Hibrido::~Hibrido()
{
    cout << "Deleting hybrid method" << endl;
    logBoxes.close();
    logParticles.close();
}


void Hibrido::executarLocalizacaoHibridaContratores()
{

    /*
    Criar a população
    Mover a população
    Mover a caixa
    Contrair a caixa pela distancia dos pingers
    Contrair a caixa pela profundidade
    Contrair a caixa pelo gps
    Contrair a caixa pela angulação dos pingers
    Contrair a caixa pelo sonar
    Descartar particulas fora da caixa
    Pesa e reamostra as particulas
    Reamostragem das particulas
    */

    cout << "    Create particles" << endl;
    this->createParticles();


    /**************************************************
     *                                                *
     *                 Mover população                *
     *                                                *
     **************************************************/
    //se tem velocidade e
    //se tem tempo entre as leituras
    //ou
    //se tem aceleração e aceleração acumulada
    //se tem tempo entre as leituras
    cout << "    Move particles" << endl;
    this->moveParticles();
    cout << "    Move boxes" << endl;
//    cout << "Antes: "
//         //<< searchSpace.lb() << searchSpace.ub()
//         << searchSpace.mid() << searchSpace.mid()
//         << mRobot->mGPS[mRobot->curTime].x << ", "
//         << mRobot->mGPS[mRobot->curTime].y << ", "
//         << mRobot->mGPS[mRobot->curTime].z << ", "
//         << endl;
    this->moveCaixa();
//    cout << "Depois: " << searchSpace.lb() << searchSpace.ub() << endl;

    /**************************************************
     *                                                *
     *    Posiciona landmarks e realiza contratores   *
     *                                                *
     **************************************************/
    //se tem markers

    cout << "    Contract boxes" << endl;
    this->contractByDistance();


    /**************************************************
     *                                                *
     *       Filtro de Particulas dentro da caixa     *
     *                                                *
     *************************************************/

    cout << "    Resampling particles: Discard" << endl;
    this->discardParticlesOutsideBox();

    if (mRobot->getLandmarks().size() > 0)
    {
        cout << "    Resampling particles: Weight" << endl;
        this->weighParticles();
        cout << "    Resampling particles: Resampling" << endl;
        this->resamplingParticles();
    }

    cout << "    Computing the statistics" << endl;
    this->statistics();
    this->log();
}


void Hibrido::createParticles()
{
    //**************************************************
    //* criar população de partículas no searchspace   *
    //**************************************************
    //se tem ambiente inicial < inf e
    //se tem yawPitchRoll
    IntervalVector *complementary = NULL;
    this->searchSpace.complementary(complementary);

    if(this->population.size()==0 && !complementary->is_empty())
    {
        cout << "Cria população" <<endl;
        this->particleFilter.criarPopulacao(this->searchSpace, this->population, mRobot->getGyrocompass());
    }
}

void Hibrido::moveParticles()
{
    xyz velocity = mRobot->getLinearVelocity();
    xyz deltaHeading = mRobot->getDeltaHeading();

    for(int index=0;index<population.size();index++)
    {
        population[index].modeloMovimento2(velocity.x,velocity.y,velocity.z,
                                      deltaHeading.x ,deltaHeading.y,deltaHeading.z,mRobot->getElapsedTime());
    }
}

void Hibrido::moveCaixa()
{
    double elapsedTime = mRobot->getElapsedTime();
    xyz linearVelocity = mRobot->getLinearVelocity();

    Interval velocityX = Interval (linearVelocity.x*elapsedTime-ERRO_VELOCITY,linearVelocity.x*elapsedTime+ERRO_VELOCITY);
    Interval velocityY = Interval (linearVelocity.y*elapsedTime-ERRO_VELOCITY,linearVelocity.y*elapsedTime+ERRO_VELOCITY);
    Interval velocityZ = Interval (linearVelocity.z*elapsedTime-ERRO_VELOCITY,linearVelocity.z*elapsedTime+ERRO_VELOCITY);

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

    searchSpace[0]=searchSpace[0]+velocityX*J[0][0]+velocityY*J[0][1]+velocityZ*J[0][2];
    searchSpace[1]=searchSpace[1]+velocityX*J[1][0]+velocityY*J[1][1]+velocityZ*J[1][2];
    searchSpace[2]=searchSpace[2]+velocityX*J[2][0]+velocityY*J[2][1]+velocityZ*J[2][2];

    searchSpace = searchSpace & ambienteInicial;
}


void Hibrido::contractByDistance()
{
    QVector <Landmark> landmarks = mRobot->getLandmarks();
    int N = landmarks.size();

    if (N == 0)
        return;

    Interval boxX[N];
    Interval boxY[N];
    Interval boxZ[N];
    Interval boxD[N];

    for (int index=0; index<N; index++)
    {
        boxX[index]=Interval(landmarks[index].posicao.x);
        boxY[index]=Interval(landmarks[index].posicao.y);
        boxZ[index]=Interval(landmarks[index].posicao.z);
        boxD[index]=landmarks[index].dist;
    }

    Array<Ctc> contractors(N);
    Variable x(3);

    for(int contractorIndex=0;contractorIndex<N;contractorIndex++)
    {
        Function *constraintFunction = new Function(x,((sqrt(sqr(x[0]-boxX[contractorIndex])+sqr(x[1]-boxY[contractorIndex])+sqr(x[2]-boxZ[contractorIndex])) - boxD[contractorIndex])));
        CtcFwdBwd *ar=new CtcFwdBwd(*constraintFunction);
        contractors.set_ref(contractorIndex,*ar);
    }

    CtcCompo composition(contractors);
    CtcFixPoint fixPoint(composition);// O FIX POINT FICA CONTRAINDO ATÉ NÃO MUDAR MAIS SERIA COMO FAZER UM MONTE DE "comp.contract(array);"
    fixPoint.contract(this->searchSpace);
}

void Hibrido::discardParticlesOutsideBox()
{
    QVector <Particula> populationAux;
    std::swap(population,populationAux);

    for(int index=0;index<populationAux.size();index++)
    {
        double posicao[]= {
                populationAux[index].pose.x,
                populationAux[index].pose.y,
                populationAux[index].pose.z};

        xyz gyrocompass = mRobot->getGyrocompass();

        //testa se as partículas da população estão dentro do searchSpace, eliminar as que estão fora e repoe com uma aleatoria
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

void Hibrido::weighParticles()
{
    double normalizador = 0.;

    for(int index=0;index<population.size();index++)
    {
        normalizador += population[index].calcularPeso(mRobot->getLandmarks());
        //cout << normalizador << " " << population[index].peso<< endl;
    }

    for(int index=0;index<population.size();index++)
    {
        population[index].peso /= normalizador;
        //cout << normalizador << " " << population[index].peso<< endl;
    }
}

void Hibrido::resamplingParticles()
{
    particleFilter.roleta(population);
}

void Hibrido::statistics()
{
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

    avgParticle.pose.x=weightedAverageX/totalWeight;
    avgParticle.pose.y=weightedAverageY/totalWeight;
    avgParticle.pose.z=weightedAverageZ/totalWeight;
    avgParticle.yawPitchRoll.x=weightedAverageHeadingX/totalWeight;
    avgParticle.yawPitchRoll.y=weightedAverageHeadingY/totalWeight;
    avgParticle.yawPitchRoll.z=weightedAverageHeadingZ/totalWeight;
}

void Hibrido::log()
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

    QVector<double> position = mRobot->getGPS();
    logRealPosition
            << Dados::stringalizar(position[0]) << ";"
            << Dados::stringalizar(position[1]) << ";"
            << Dados::stringalizar(position[2]) << ";"
            << "\n";

}
