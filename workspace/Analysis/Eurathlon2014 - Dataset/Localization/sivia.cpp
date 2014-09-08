#include "sivia.h"

Sivia::Sivia()
{
}

double Sivia::tempo(clock_t inicio){
    clock_t fim;
    fim=clock();
    double t=(double)(fim - inicio)/CLOCKS_PER_SEC;
    return t;
}

//std::string stringalizar(double x)
//{
//    std::ostringstream oss;
//    oss << x;
//    return oss.str();
//}

iboolean Sivia::In(const Interval F, const Interval Y)
{
    //double r=0.0000000017;//1e-17;
    Interval Z= Y;//Y.inflate(r);
    if (F.is_disjoint(Z)) return false;
    if (F.is_subset(Z)) return true;
    return iboolean(iperhaps);
}

iboolean Sivia::Inside (IntervalVector X, QVector<Landmark>  landmarks, QVector<transponder> landmarksDist/*, box& V*/)
{
    int i;
    QVector<Interval> F;
    for(i=0;i<landmarks.size();i++){
        //cout<<landmarksDist[i].dist<<landmarks[i].posicao.x<<landmarks[i].posicao.y<<landmarks[i].posicao.z<<endl;
        Landmark aux=landmarks[i];
        Interval x=Interval(aux.posicao.x,aux.posicao.x);
        Interval y=Interval(aux.posicao.y,aux.posicao.y);
        Interval z=Interval(aux.posicao.z,aux.posicao.z);
        F.push_back(sqrt(sqr(X[0]-x)+sqr(X[1]-y)+sqr(X[2]-z)));//3d

    }
    iboolean result;
    double erroTransp=STD_DIST_TRANSP*SIGMA_FACTOR_TRA;
    if(F.size()>1){
        result=(In(F[0],Interval(landmarksDist[0].distNoise-erroTransp,landmarksDist[0].distNoise+erroTransp)) && In(F[1],Interval(landmarksDist[1].distNoise-erroTransp,landmarksDist[1].distNoise+erroTransp)));
        for(i=2;i<F.size();i++){
            result=(In(F[i],Interval(landmarksDist[i].distNoise-erroTransp,landmarksDist[i].distNoise+erroTransp)) && result);
        }
    }else{
        result=(In(F[0],Interval(landmarksDist[0].distNoise-erroTransp,landmarksDist[0].distNoise+erroTransp)));
    }




    //testa com caixa viajante, senão quiser que corte é só comentar essa linha
    //result=(In(X[1],V[1]) && In(X[2],V[2]) && result);

    return (result);

}


QVector <IntervalVector> Sivia::execSivia(IntervalVector& box, QVector<Landmark> landmarks, QVector<transponder> landmarksDist){
    QVector <IntervalVector> caixas;

    double mxX,mxY,mxZ,mnX,mnY,mnZ;  mxX=mxY=mxZ=mnX=mnY=mnZ=-1.0;

    list <IntervalVector> L;
    IntervalVector X=box;
    LargestFirst lf;

    caixas.clear();
    L.push_back (X);
    //int e=0, t=0;
    while ( !L.empty() )
    {
        IntervalVector Xaux(3);

        Xaux=L.front();   L.pop_front();

        iboolean test=Inside(Xaux,landmarks,landmarksDist);


        if (Xaux.max_diam()<EPSILON){
            caixas.push_back(Xaux);
            //e++;
            if(mnX==-1 || Xaux[0].lb()<mnX)mnX=Xaux[0].lb();   if(mnY==-1 || Xaux[1].lb()<mnY)mnY=Xaux[1].lb();   if(mnZ==-1 || Xaux[2].lb()<mnZ)mnZ=Xaux[2].lb();
            if(mxX==-1 || Xaux[0].ub()>mxX)mxX=Xaux[0].ub();   if(mxY==-1 || Xaux[1].ub()>mxY)mxY=Xaux[1].ub();   if(mxZ==-1 || Xaux[2].ub()>mxZ)mxZ=Xaux[2].ub();
        }
        else if ( test==itrue ){
            caixas.push_back(Xaux);
            //t++;
            if(mnX==-1 || Xaux[0].lb()<mnX)mnX=Xaux[0].lb();   if(mnY==-1 || Xaux[1].lb()<mnY)mnY=Xaux[1].lb();   if(mnZ==-1 || Xaux[2].lb()<mnZ)mnZ=Xaux[2].lb();
            if(mxX==-1 || Xaux[0].ub()>mxX)mxX=Xaux[0].ub();   if(mxY==-1 || Xaux[1].ub()>mxY)mxY=Xaux[1].ub();   if(mxZ==-1 || Xaux[2].ub()>mxZ)mxZ=Xaux[2].ub();
        }
        else if (test==ifalse){}
        else{
            pair <IntervalVector,IntervalVector> intervalos = lf.bisect(Xaux);//   Xaux.bisect(0.5);
            L.push_back(intervalos.first);  L.push_back(intervalos.second);
        }

    }

    box.clear();
    double _x[3][2]={{mnX,mxX},{mnY, mxY},{mnZ,mxZ}};
    IntervalVector a(3,_x);
    box=a;
    //cout<<"nro de caixas "<<e<<" "<<t<<endl;
    return caixas;
}

