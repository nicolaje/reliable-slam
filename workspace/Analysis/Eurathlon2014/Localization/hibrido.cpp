#include "hibrido.h"

Hibrido::Hibrido()
{
}

void Hibrido::executarLocalizacaoHibridaContratores(IntervalVector searchSpace, IntervalVector ambienteInicial, QVector<xyz> poseXYZ, QVector<xyz> yawPitchRoll, QVector<xyz> velXYZ, QVector<QVector<transponder> > transponders, QVector<Landmark> landmarksUsados, int idExec){

    clock_t inicio=clock();
    std::stringstream sstr;
    sstr << idExec;
    string nome = PATH_RESULTS + sstr.str() + string("hibridoContratores.csv");
    ofstream logCaixas(nome.c_str());
    nome = PATH_RESULTS + sstr.str() + string("hibridoContratoresFP.csv");
    ofstream logParticulas(nome.c_str());


    Dados d;
    Sivia s;
    QVector<Particula> populacao;
    int movAnterior=0;
    double normalizador=0;
    FiltroParticulas fp;
    int reinicializaFP=0;


    logCaixas<<"#minx;maxx;miny;maxy;minz;maxz\n";
    logParticulas<<"#melhor.pose.x;melhor.pose.y;melhor.pose.z;melhor.ypr.x;melhor.ypr.y;melhor.ypr.z;pior.pose.x;pior.pose.y;pior.pose.z;pior.ypr.x;pior.ypr.y;pior.ypr.z;media.pose.x;media.pose.y;media.pose.z;media.ypr.x;media.ypr.y;media.ypr.z;\n";


    for(int j=0;j<poseXYZ.size();j=j+LEITURAS_POR_TEMPO_LEITURAS){
        if(j%100==0)qDebug()<<"Etapa"<<j<<"/"<<poseXYZ.size();

        //        cout<<j<<endl;
        //        Imagem im;
        //        im.carregarImagem("../mapas/mapa1000x1000.bmp");
        //        im.inicializarPaiter();
        //        im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::blue,Qt::NoBrush);

        //fp*************************************************************************
        normalizador=0;

        //ai*************************************************************************
        const int N=NRO_TRANSPONDERS;
        Interval bX[N];
        Interval bY[N];
        Interval bZ[N];
        Interval bD[N];
        for (int i=0; i<N; i++) {
            bX[i]=Interval(landmarksUsados[i].posicao.x);
            bY[i]=Interval(landmarksUsados[i].posicao.y);
            bZ[i]=Interval(landmarksUsados[i].posicao.z);
            bD[i]=Interval(transponders[j][i].distNoise-(STD_DIST_TRANSP*SIGMA_FACTOR_TRA),transponders[j][i].distNoise+(STD_DIST_TRANSP*SIGMA_FACTOR_TRA));
        }
        Array<Ctc> array(N);
        Variable x(3);
        for(int c=0;c<N;c++){
            Function *fun2 =new Function(x,((sqrt(sqr(x[0]-bX[c])+sqr(x[1]-bY[c])+sqr(x[2]-bZ[c]))-bD[c])));
            CtcFwdBwd *ar=new CtcFwdBwd(*fun2);
            array.set_ref(c,*ar);
        }
        CtcCompo comp(array);
        CtcFixPoint fix(comp);// O FIX POINT FICA CONTRAINDO ATÉ NÃO MUDAR MAIS SERIA COMO FAZER UM MONTE DE "comp.contract(array);"
        fix.contract(searchSpace);

        double _x[3][2]={{poseXYZ[j].x,poseXYZ[j].x},{poseXYZ[j].y, poseXYZ[j].y},{poseXYZ[j].z,poseXYZ[j].z}};
        IntervalVector p(3,_x);
        if(!p.is_subset(searchSpace)) {qDebug()<<"Robo fora da caixa!!!!!!!!";}

        logCaixas<<d.stringalizar(searchSpace[0].lb())+";"+d.stringalizar(searchSpace[0].ub())+";"+d.stringalizar(searchSpace[1].lb())+";"+d.stringalizar(searchSpace[1].ub())+";"+d.stringalizar(searchSpace[2].lb())+";"+d.stringalizar(searchSpace[2].ub())+";\n";


        //        im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::red,Qt::NoBrush);

        //fp*************************************************************************
        //se for 1a iteração criar partículas dentro do searchSpace
        if(j==0){
            for(int k=0;k<TAMANHO_POPULACAO;k++){
                Particula p;
                p.pose.x=p.fRand(searchSpace[0].lb(),searchSpace[0].ub());
                p.pose.y=p.fRand(searchSpace[1].lb(),searchSpace[1].ub());
                p.pose.z=p.fRand(searchSpace[2].lb(),searchSpace[2].ub());
                p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                p.id=k;
                populacao.push_back(p);
                normalizador += populacao[populacao.size()-1].calcularPeso(transponders[j],landmarksUsados/*,limXmin,limXmax,limYmin,limYmax,limZmin,limZmax*/);
            }
        }

        //se não é a primeira iteração, então move as particulas da populacao existente
        if(j!=0){
            QVector <Particula> populacaoAux;
            std::swap(populacao,populacaoAux);
            populacao.clear();
            for(int k=0;k<populacaoAux.size();k++){
                populacaoAux[k].modeloMovimento2(velXYZ[j].xNoise,velXYZ[j].yNoise,velXYZ[j].zNoise,yawPitchRoll[j].xNoise,yawPitchRoll[j].yNoise,yawPitchRoll[j].zNoise, (yawPitchRoll[j].xNoise-yawPitchRoll[movAnterior].xNoise) ,(yawPitchRoll[j].yNoise-yawPitchRoll[movAnterior].yNoise),(yawPitchRoll[j].zNoise-yawPitchRoll[movAnterior].zNoise));

                //testa se as partículas da população estão dentro do searchSpace, eliminar as que estão fora e repoe com uma aleatoria
                if(searchSpace[0].contains(populacaoAux[k].pose.x) && searchSpace[1].contains(populacaoAux[k].pose.y) && searchSpace[2].contains(populacaoAux[k].pose.z)){
                    populacao.push_back(populacaoAux[k]);
                }
                else{
                    Particula p;
                    p.pose.x=p.fRand(searchSpace[0].lb(),searchSpace[0].ub());
                    p.pose.y=p.fRand(searchSpace[1].lb(),searchSpace[1].ub());
                    p.pose.z=p.fRand(searchSpace[2].lb(),searchSpace[2].ub());
                    p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.id=k;
                    populacao.push_back(p);
                }
                if(populacao.size()<1)qDebug()<<"VAI DA PAU"<<populacao.size();
                normalizador += populacao[populacao.size()-1].calcularPeso(transponders[j],landmarksUsados/*,limXmin,limXmax,limYmin,limYmax,limZmin,limZmax*/);
            }
            movAnterior=j;
            populacaoAux.clear();

            if(populacao.size()<1){
                qDebug()<<"Reinicializar população";
                normalizador=0;
                for(int k=0;k<TAMANHO_POPULACAO;k++){
                    Particula p;
                    p.pose.x=p.fRand(searchSpace[0].lb(),searchSpace[0].ub());
                    p.pose.y=p.fRand(searchSpace[1].lb(),searchSpace[1].ub());
                    p.pose.z=p.fRand(searchSpace[2].lb(),searchSpace[2].ub());
                    p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.id=k;
                    populacao.push_back(p);
                    normalizador += populacao[populacao.size()-1].calcularPeso(transponders[j],landmarksUsados/*,limXmin,limXmax,limYmin,limYmax,limZmin,limZmax*/);
                }
                reinicializaFP++;
            }
        }

        //executa roleta na população
        for(int k=0;k<populacao.size();k++){
            populacao[k].peso=populacao[k].peso/normalizador;
        }
        fp.roleta(populacao);


        //ai*************************************************************************
        //move searchSpace
        Interval vx((velXYZ[j].xNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].xNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vy((velXYZ[j].yNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].yNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vz((velXYZ[j].zNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].zNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval phi  (yawPitchRoll[j].xNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].xNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval theta(yawPitchRoll[j].yNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].yNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval psi  (yawPitchRoll[j].zNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].zNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        s.moveCaixa( searchSpace,ambienteInicial,  vx,  vy,  vz,  phi,  theta,  psi);

        //fp*************************************************************************
        Particula piorParticula, melhorParticula, mp;
        piorParticula.peso=-1;melhorParticula.peso=-1;
        double mpx=0, mpy=0, mpz=0, a1=0, a2=0, a3=0, angx=0, angy=0, angz=0, a4=0, a5=0, a6=0;
        for(int k=0;k<populacao.size();k++){
            if(populacao[k].peso<piorParticula.peso || piorParticula.peso==-1){
                piorParticula=populacao[k];
            }
            if(populacao[k].peso>melhorParticula.peso || melhorParticula.peso==-1){
                melhorParticula=populacao[k];
            }
            mpx=mpx+populacao[k].pose.x*populacao[k].peso;
            a1=a1+populacao[k].peso;
            mpy=mpy+populacao[k].pose.y*populacao[k].peso;
            a2=a2+populacao[k].peso;
            mpz=mpz+populacao[k].pose.z*populacao[k].peso;
            a3=a3+populacao[k].peso;
            angx=angx+populacao[k].yawPitchRoll.x*populacao[k].peso;
            a4=a4+populacao[k].peso;
            angy=angy+populacao[k].yawPitchRoll.y*populacao[k].peso;
            a5=a5+populacao[k].peso;
            angz=angz+populacao[k].yawPitchRoll.z*populacao[k].peso;
            a6=a6+populacao[k].peso;
        }
        mp.pose.x=mpx/a1;
        mp.pose.y=mpy/a2;
        mp.pose.z=mpz/a3;
        mp.yawPitchRoll.x=angx/a4;
        mp.yawPitchRoll.y=angy/a5;
        mp.yawPitchRoll.z=angz/a6;

        logParticulas<<d.stringalizar(melhorParticula.pose.x)+";"+d.stringalizar(melhorParticula.pose.y)+";"+d.stringalizar(melhorParticula.pose.z)+";"+d.stringalizar(melhorParticula.yawPitchRoll.x)+";"+d.stringalizar(melhorParticula.yawPitchRoll.y)+";"+d.stringalizar(melhorParticula.yawPitchRoll.z)+";"+d.stringalizar(piorParticula.pose.x)+";"+d.stringalizar(piorParticula.pose.y)+";"+d.stringalizar(piorParticula.pose.z)+";"+d.stringalizar(piorParticula.yawPitchRoll.x)+";"+d.stringalizar(piorParticula.yawPitchRoll.y)+";"+d.stringalizar(piorParticula.yawPitchRoll.z)+";"+d.stringalizar(mp.pose.x)+";"+d.stringalizar(mp.pose.y)+";"+d.stringalizar(mp.pose.z)+";"+d.stringalizar(mp.yawPitchRoll.x)+";"+d.stringalizar(mp.yawPitchRoll.y)+";"+d.stringalizar(mp.yawPitchRoll.z)+";"+"\n";


        //        PaletaCores paletaCor;
        //        double v1 = piorParticula.peso;
        //        double v3 = melhorParticula.peso;
        //        if(v1==v3){
        //            v1=v1-1;
        //            v3=v3-1;
        //        }
        //        for(int k=0;k<populacao.size();k++){
        //            double v2 = populacao[k].peso;
        //            paletaCor.updatePorcentagem((v2-v1)/(v3-v1));
        //            im.desenhaElipse2(populacao[k].pose.x,populacao[k].pose.y,0.2,0.2,QColor(paletaCor.cor->red(),paletaCor.cor->green(),paletaCor.cor->blue()),Qt::NoBrush);
        //            //cout<<searchSpace<<" "<<populacao[k].pose.x<<" "<<populacao[k].pose.y<<" "<<populacao[k].pose.z<<endl;
        //        }
        //        im.desenhaElipse2(poseXYZ[j].x,poseXYZ[j].y,0.5,0.5,Qt::black,Qt::black);
        //        im.finalizarPainter();
        //        im.salvarImagem("../mapasResult/"+QString::number(j)+".bmp");

        //cout<<endl;
    }
    logParticulas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio))+"\n";
    logParticulas<<"#Inicializacoes do filtro "+d.stringalizar(reinicializaFP);
    logParticulas<<"\n#Fim";
    logCaixas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio));
    logCaixas<<"\n#Fim";
    logParticulas.close();
    logCaixas.close();

}