QVector <IntervalVector> Sivia::execSiviaContratores(IntervalVector& box, QVector<Landmark> landmarks, QVector<transponder> landmarksDist){
    QVector <IntervalVector> caixas;

    double mxX,mxY,mxZ,mnX,mnY,mnZ;  mxX=mxY=mxZ=mnX=mnY=mnZ=-1.0;

    list <IntervalVector> L;
    IntervalVector X=box;
    LargestFirst lf;

    caixas.clear();
    L.push_back (X);
    //int e=0, t=0;


    //*****************************************
    const int N=NRO_TRANSPONDERS;
    Interval bX[N];
    Interval bY[N];
    Interval bZ[N];
    Interval bD[N];
    for (int i=0; i<N; i++) {
        bX[i]=Interval(landmarks[i].posicao.x);
        bY[i]=Interval(landmarks[i].posicao.y);
        bZ[i]=Interval(landmarks[i].posicao.z);
        bD[i]=Interval(landmarksDist[i].distNoise-(STD_DIST_TRANSP*SIGMA_FACTOR_TRA),landmarksDist[i].distNoise+(STD_DIST_TRANSP*SIGMA_FACTOR_TRA));
    }
    Array<Ctc> array(N);
    Variable x(3);
    for(int c=0;c<N;c++){
        Function *fun2 =new Function(x,((sqrt(sqr(x[0]-bX[c])+sqr(x[1]-bY[c])+sqr(x[2]-bZ[c]))-bD[c])));
        CtcFwdBwd *ar=new CtcFwdBwd(*fun2);
        array.set_ref(c,*ar);

    }
    CtcCompo comp(array);
    CtcFixPoint fix(comp);

    //******************************************


    while ( !L.empty() )
    {
        IntervalVector Xaux(3);

        Xaux=L.front();   L.pop_front();



        //************CONTRAI CAIXAS*********************************************

        int p=1;
        while(p==1){

            try{

                fix.contract(Xaux);
                p=0;
                //cout<<"nao vazia"<<endl;
            }catch(Exception e){
                //qDebug()<<"Caixa vazia";
                Xaux=L.front();   L.pop_front();

            }

        }
        //*********************************************************

        iboolean test=Inside(Xaux,landmarks,landmarksDist);


        if (Xaux.max_diam()<EPSILON){
            caixas.push_back(Xaux);
            //e++;
            if(mnX==-1 || Xaux[0].lb()<mnX)mnX=Xaux[0].lb();   if(mnY==-1 || Xaux[1].lb()<mnY)mnY=Xaux[1].lb();   if(mnZ==-1 || Xaux[2].lb()<mnZ)mnZ=Xaux[2].lb();
            if(mxX==-1 || Xaux[0].ub()>mxX)mxX=Xaux[0].ub();   if(mxY==-1 || Xaux[1].ub()>mxY)mxY=Xaux[1].ub();   if(mxZ==-1 || Xaux[2].ub()>mxZ)mxZ=Xaux[2].ub();
        }
        else if ( test==itrue ){
            caixas.push_back(Xaux);
            //t++;
            if(mnX==-1 || Xaux[0].lb()<mnX)mnX=Xaux[0].lb();   if(mnY==-1 || Xaux[1].lb()<mnY)mnY=Xaux[1].lb();   if(mnZ==-1 || Xaux[2].lb()<mnZ)mnZ=Xaux[2].lb();
            if(mxX==-1 || Xaux[0].ub()>mxX)mxX=Xaux[0].ub();   if(mxY==-1 || Xaux[1].ub()>mxY)mxY=Xaux[1].ub();   if(mxZ==-1 || Xaux[2].ub()>mxZ)mxZ=Xaux[2].ub();
        }
        else if (test==ifalse){}
        else{

            pair <IntervalVector,IntervalVector> intervalos = lf.bisect(Xaux);
            L.push_back(intervalos.first);  L.push_back(intervalos.second);
        }

    }

    box.clear();
    double _x[3][2]={{mnX,mxX},{mnY, mxY},{mnZ,mxZ}};
    IntervalVector a(3,_x);
    box=a;
    //cout<<"nro de caixas "<<e<<" "<<t<<endl;
    return caixas;
}