void Hibrido::executarLocalizacaoHibridaContratores(IntervalVector searchSpace, IntervalVector ambienteInicial, QVector<xyz> poseXYZ, QVector<xyz> yawPitchRoll, QVector<xyz> velXYZ, QVector< QVector<Landmark> > landmarksUsados, int idExec){

    clock_t inicio=clock();
    std::stringstream sstr;
    sstr << idExec;
    string nome = PATH_RESULTS + sstr.str() + string("hibridoContratores.csv");
    ofstream logCaixas(nome.c_str());
    nome = PATH_RESULTS + sstr.str() + string("hibridoContratoresFP.csv");
    ofstream logParticulas(nome.c_str());


    Dados d;
    Sivia s;
    QVector<Particula> populacao;
    int movAnterior=0;
    double normalizador=0;
    FiltroParticulas fp;
    int reinicializaFP=0;


    logCaixas<<"#minx;maxx;miny;maxy;minz;maxz\n";
    logParticulas<<"#melhor.pose.x;melhor.pose.y;melhor.pose.z;melhor.ypr.x;melhor.ypr.y;melhor.ypr.z;pior.pose.x;pior.pose.y;pior.pose.z;pior.ypr.x;pior.ypr.y;pior.ypr.z;media.pose.x;media.pose.y;media.pose.z;media.ypr.x;media.ypr.y;media.ypr.z;\n";


    for(int j=0;j<poseXYZ.size();j=j+LEITURAS_POR_TEMPO_LEITURAS){
        if(j%100==0)qDebug()<<"Etapa"<<j<<"/"<<poseXYZ.size();

        //        cout<<j<<endl;
        //        Imagem im;
        //        im.carregarImagem("../mapas/mapa1000x1000.bmp");
        //        im.inicializarPaiter();
        //        im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::blue,Qt::NoBrush);

        //fp*************************************************************************
        normalizador=0;

        //ai*************************************************************************

        /*************************************************
        *                                                *
        *    Posiciona landmarks e realiza contratores   *
        *                                                *
        *************************************************/
        const int N=NRO_TRANSPONDERS;
        Interval bX[N];
        Interval bY[N];
        Interval bZ[N];
        Interval bD[N];
        for (int i=0; i<N; i++) {
            bX[i]=Interval(landmarksUsados[j][i].posicao.x);
            bY[i]=Interval(landmarksUsados[j][i].posicao.y);
            bZ[i]=Interval(landmarksUsados[j][i].posicao.z);
            bD[i]=landmarksUsados[j][i].dist;
        }
        Array<Ctc> array(N);
        Variable x(3);
        for(int c=0;c<N;c++){
            Function *fun2 =new Function(x,((sqrt(sqr(x[0]-bX[c])+sqr(x[1]-bY[c])+sqr(x[2]-bZ[c])) - bD[c])));
            CtcFwdBwd *ar=new CtcFwdBwd(*fun2);
            array.set_ref(c,*ar);
        }
        CtcCompo comp(array);
        CtcFixPoint fix(comp);// O FIX POINT FICA CONTRAINDO ATÉ NÃO MUDAR MAIS SERIA COMO FAZER UM MONTE DE "comp.contract(array);"
        fix.contract(searchSpace);

        double _x[3][2]={{poseXYZ[j].x,poseXYZ[j].x},{poseXYZ[j].y, poseXYZ[j].y},{poseXYZ[j].z,poseXYZ[j].z}};
        IntervalVector p(3,_x);

        if(!p.is_subset(searchSpace))
            qDebug()<<"Robo fora da caixa!!!!!!!!";

        logCaixas << d.stringalizar(searchSpace[0].lb())+";"+d.stringalizar(searchSpace[0].ub())+";"+d.stringalizar(searchSpace[1].lb())+";"+d.stringalizar(searchSpace[1].ub())+";"+d.stringalizar(searchSpace[2].lb())+";"+d.stringalizar(searchSpace[2].ub())+";\n";

        /*************************************************
        *                                                *
        *       Filtro de Particulas dentro da caixa     *
        *                                                *
        *************************************************/


        //        im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::red,Qt::NoBrush);

        //fp*************************************************************************
        //se for 1a iteração criar partículas dentro do searchSpace
        if(j==0){
            for(int k=0;k<TAMANHO_POPULACAO;k++){
                Particula p;
                p.pose.x=p.fRand(searchSpace[0].lb(),searchSpace[0].ub());
                p.pose.y=p.fRand(searchSpace[1].lb(),searchSpace[1].ub());
                p.pose.z=p.fRand(searchSpace[2].lb(),searchSpace[2].ub());
                p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                p.id=k;
                populacao.push_back(p);
                normalizador += populacao[populacao.size()-1].calcularPeso(landmarksUsados[j]/*,limXmin,limXmax,limYmin,limYmax,limZmin,limZmax*/);
            }
        }

        //se não é a primeira iteração, então move as particulas da populacao existente
        if(j!=0){
            QVector <Particula> populacaoAux;
            std::swap(populacao,populacaoAux);
            populacao.clear();
            for(int k=0;k<populacaoAux.size();k++){
                populacaoAux[k].modeloMovimento2(velXYZ[j].xNoise,velXYZ[j].yNoise,velXYZ[j].zNoise,yawPitchRoll[j].xNoise,yawPitchRoll[j].yNoise,yawPitchRoll[j].zNoise, (yawPitchRoll[j].xNoise-yawPitchRoll[movAnterior].xNoise) ,(yawPitchRoll[j].yNoise-yawPitchRoll[movAnterior].yNoise),(yawPitchRoll[j].zNoise-yawPitchRoll[movAnterior].zNoise));

                //testa se as partículas da população estão dentro do searchSpace, eliminar as que estão fora e repoe com uma aleatoria
                if(searchSpace[0].contains(populacaoAux[k].pose.x) && searchSpace[1].contains(populacaoAux[k].pose.y) && searchSpace[2].contains(populacaoAux[k].pose.z)){
                    populacao.push_back(populacaoAux[k]);
                }
                else{
                    Particula p;
                    p.pose.x=p.fRand(searchSpace[0].lb(),searchSpace[0].ub());
                    p.pose.y=p.fRand(searchSpace[1].lb(),searchSpace[1].ub());
                    p.pose.z=p.fRand(searchSpace[2].lb(),searchSpace[2].ub());
                    p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.id=k;
                    populacao.push_back(p);
                }
                if(populacao.size()<1)
                    qDebug()<<"VAI DA PAU"<<populacao.size();
                normalizador += populacao[populacao.size()-1].calcularPeso(landmarksUsados[j]/*,limXmin,limXmax,limYmin,limYmax,limZmin,limZmax*/);
            }
            movAnterior=j;
            populacaoAux.clear();

            if(populacao.size()<1){
                qDebug()<<"Reinicializar população";
                normalizador=0;
                for(int k=0;k<TAMANHO_POPULACAO;k++){
                    Particula p;
                    p.pose.x=p.fRand(searchSpace[0].lb(),searchSpace[0].ub());
                    p.pose.y=p.fRand(searchSpace[1].lb(),searchSpace[1].ub());
                    p.pose.z=p.fRand(searchSpace[2].lb(),searchSpace[2].ub());
                    p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.id=k;
                    populacao.push_back(p);
                    normalizador += populacao[populacao.size()-1].calcularPeso(landmarksUsados[j]/*,limXmin,limXmax,limYmin,limYmax,limZmin,limZmax*/);
                }
                reinicializaFP++;
            }
        }

        //executa roleta na população
        for(int k=0;k<populacao.size();k++){
            populacao[k].peso=populacao[k].peso/normalizador;
        }
        fp.roleta(populacao);


        //ai*************************************************************************
        //move searchSpace
        Interval vx((velXYZ[j].xNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].xNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vy((velXYZ[j].yNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].yNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vz((velXYZ[j].zNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].zNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval phi  (yawPitchRoll[j].xNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].xNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval theta(yawPitchRoll[j].yNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].yNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval psi  (yawPitchRoll[j].zNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].zNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        s.moveCaixa( searchSpace,ambienteInicial,  vx,  vy,  vz,  phi,  theta,  psi);

        //fp*************************************************************************
        Particula piorParticula, melhorParticula, mp;
        piorParticula.peso=-1;melhorParticula.peso=-1;
        double mpx=0, mpy=0, mpz=0, a1=0, a2=0, a3=0, angx=0, angy=0, angz=0, a4=0, a5=0, a6=0;
        for(int k=0;k<populacao.size();k++){
            if(populacao[k].peso<piorParticula.peso || piorParticula.peso==-1){
                piorParticula=populacao[k];
            }
            if(populacao[k].peso>melhorParticula.peso || melhorParticula.peso==-1){
                melhorParticula=populacao[k];
            }
            mpx=mpx+populacao[k].pose.x*populacao[k].peso;
            a1=a1+populacao[k].peso;
            mpy=mpy+populacao[k].pose.y*populacao[k].peso;
            a2=a2+populacao[k].peso;
            mpz=mpz+populacao[k].pose.z*populacao[k].peso;
            a3=a3+populacao[k].peso;
            angx=angx+populacao[k].yawPitchRoll.x*populacao[k].peso;
            a4=a4+populacao[k].peso;
            angy=angy+populacao[k].yawPitchRoll.y*populacao[k].peso;
            a5=a5+populacao[k].peso;
            angz=angz+populacao[k].yawPitchRoll.z*populacao[k].peso;
            a6=a6+populacao[k].peso;
        }
        mp.pose.x=mpx/a1;
        mp.pose.y=mpy/a2;
        mp.pose.z=mpz/a3;
        mp.yawPitchRoll.x=angx/a4;
        mp.yawPitchRoll.y=angy/a5;
        mp.yawPitchRoll.z=angz/a6;

        logParticulas<<d.stringalizar(melhorParticula.pose.x)+";"+d.stringalizar(melhorParticula.pose.y)+";"+d.stringalizar(melhorParticula.pose.z)+";"+d.stringalizar(melhorParticula.yawPitchRoll.x)+";"+d.stringalizar(melhorParticula.yawPitchRoll.y)+";"+d.stringalizar(melhorParticula.yawPitchRoll.z)+";"+d.stringalizar(piorParticula.pose.x)+";"+d.stringalizar(piorParticula.pose.y)+";"+d.stringalizar(piorParticula.pose.z)+";"+d.stringalizar(piorParticula.yawPitchRoll.x)+";"+d.stringalizar(piorParticula.yawPitchRoll.y)+";"+d.stringalizar(piorParticula.yawPitchRoll.z)+";"+d.stringalizar(mp.pose.x)+";"+d.stringalizar(mp.pose.y)+";"+d.stringalizar(mp.pose.z)+";"+d.stringalizar(mp.yawPitchRoll.x)+";"+d.stringalizar(mp.yawPitchRoll.y)+";"+d.stringalizar(mp.yawPitchRoll.z)+";"+"\n";


        //        PaletaCores paletaCor;
        //        double v1 = piorParticula.peso;
        //        double v3 = melhorParticula.peso;
        //        if(v1==v3){
        //            v1=v1-1;
        //            v3=v3-1;
        //        }
        //        for(int k=0;k<populacao.size();k++){
        //            double v2 = populacao[k].peso;
        //            paletaCor.updatePorcentagem((v2-v1)/(v3-v1));
        //            im.desenhaElipse2(populacao[k].pose.x,populacao[k].pose.y,0.2,0.2,QColor(paletaCor.cor->red(),paletaCor.cor->green(),paletaCor.cor->blue()),Qt::NoBrush);
        //            //cout<<searchSpace<<" "<<populacao[k].pose.x<<" "<<populacao[k].pose.y<<" "<<populacao[k].pose.z<<endl;
        //        }
        //        im.desenhaElipse2(poseXYZ[j].x,poseXYZ[j].y,0.5,0.5,Qt::black,Qt::black);
        //        im.finalizarPainter();
        //        im.salvarImagem("../mapasResult/"+QString::number(j)+".bmp");

        //cout<<endl;
    }
    logParticulas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio))+"\n";
    logParticulas<<"#Inicializacoes do filtro "+d.stringalizar(reinicializaFP);
    logParticulas<<"\n#Fim";
    logCaixas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio));
    logCaixas<<"\n#Fim";
    logParticulas.close();
    logCaixas.close();

}



void Hibrido::executarLocalizacaoHibridaSivia1(IntervalVector searchSpace, IntervalVector ambienteInicial, QVector<xyz> poseXYZ, QVector<xyz> yawPitchRoll, QVector<xyz> velXYZ, QVector<QVector<transponder> > transponders, QVector<Landmark> landmarksUsados, int idExec){

    clock_t inicio=clock();
    std::stringstream sstr;
    sstr << idExec;
    string nome = PATH_RESULTS + sstr.str() + string("hibridoSivia1BB.csv");
    ofstream logCaixasBB(nome.c_str());
    //    nome = PATH_RESULTS + sstr.str() + string("hibridoSivia1Caixas.csv");
    //    ofstream logCaixas(nome.c_str());
    nome = PATH_RESULTS + sstr.str() + string("hibridoSivia1FP.csv");
    ofstream logParticulas(nome.c_str());


    Dados d;
    Sivia s;
    QVector<Particula> populacao;
    int movAnterior=0;
    double normalizador=0;
    FiltroParticulas fp;
    int reinicializaFP=0;


    //    logCaixas<<"#minx;maxx;miny;maxy;minz;maxz\n";
    logCaixasBB<<"#minx;maxx;miny;maxy;minz;maxz\n";
    logParticulas<<"#melhor.pose.x;melhor.pose.y;melhor.pose.z;melhor.ypr.x;melhor.ypr.y;melhor.ypr.z;pior.pose.x;pior.pose.y;pior.pose.z;pior.ypr.x;pior.ypr.y;pior.ypr.z;media.pose.x;media.pose.y;media.pose.z;media.ypr.x;media.ypr.y;media.ypr.z;\n";



    QVector <IntervalVector> resultSivia;
    for(int j=0;j<poseXYZ.size();j=j+LEITURAS_POR_TEMPO_LEITURAS){
        if(j%100==0)qDebug()<<"Etapa"<<j<<"/"<<poseXYZ.size();
        //                cout<<j<<endl;
        //                Imagem im;
        //                im.carregarImagem("../mapas/mapa1000x1000.bmp");
        //                im.inicializarPaiter();
        //                im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::blue,Qt::NoBrush);

        //fp*************************************************************************
        normalizador=0;

        //ai*************************************************************************
        resultSivia.clear();
        resultSivia=s.execSivia(searchSpace,landmarksUsados,transponders[j]);

        double _x[3][2]={{poseXYZ[j].x,poseXYZ[j].x},{poseXYZ[j].y, poseXYZ[j].y},{poseXYZ[j].z,poseXYZ[j].z}};
        IntervalVector p(3,_x);
        if(!p.is_subset(searchSpace)) {qDebug()<<"Robo fora da caixa!!!!!!!!";}

        logCaixasBB<<d.stringalizar(searchSpace[0].lb())+";"+d.stringalizar(searchSpace[0].ub())+";"+d.stringalizar(searchSpace[1].lb())+";"+d.stringalizar(searchSpace[1].ub())+";"+d.stringalizar(searchSpace[2].lb())+";"+d.stringalizar(searchSpace[2].ub())+";\n";


        //        im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::red,Qt::NoBrush);

        //fp*************************************************************************
        //se for 1a iteração criar partículas dentro do searchSpace
        if(j==0){

            double v=0;
            for (int i=0;i<resultSivia.size();i++){v=v+resultSivia[j].volume();}
            double acum=0;
            double ppm=TAMANHO_POPULACAO/v;
            for (int i=0;i<resultSivia.size();i++){
                int partCaixa=resultSivia[i].volume()*ppm;
                acum=acum+(resultSivia[i].volume()*ppm)-partCaixa;
                if(acum>=0.85){partCaixa++;acum=0;}
                for(int k=0;k<partCaixa;k++){
                    Particula p;
                    p.pose.x=p.fRand(resultSivia[i][0].lb(),resultSivia[i][0].ub());
                    p.pose.y=p.fRand(resultSivia[i][1].lb(),resultSivia[i][1].ub());
                    p.pose.z=p.fRand(resultSivia[i][2].lb(),resultSivia[i][2].ub());
                    p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    populacao.push_back(p);
                    if(populacao.size()<1)qDebug()<<"VAI DA PAU (j==0)"<<populacao.size();
                    normalizador += populacao[populacao.size()-1].calcularPeso(transponders[j],landmarksUsados);
                }
            }

        }

        //se não é a primeira iteração, então move as particulas da populacao existente

        if(j!=0){



            //            QVector <Particula> populacaoAux;
            //            std::swap(populacao,populacaoAux);
            //            populacao.clear();
            //            for(int k=0;k<populacaoAux.size();k++){
            //                populacaoAux[k].modeloMovimento2(velXYZ[j].xNoise,velXYZ[j].yNoise,velXYZ[j].zNoise,yawPitchRoll[j].xNoise,yawPitchRoll[j].yNoise,yawPitchRoll[j].zNoise, (yawPitchRoll[j].xNoise-yawPitchRoll[movAnterior].xNoise) ,(yawPitchRoll[j].yNoise-yawPitchRoll[movAnterior].yNoise),(yawPitchRoll[j].zNoise-yawPitchRoll[movAnterior].zNoise));
            //            }

            for(int k=0;k<populacao.size();k++){
                populacao[k].modeloMovimento2(velXYZ[j].xNoise,velXYZ[j].yNoise,velXYZ[j].zNoise,yawPitchRoll[j].xNoise,yawPitchRoll[j].yNoise,yawPitchRoll[j].zNoise, (yawPitchRoll[j].xNoise-yawPitchRoll[movAnterior].xNoise) ,(yawPitchRoll[j].yNoise-yawPitchRoll[movAnterior].yNoise),(yawPitchRoll[j].zNoise-yawPitchRoll[movAnterior].zNoise));
            }



            //testa se as partículas da população estão dentro do searchSpace, eliminar as que estão fora e repoe com uma aleatoria

            //std::swap(populacaoAux,populacao);
            int dentro;
            for(int k=0;k<populacao.size();k++){
                dentro=0;
                for(int l=0;l<resultSivia.size();l++){
                    if(resultSivia[l][0].contains(populacao[k].pose.x) && resultSivia[l][1].contains(populacao[k].pose.y) && resultSivia[l][2].contains(populacao[k].pose.z)){
                        dentro=1;
                        break;
                    }
                }
                if(dentro==0){
                    int r=rand()%resultSivia.size();
                    populacao[k].pose.x=populacao[k].fRand(resultSivia[r][0].lb(),resultSivia[r][0].ub());
                    populacao[k].pose.y=populacao[k].fRand(resultSivia[r][1].lb(),resultSivia[r][1].ub());
                    populacao[k].pose.z=populacao[k].fRand(resultSivia[r][2].lb(),resultSivia[r][2].ub());
                    populacao[k].yawPitchRoll.x=populacao[k].fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    populacao[k].yawPitchRoll.y=populacao[k].fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    populacao[k].yawPitchRoll.z=populacao[k].fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                }



                normalizador=normalizador+populacao[k].calcularPeso(transponders[j],landmarksUsados);

            }















            movAnterior=j;
            // populacaoAux.clear();



            if(populacao.size()<1){
                qDebug()<<"Reinicializar população";
                normalizador=0;
                int v=0;
                for (int i=0;i<resultSivia.size();i++){v=v+resultSivia[j].volume();}
                for(int k=0;k<TAMANHO_POPULACAO;k++){
                    double acum=0;
                    double ppm=TAMANHO_POPULACAO/v;
                    for (int i=0;i<resultSivia.size();i++){
                        int partCaixa=resultSivia[i].volume()*ppm;
                        acum=acum+(resultSivia[i].volume()*ppm)-partCaixa;
                        if(acum>=0.85){partCaixa++;acum=0;}
                        for(int k=0;k<partCaixa;k++){
                            Particula p;
                            p.pose.x=p.fRand(resultSivia[i][0].lb(),resultSivia[i][0].ub());
                            p.pose.y=p.fRand(resultSivia[i][1].lb(),resultSivia[i][1].ub());
                            p.pose.z=p.fRand(resultSivia[i][2].lb(),resultSivia[i][2].ub());
                            p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                            p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                            p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                            populacao.push_back(p);
                            normalizador += populacao[populacao.size()-1].calcularPeso(transponders[j],landmarksUsados);
                        }
                    }
                }
                reinicializaFP++;
            }
        }

        //executa roleta na população
        for(int k=0;k<populacao.size();k++){
            populacao[k].peso=populacao[k].peso/normalizador;
        }
        try{
            fp.roleta(populacao);
        }catch(Exception e){
            qDebug()<<"PROBLEMA";
        }

        //ai*************************************************************************
        //move searchSpace
        Interval vx((velXYZ[j].xNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].xNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vy((velXYZ[j].yNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].yNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vz((velXYZ[j].zNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].zNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval phi  (yawPitchRoll[j].xNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].xNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval theta(yawPitchRoll[j].yNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].yNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval psi  (yawPitchRoll[j].zNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].zNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        s.moveCaixa( searchSpace, ambienteInicial, vx,  vy,  vz,  phi,  theta,  psi);

        //fp*************************************************************************
        Particula piorParticula, melhorParticula, mp;
        piorParticula.peso=-1;melhorParticula.peso=-1;
        double mpx=0, mpy=0, mpz=0, a1=0, a2=0, a3=0, angx=0, angy=0, angz=0, a4=0, a5=0, a6=0;
        for(int k=0;k<populacao.size();k++){
            if(populacao[k].peso<piorParticula.peso || piorParticula.peso==-1){
                piorParticula=populacao[k];
            }
            if(populacao[k].peso>melhorParticula.peso || melhorParticula.peso==-1){
                melhorParticula=populacao[k];
            }
            mpx=mpx+populacao[k].pose.x*populacao[k].peso;
            a1=a1+populacao[k].peso;
            mpy=mpy+populacao[k].pose.y*populacao[k].peso;
            a2=a2+populacao[k].peso;
            mpz=mpz+populacao[k].pose.z*populacao[k].peso;
            a3=a3+populacao[k].peso;
            angx=angx+populacao[k].yawPitchRoll.x*populacao[k].peso;
            a4=a4+populacao[k].peso;
            angy=angy+populacao[k].yawPitchRoll.y*populacao[k].peso;
            a5=a5+populacao[k].peso;
            angz=angz+populacao[k].yawPitchRoll.z*populacao[k].peso;
            a6=a6+populacao[k].peso;
        }
        mp.pose.x=mpx/a1;
        mp.pose.y=mpy/a2;
        mp.pose.z=mpz/a3;
        mp.yawPitchRoll.x=angx/a4;
        mp.yawPitchRoll.y=angy/a5;
        mp.yawPitchRoll.z=angz/a6;

        logParticulas<<d.stringalizar(melhorParticula.pose.x)+";"+d.stringalizar(melhorParticula.pose.y)+";"+d.stringalizar(melhorParticula.pose.z)+";"+d.stringalizar(melhorParticula.yawPitchRoll.x)+";"+d.stringalizar(melhorParticula.yawPitchRoll.y)+";"+d.stringalizar(melhorParticula.yawPitchRoll.z)+";"+d.stringalizar(piorParticula.pose.x)+";"+d.stringalizar(piorParticula.pose.y)+";"+d.stringalizar(piorParticula.pose.z)+";"+d.stringalizar(piorParticula.yawPitchRoll.x)+";"+d.stringalizar(piorParticula.yawPitchRoll.y)+";"+d.stringalizar(piorParticula.yawPitchRoll.z)+";"+d.stringalizar(mp.pose.x)+";"+d.stringalizar(mp.pose.y)+";"+d.stringalizar(mp.pose.z)+";"+d.stringalizar(mp.yawPitchRoll.x)+";"+d.stringalizar(mp.yawPitchRoll.y)+";"+d.stringalizar(mp.yawPitchRoll.z)+";"+"\n";





        //        for(int l=0;l<resultSivia.size();l++){
        //            logCaixas<<d.stringalizar(resultSivia[l][0].lb())+";"+d.stringalizar(resultSivia[l][0].ub())+";"+d.stringalizar(resultSivia[l][1].lb())+";"+d.stringalizar(resultSivia[l][1].ub())+";"+d.stringalizar(resultSivia[l][2].lb())+";"+d.stringalizar(resultSivia[l][2].ub())+";\n";
        ////            im.desenhaCaixa2(resultSivia[l][0].lb(),resultSivia[l][0].ub(),resultSivia[l][1].lb(),resultSivia[l][1].ub(),Qt::lightGray,Qt::NoBrush);
        //        }
        //        logCaixas<<"*\n";

        //        PaletaCores paletaCor;
        //        double v1 = piorParticula.peso;
        //        double v3 = melhorParticula.peso;
        //        if(v1==v3){
        //            v1=v1-1;
        //            v3=v3-1;
        //        }
        //        for(int k=0;k<populacao.size();k++){
        //            double v2 = populacao[k].peso;
        //            paletaCor.updatePorcentagem((v2-v1)/(v3-v1));
        //            im.desenhaElipse2(populacao[k].pose.x,populacao[k].pose.y,0.2,0.2,QColor(paletaCor.cor->red(),paletaCor.cor->green(),paletaCor.cor->blue()),Qt::NoBrush);
        //            //cout<<searchSpace<<" "<<populacao[k].pose.x<<" "<<populacao[k].pose.y<<" "<<populacao[k].pose.z<<endl;
        //        }
        //        im.desenhaElipse2(poseXYZ[j].x,poseXYZ[j].y,0.5,0.5,Qt::black,Qt::black);
        //        im.finalizarPainter();
        //        im.salvarImagem("../mapasResult/"+QString::number(j)+".bmp");

        //cout<<endl;
    }
    logParticulas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio))+"\n";
    logParticulas<<"#Inicializacoes do filtro "+d.stringalizar(reinicializaFP);
    logParticulas<<"\n#Fim";
    //    logCaixas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio));
    //    logCaixas<<"\n#Fim";
    logCaixasBB<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio));
    logCaixasBB<<"\n#Fim";
    logParticulas.close();
    //    logCaixas.close();
    logCaixasBB.close();


}