void Sivia::moveCaixa(IntervalVector& box, IntervalVector ambienteInicial, Interval vx, Interval vy, Interval vz, Interval phi, Interval theta, Interval psi){

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

    box[0]=box[0]+vx*J[0][0]+vy*J[0][1]+vz*J[0][2];
    box[1]=box[1]+vx*J[1][0]+vy*J[1][1]+vz*J[1][2];
    box[2]=box[2]+vx*J[2][0]+vy*J[2][1]+vz*J[2][2];


    box=box&ambienteInicial;

}

void Sivia::executarLocalizacaoSivia1(IntervalVector searchSpace, IntervalVector ambienteInicial, QVector<xyz> poseXYZ, QVector<xyz> yawPitchRoll, QVector<xyz> velXYZ, QVector<QVector<transponder> > transponders, QVector<Landmark> landmarksUsados, int idExec){

    clock_t inicio=clock();

    std::stringstream sstr;
    sstr << idExec;
    string nome;
    //    nome = PATH_RESULTS + sstr.str() + string("sivia1caixas.csv");
    //    ofstream logCaixas(nome.c_str());
    nome = PATH_RESULTS + sstr.str() + string("sivia1bb.csv");
    ofstream logBB(nome.c_str());
    Dados d;

    //    logCaixas<<"#o sinal '*' respresenta a divisao entre os conj de caixas por iteracao \n#minx;maxx;miny;maxy;minz;maxz\n";
    logBB<<"#minx;maxx;miny;maxy;minz;maxz\n";


    QVector <IntervalVector> resultSivia;


    for(int i=0;i<poseXYZ.size();i=i+LEITURAS_POR_TEMPO_LEITURAS){
        if(i%100==0)qDebug()<<"Etapa"<<i<<"/"<<poseXYZ.size();
        resultSivia.clear();
        resultSivia=execSivia(searchSpace,landmarksUsados,transponders[i]);
        logBB<<d.stringalizar(searchSpace[0].lb())+";"+d.stringalizar(searchSpace[0].ub())+";"+d.stringalizar(searchSpace[1].lb())+";"+d.stringalizar(searchSpace[1].ub())+";"+d.stringalizar(searchSpace[2].lb())+";"+d.stringalizar(searchSpace[2].ub())+";\n";

        //qDebug()<<searchSpace[0].lb()<<";"<<searchSpace[0].ub()<<";"<<searchSpace[1].lb()<<";"<<searchSpace[1].ub()<<";"<<searchSpace[2].lb()<<";"<<searchSpace[2].ub();

        Interval vx((velXYZ[i].xNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[i].xNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vy((velXYZ[i].yNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[i].yNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vz((velXYZ[i].zNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[i].zNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval phi  (yawPitchRoll[i].xNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[i].xNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval theta(yawPitchRoll[i].yNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[i].yNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval psi  (yawPitchRoll[i].zNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[i].zNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        moveCaixa(searchSpace, ambienteInicial, vx,vy,vz,phi,theta,psi);

        //        for(int k=0;k<resultSivia.size();k++){
        //            logCaixas<<d.stringalizar(resultSivia[k][0].lb())+";"+d.stringalizar(resultSivia[k][0].ub())+";"+d.stringalizar(resultSivia[k][1].lb())+";"+d.stringalizar(resultSivia[k][1].ub())+";"+d.stringalizar(resultSivia[k][2].lb())+";"+d.stringalizar(resultSivia[k][2].ub())+";\n";
        //        }
        //        logCaixas<<"*\n";

    }

    //    logCaixas<<"#Tempo: "+d.stringalizar(d.tempo(inicio));
    //    logCaixas<<"\n#Fim";
    logBB<<"#Tempo: "+d.stringalizar(d.tempo(inicio));
    logBB<<"\n#Fim";


}


void Sivia::executarLocalizacaoSivia2(IntervalVector searchSpace, IntervalVector ambienteInicial, QVector<xyz> poseXYZ, QVector<xyz> yawPitchRoll, QVector<xyz> velXYZ, QVector<QVector<transponder> > transponders, QVector<Landmark> landmarksUsados, int idExec){

    clock_t inicio=clock();

    std::stringstream sstr;
    sstr << idExec;
    string nome;
    nome = PATH_RESULTS + sstr.str() + string("sivia2caixas.csv");
    //ofstream logCaixas(nome.c_str());
    nome = PATH_RESULTS + sstr.str() + string("sivia2bb.csv");
    ofstream logBB(nome.c_str());
    Dados d;

    //logCaixas<<"#o sinal '*' respresenta a divisao entre os conj de caixas por iteracao \n#minx;maxx;miny;maxy;minz;maxz\n";
    logBB<<"#minx;maxx;miny;maxy;minz;maxz\n";


    QVector <IntervalVector> resultSivia;

    for(int i=0;i<poseXYZ.size();i=i+LEITURAS_POR_TEMPO_LEITURAS){

        //            Imagem im;
        //            im.carregarImagem("../mapas/mapa1000x1000.bmp");
        //            im.inicializarPaiter();


        if(i%100==0)qDebug()<<"Etapa"<<i<<"/"<<poseXYZ.size();
        resultSivia.clear();
        resultSivia=execSiviaContratores(searchSpace,landmarksUsados,transponders[i]);
        logBB<<d.stringalizar(searchSpace[0].lb())+";"+d.stringalizar(searchSpace[0].ub())+";"+d.stringalizar(searchSpace[1].lb())+";"+d.stringalizar(searchSpace[1].ub())+";"+d.stringalizar(searchSpace[2].lb())+";"+d.stringalizar(searchSpace[2].ub())+";\n";

        //        im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::red,Qt::NoBrush);

        //qDebug()<<searchSpace[0].lb()<<";"<<searchSpace[0].ub()<<";"<<searchSpace[1].lb()<<";"<<searchSpace[1].ub()<<";"<<searchSpace[2].lb()<<";"<<searchSpace[2].ub();

        Interval vx((velXYZ[i].xNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[i].xNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vy((velXYZ[i].yNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[i].yNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vz((velXYZ[i].zNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[i].zNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval phi  (yawPitchRoll[i].xNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[i].xNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval theta(yawPitchRoll[i].yNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[i].yNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval psi  (yawPitchRoll[i].zNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[i].zNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        moveCaixa(searchSpace,ambienteInicial,vx,vy,vz,phi,theta,psi);

        //        for(int k=0;k<resultSivia.size();k++){
        //            logCaixas<<d.stringalizar(resultSivia[k][0].lb())+";"+d.stringalizar(resultSivia[k][0].ub())+";"+d.stringalizar(resultSivia[k][1].lb())+";"+d.stringalizar(resultSivia[k][1].ub())+";"+d.stringalizar(resultSivia[k][2].lb())+";"+d.stringalizar(resultSivia[k][2].ub())+";\n";
        //            im.desenhaCaixa2(resultSivia[k][0].lb(),resultSivia[k][0].ub(),resultSivia[k][1].lb(),resultSivia[k][1].ub(),Qt::blue,Qt::NoBrush);
        //        }
        //        logCaixas<<"*\n";



        //        im.desenhaElipse2(poseXYZ[i].x,poseXYZ[i].y,0.5,0.5,Qt::black,Qt::black);
        //        im.finalizarPainter();
        //        im.salvarImagem("../mapasResult/"+QString::number(i)+".bmp");


    }

    //    logCaixas<<"#Tempo: "+d.stringalizar(d.tempo(inicio));
    //    logCaixas<<"\n#Fim";
    logBB<<"#Tempo: "+d.stringalizar(d.tempo(inicio));
    logBB<<"\n#Fim";


}

void Sivia::executarLocalizacaoContratores(IntervalVector searchSpace, IntervalVector ambienteInicial, QVector<xyz> poseXYZ, QVector<xyz> yawPitchRoll, QVector<xyz> velXYZ, QVector<QVector<transponder> > transponders, QVector<Landmark> landmarksUsados, int idExec){

    clock_t inicio=clock();

    std::stringstream sstr;
    sstr << idExec;
    string nome = PATH_RESULTS + sstr.str() + string("contratores.csv");
    ofstream logCaixas(nome.c_str());
    Dados d;

    logCaixas<<"#minx;maxx;miny;maxy;minz;maxz\n";


    for(int j=0;j<poseXYZ.size();j=j+LEITURAS_POR_TEMPO_LEITURAS){

        //    Imagem im;
        //    im.carregarImagem("../mapas/mapa1000x1000.bmp");
        //    im.inicializarPaiter();


        const int N=NRO_TRANSPONDERS;


        Interval bX[N];
        Interval bY[N];
        Interval bZ[N];
        Interval bD[N];
        /* add uncertainty on measurements */
        for (int i=0; i<N; i++) {
            bX[i]=Interval(landmarksUsados[i].posicao.x);
            bY[i]=Interval(landmarksUsados[i].posicao.y);
            bZ[i]=Interval(landmarksUsados[i].posicao.z);
            bD[i]=Interval(transponders[j][i].distNoise-(STD_DIST_TRANSP*SIGMA_FACTOR_TRA),transponders[j][i].distNoise+(STD_DIST_TRANSP*SIGMA_FACTOR_TRA));
        }


        //Array <Function> funcs(N);
        //vector <Function*> fun(N, NULL);
        Array<Ctc> array(N);
        //vector<Ctc*> ar(N,NULL);

        Variable x(3);
        for(int c=0;c<N;c++){
            Function *fun2 =new Function(x,((sqrt(sqr(x[0]-bX[c])+sqr(x[1]-bY[c])+sqr(x[2]-bZ[c]))-bD[c])));
            //fun[c]=new Function(x,((sqrt(sqr(x[0]-bX[c])+sqr(x[1]-bY[c])+sqr(x[2]-bZ[c]))-bD[c])));
            //funcs.set_ref(c, *fun2);

            CtcFwdBwd *ar=new CtcFwdBwd(*fun2);

            //ar[c]=new CtcFwdBwd(*fun2);
            array.set_ref(c,*ar);

        }



        //    im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::blue,Qt::NoBrush);

        CtcCompo comp(array);
        CtcFixPoint fix(comp);// O FIX POINT FICA CONTRAINDO ATÉ NÃO MUDAR MAIS SERIA COMO FAZER UM MONTE DE "comp.contract(array);"
        fix.contract(searchSpace);


        double _x[3][2]={{poseXYZ[j].x,poseXYZ[j].x},{poseXYZ[j].y, poseXYZ[j].y},{poseXYZ[j].z,poseXYZ[j].z}};
        IntervalVector p(3,_x);
        if(!p.is_subset(searchSpace))
            qDebug()<<"Robo fora da caixa!!!!!!!!";


        logCaixas<<d.stringalizar(searchSpace[0].lb())+";"+d.stringalizar(searchSpace[0].ub())+";"+d.stringalizar(searchSpace[1].lb())+";"+d.stringalizar(searchSpace[1].ub())+";"+d.stringalizar(searchSpace[2].lb())+";"+d.stringalizar(searchSpace[2].ub())+";\n";

        //    cout << "box =" << searchSpace << endl;

        //im.desenhaCaixa2(searchSpace[0].lb(),searchSpace[0].ub(),searchSpace[1].lb(),searchSpace[1].ub(),Qt::red,Qt::NoBrush);

        //move searchSpace
        Interval vx((velXYZ[j].xNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].xNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vy((velXYZ[j].yNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].yNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval vz((velXYZ[j].zNoise*TEMPO_LEITURAS)-(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER),(velXYZ[j].zNoise*TEMPO_LEITURAS)+(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER));
        Interval phi  (yawPitchRoll[j].xNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].xNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval theta(yawPitchRoll[j].yNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].yNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        Interval psi  (yawPitchRoll[j].zNoise-(SIGMA_FACTOR_ORI*STD_ORIENTATION),yawPitchRoll[j].zNoise+(SIGMA_FACTOR_ORI*STD_ORIENTATION));
        moveCaixa( searchSpace, ambienteInicial, vx,  vy,  vz,  phi,  theta,  psi);



        //   im.desenhaElipse2(poseXYZ[j].x,poseXYZ[j].y,0.5,0.5,Qt::red,Qt::red);
        //    im.finalizarPainter();
        //    im.salvarImagem("../mapasResult/"+QString::number(j)+".bmp");


    }
    logCaixas<<"#Tempo: "+d.stringalizar(d.tempo(inicio));
    logCaixas<<"\n#Fim";

}