//********************************************************************************************************************
void Hibrido::executarLocalizacaoHibridaSivia2(IntervalVector searchSpace, IntervalVector ambienteInicial, QVector<xyz> poseXYZ, QVector<xyz> yawPitchRoll, QVector<xyz> velXYZ, QVector<QVector<transponder> > transponders, QVector<Landmark> landmarksUsados, int idExec){

    clock_t inicio=clock();
    std::stringstream sstr;
    sstr << idExec;
    string nome;
    nome = PATH_RESULTS + sstr.str() + string("hibridoSivia2BB.csv");
    ofstream logCaixasBB(nome.c_str());
    //    nome = PATH_RESULTS + sstr.str() + string("hibridoSivia2Caixas.csv");
    //    ofstream logCaixas(nome.c_str());
    nome = PATH_RESULTS + sstr.str() + string("hibridoSivia2FP.csv");
    ofstream logParticulas(nome.c_str());


    Dados d;
    Sivia s;
    QVector<Particula> populacao;
    int movAnterior=0;
    double normalizador=0;
    FiltroParticulas fp;
    int reinicializaFP=0;


    //    logCaixas<<"#minx;maxx;miny;maxy;minz;maxz\n";
    logCaixasBB<<"#minx;maxx;miny;maxy;minz;maxz\n";
    logParticulas<<"#melhor.pose.x;melhor.pose.y;melhor.pose.z;melhor.ypr.x;melhor.ypr.y;melhor.ypr.z;pior.pose.x;pior.pose.y;pior.pose.z;pior.ypr.x;pior.ypr.y;pior.ypr.z;media.pose.x;media.pose.y;media.pose.z;media.ypr.x;media.ypr.y;media.ypr.z;\n";


    QVector <IntervalVector> resultSivia;
    for(int j=0;j<poseXYZ.size();j=j+LEITURAS_POR_TEMPO_LEITURAS){
        if(j%100==0)qDebug()<<"Etapa"<<j<<"/"<<poseXYZ.size();

        //                cout<<j<<endl;
        //                Imagem im;
        //                im.carregarImagem("../mapas/mapa1000x1000.bmp");
        //                im.inicializarPaiter();
        //                im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::blue,Qt::NoBrush);

        //fp*************************************************************************
        normalizador=0;

        //ai*************************************************************************
        resultSivia.clear();
        resultSivia=s.execSiviaContratores(searchSpace,landmarksUsados,transponders[j]);

        double _x[3][2]={{poseXYZ[j].x,poseXYZ[j].x},{poseXYZ[j].y, poseXYZ[j].y},{poseXYZ[j].z,poseXYZ[j].z}};
        IntervalVector p(3,_x);
        if(!p.is_subset(searchSpace)) {qDebug()<<"Robo fora da caixa!!!!!!!!";}

        logCaixasBB<<d.stringalizar(searchSpace[0].lb())+";"+d.stringalizar(searchSpace[0].ub())+";"+d.stringalizar(searchSpace[1].lb())+";"+d.stringalizar(searchSpace[1].ub())+";"+d.stringalizar(searchSpace[2].lb())+";"+d.stringalizar(searchSpace[2].ub())+";\n";


        //        im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::red,Qt::NoBrush);

        //fp*************************************************************************
        //se for 1a iteração criar partículas dentro do searchSpace
        if(j==0){

            double v=0;
            for (int i=0;i<resultSivia.size();i++){v=v+resultSivia[j].volume();}
            double acum=0;
            double ppm=TAMANHO_POPULACAO/v;
            for (int i=0;i<resultSivia.size();i++){
                int partCaixa=resultSivia[i].volume()*ppm;
                acum=acum+(resultSivia[i].volume()*ppm)-partCaixa;
                if(acum>=0.85){partCaixa++;acum=0;}
                for(int k=0;k<partCaixa;k++){
                    Particula p;
                    p.pose.x=p.fRand(resultSivia[i][0].lb(),resultSivia[i][0].ub());
                    p.pose.y=p.fRand(resultSivia[i][1].lb(),resultSivia[i][1].ub());
                    p.pose.z=p.fRand(resultSivia[i][2].lb(),resultSivia[i][2].ub());
                    p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    populacao.push_back(p);
                    if(populacao.size()<1)qDebug()<<"VAI DA PAU (j==0)"<<populacao.size();
                    normalizador += populacao[populacao.size()-1].calcularPeso(transponders[j],landmarksUsados);
                }
            }

        }

        //se não é a primeira iteração, então move as particulas da populacao existente

        if(j!=0){



            //            QVector <Particula> populacaoAux;
            //            std::swap(populacao,populacaoAux);
            //            populacao.clear();
            //            for(int k=0;k<populacaoAux.size();k++){
            //                populacaoAux[k].modeloMovimento2(velXYZ[j].xNoise,velXYZ[j].yNoise,velXYZ[j].zNoise,yawPitchRoll[j].xNoise,yawPitchRoll[j].yNoise,yawPitchRoll[j].zNoise, (yawPitchRoll[j].xNoise-yawPitchRoll[movAnterior].xNoise) ,(yawPitchRoll[j].yNoise-yawPitchRoll[movAnterior].yNoise),(yawPitchRoll[j].zNoise-yawPitchRoll[movAnterior].zNoise));
            //            }

            for(int k=0;k<populacao.size();k++){
                populacao[k].modeloMovimento2(velXYZ[j].xNoise,velXYZ[j].yNoise,velXYZ[j].zNoise,yawPitchRoll[j].xNoise,yawPitchRoll[j].yNoise,yawPitchRoll[j].zNoise, (yawPitchRoll[j].xNoise-yawPitchRoll[movAnterior].xNoise) ,(yawPitchRoll[j].yNoise-yawPitchRoll[movAnterior].yNoise),(yawPitchRoll[j].zNoise-yawPitchRoll[movAnterior].zNoise));
            }



            //testa se as partículas da população estão dentro do searchSpace, eliminar as que estão fora e repoe com uma aleatoria

            //std::swap(populacaoAux,populacao);
            int dentro;
            for(int k=0;k<populacao.size();k++){
                dentro=0;
                for(int l=0;l<resultSivia.size();l++){
                    if(resultSivia[l][0].contains(populacao[k].pose.x) && resultSivia[l][1].contains(populacao[k].pose.y) && resultSivia[l][2].contains(populacao[k].pose.z)){
                        dentro=1;
                        break;
                    }
                }
                if(dentro==0){
                    int r=rand()%resultSivia.size();
                    populacao[k].pose.x=populacao[k].fRand(resultSivia[r][0].lb(),resultSivia[r][0].ub());
                    populacao[k].pose.y=populacao[k].fRand(resultSivia[r][1].lb(),resultSivia[r][1].ub());
                    populacao[k].pose.z=populacao[k].fRand(resultSivia[r][2].lb(),resultSivia[r][2].ub());
                    populacao[k].yawPitchRoll.x=populacao[k].fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    populacao[k].yawPitchRoll.y=populacao[k].fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                    populacao[k].yawPitchRoll.z=populacao[k].fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                }



                normalizador=normalizador+populacao[k].calcularPeso(transponders[j],landmarksUsados);

            }


            movAnterior=j;
            // populacaoAux.clear();



            if(populacao.size()<1){
                qDebug()<<"Reinicializar população";
                normalizador=0;
                int v=0;
                for (int i=0;i<resultSivia.size();i++){v=v+resultSivia[j].volume();}
                for(int k=0;k<TAMANHO_POPULACAO;k++){
                    double acum=0;
                    double ppm=TAMANHO_POPULACAO/v;
                    for (int i=0;i<resultSivia.size();i++){
                        int partCaixa=resultSivia[i].volume()*ppm;
                        acum=acum+(resultSivia[i].volume()*ppm)-partCaixa;
                        if(acum>=0.85){partCaixa++;acum=0;}
                        for(int k=0;k<partCaixa;k++){
                            Particula p;
                            p.pose.x=p.fRand(resultSivia[i][0].lb(),resultSivia[i][0].ub());
                            p.pose.y=p.fRand(resultSivia[i][1].lb(),resultSivia[i][1].ub());
                            p.pose.z=p.fRand(resultSivia[i][2].lb(),resultSivia[i][2].ub());
                            p.yawPitchRoll.x=p.fRand(yawPitchRoll[j].x-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].x+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                            p.yawPitchRoll.y=p.fRand(yawPitchRoll[j].y-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].y+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                            p.yawPitchRoll.z=p.fRand(yawPitchRoll[j].z-SIGMA_FACTOR_ORI*STD_ORIENTATION,yawPitchRoll[j].z+SIGMA_FACTOR_ORI*STD_ORIENTATION);
                            populacao.push_back(p);
                            normalizador += populacao[populacao.size()-1].calcularPeso(transponders[j],landmarksUsados);
                        }
                    }
                }
                reinicializaFP++;
            }
        }

        //executa roleta na população
        for(int k=0;k<populacao.size();k++){
            populacao[k].peso=populacao[k].peso/normalizador;
        }
        try{
            fp.roleta(populacao);
        }catch(Exception e){
            qDebug()<<"PROBLEMA";
        }

        //ai*************************************************************************
        //move searchSpace
        Interval vx((velXYZ[j].xNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].xNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vy((velXYZ[j].yNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].yNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vz((velXYZ[j].zNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].zNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval phi  (yawPitchRoll[j].xNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].xNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval theta(yawPitchRoll[j].yNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].yNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval psi  (yawPitchRoll[j].zNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].zNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        s.moveCaixa( searchSpace, ambienteInicial, vx,  vy,  vz,  phi,  theta,  psi);

        //fp*************************************************************************
        Particula piorParticula, melhorParticula, mp;
        piorParticula.peso=-1;melhorParticula.peso=-1;
        double mpx=0, mpy=0, mpz=0, a1=0, a2=0, a3=0, angx=0, angy=0, angz=0, a4=0, a5=0, a6=0;
        for(int k=0;k<populacao.size();k++){
            if(populacao[k].peso<piorParticula.peso || piorParticula.peso==-1){
                piorParticula=populacao[k];
            }
            if(populacao[k].peso>melhorParticula.peso || melhorParticula.peso==-1){
                melhorParticula=populacao[k];
            }
            mpx=mpx+populacao[k].pose.x*populacao[k].peso;
            a1=a1+populacao[k].peso;
            mpy=mpy+populacao[k].pose.y*populacao[k].peso;
            a2=a2+populacao[k].peso;
            mpz=mpz+populacao[k].pose.z*populacao[k].peso;
            a3=a3+populacao[k].peso;
            angx=angx+populacao[k].yawPitchRoll.x*populacao[k].peso;
            a4=a4+populacao[k].peso;
            angy=angy+populacao[k].yawPitchRoll.y*populacao[k].peso;
            a5=a5+populacao[k].peso;
            angz=angz+populacao[k].yawPitchRoll.z*populacao[k].peso;
            a6=a6+populacao[k].peso;
        }
        mp.pose.x=mpx/a1;
        mp.pose.y=mpy/a2;
        mp.pose.z=mpz/a3;
        mp.yawPitchRoll.x=angx/a4;
        mp.yawPitchRoll.y=angy/a5;
        mp.yawPitchRoll.z=angz/a6;

        logParticulas<<d.stringalizar(melhorParticula.pose.x)+";"+d.stringalizar(melhorParticula.pose.y)+";"+d.stringalizar(melhorParticula.pose.z)+";"+d.stringalizar(melhorParticula.yawPitchRoll.x)+";"+d.stringalizar(melhorParticula.yawPitchRoll.y)+";"+d.stringalizar(melhorParticula.yawPitchRoll.z)+";"+d.stringalizar(piorParticula.pose.x)+";"+d.stringalizar(piorParticula.pose.y)+";"+d.stringalizar(piorParticula.pose.z)+";"+d.stringalizar(piorParticula.yawPitchRoll.x)+";"+d.stringalizar(piorParticula.yawPitchRoll.y)+";"+d.stringalizar(piorParticula.yawPitchRoll.z)+";"+d.stringalizar(mp.pose.x)+";"+d.stringalizar(mp.pose.y)+";"+d.stringalizar(mp.pose.z)+";"+d.stringalizar(mp.yawPitchRoll.x)+";"+d.stringalizar(mp.yawPitchRoll.y)+";"+d.stringalizar(mp.yawPitchRoll.z)+";"+"\n";





        //        for(int l=0;l<resultSivia.size();l++){
        //            logCaixas<<d.stringalizar(resultSivia[l][0].lb())+";"+d.stringalizar(resultSivia[l][0].ub())+";"+d.stringalizar(resultSivia[l][1].lb())+";"+d.stringalizar(resultSivia[l][1].ub())+";"+d.stringalizar(resultSivia[l][2].lb())+";"+d.stringalizar(resultSivia[l][2].ub())+";\n";
        ////            im.desenhaCaixa2(resultSivia[l][0].lb(),resultSivia[l][0].ub(),resultSivia[l][1].lb(),resultSivia[l][1].ub(),Qt::lightGray,Qt::NoBrush);
        //        }
        //        logCaixas<<"*\n";

        //        PaletaCores paletaCor;
        //        double v1 = piorParticula.peso;
        //        double v3 = melhorParticula.peso;
        //        if(v1==v3){
        //            v1=v1-1;
        //            v3=v3-1;
        //        }
        //        for(int k=0;k<populacao.size();k++){
        //            double v2 = populacao[k].peso;
        //            paletaCor.updatePorcentagem((v2-v1)/(v3-v1));
        //            im.desenhaElipse2(populacao[k].pose.x,populacao[k].pose.y,0.2,0.2,QColor(paletaCor.cor->red(),paletaCor.cor->green(),paletaCor.cor->blue()),Qt::NoBrush);
        //            //cout<<searchSpace<<" "<<populacao[k].pose.x<<" "<<populacao[k].pose.y<<" "<<populacao[k].pose.z<<endl;
        //        }
        //        im.desenhaElipse2(poseXYZ[j].x,poseXYZ[j].y,0.5,0.5,Qt::black,Qt::black);
        //        im.finalizarPainter();
        //        im.salvarImagem("../mapasResult/"+QString::number(j)+".bmp");

        //cout<<endl;
    }
    logParticulas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio))+"\n";
    logParticulas<<"#Inicializacoes do filtro "+d.stringalizar(reinicializaFP);
    logParticulas<<"\n#Fim";
    //    logCaixas<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio));
    //    logCaixas<<"\n#Fim";
    logCaixasBB<<"#Tempo(s): "+d.stringalizar(d.tempo(inicio));
    logCaixasBB<<"\n#Fim";
    logParticulas.close();
    //    logCaixas.close();
    logCaixasBB.close();


}
