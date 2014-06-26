#define ROBOR_SIDE 0.075
#define BALL_RADIUS 0.02135
#define PI 3,141592653589793238

As coordenadas estão em metros, o ângulo está em radianos. Cada robô é determinado pela coordenadas cartesianas X e Y e pelo ângulo A.
A função "dist_overlap_robot_robot" dev retornar 0.0 caso os robôs não esjam sobrepostos. Se os robôs estiverem sobrepostos então a função deve retornar a distância que cada robô deve ser deslocado para que eles deixem de estar sobrepostos. Para este calculo deve-se considerar que o ângulo de cada robô será invariável e que o deslocamento de cada robô ocorrerá apenas na reta determinada pelos centros de cada robô.

float dist_overlap_robot_robot(float ra_x, float ra_y, float ra_a, float rb_x, float rb_y, float rb_a);


A função "dist_overlap_robot_ball" tem a mesma finalidade que a anterior entretanto, os objetos em questão são um robô e uma bola.

float dist_overlap_robot_ball(float ra_x, float ra_y, float ra_a, float b_x, float b_y);


float dist_overlap_field_ball(float cx[16], float cy[16], float b_x, float b_y);


float dist_overlap_field_ball(float cx[16], float cy[16], float b_x, float b_y){
      
    float cx2[16],cy2[16],b_x2,b_y2,ang,tg,d;
    int i;

    //deslocando a origem das coordenadas cartesianas para o meio do campo
    for(i=0;i<16;i++){cx2[i]=cx[i]-cx[13]/2; cy2[i]=cy[i]-cy[7]/2;}
    b_x2=b_x-cx[13]/2;
    b_y2=b_y-cy[7]/2;
    
    //tornando as coordenadas x e y positivas, visto que esta
    //consideracao nao interfere no valor fornecido pela funcao
    b_x2=fabs(b_x2);
    b_y2=fabs(b_y2);
    
    //saindo da funcao e retornando valor zero caso se verifique facilmente que a bola
    //se encontra totalmente dentro do campo
    if(b_x2<=cx2[8]+(cx2[9]-cx2[8])/2-BALL_RADIUS&&b_y2<=cy2[9]+(cx2[8]-cx2[9])/2-BALL_RADIUS)
        return(0);
    if(b_x2<=cx2[11]-BALL_RADIUS&&b_y2<=cy2[10]-BALL_RADIUS)
        return(0);
    
    //verificando qual o ponto de interseccao entre o segmento que liga a bola ao meio
    //do campo e as delimitacoes do campo (se esse ponto existir) e qual a distancia
    //necessaria de aproximacao da bola ao meio do campo para que esta nao atravesse as
    //delimitacoes do campo para casos triviais
    if(b_x2<=cx2[8]-BALL_RADIUS&&b_y2>=cy2[8]-BALL_RADIUS){
        py=cy2[8]-BALL_RADIUS;
        px=py*(b_x2/b_y2);
        return(sqrt((b_y2-py)*(b_y2-py)+(b_x2-px)*(b_x2-px)));
    }
    if(b_x2>=cx2[11]-BALL_RADIUS&&b_y2<=cy2[10]-BALL_RADIUS){
        px=cx2[11]-BALL_RADIUS;
        py=px*(b_y2/b_x2);
        return(sqrt((b_y2-py)*(b_y2-py)+(b_x2-px)*(b_x2-px)));
    }
    
    //executando um "offset" para dentro nas linhas que delimitam o campo (lembrando que
    //estamos trabalhando somente com o primeiro quadrante do campo) no tamanho do raio
    //da bola, de forma que ao garantirmos que o centro da bola esteja dentro do campo
    //"offsetado", garantimos que a bola nao atravessa as linhas que delimitam o campo
    tg=(cy2[9]-cy2[8])/(cx2[9]-cx2[8]);
    ang=atan(tg);
    px=cx2[8]+BALL_RADIUS*cos(ang-PI/2);
    py=cy2[8]+BALL_RADIUS*sin(ang-PI/2);
    cy2[8]-=BALL_RADIUS;
    cx2[8]=(cy2[8]-py)/tg+px;
    cx2[9]-=BALL_RADIUS;
    cy2[9]=tg*(cx2[9]-px)+py;
    d=BALL_RADIUS*sqrt(2);
    cx2[10]-=d;
    cy2[10]-=d;
    cx2[11]-=d;
    cy2[11]-=d;
    
    //verificando qual o ponto de interseccao entre o segmento que liga a bola ao meio
    //do campo e as delimitacoes do campo (se esse ponto existir) e qual a distancia
    //necessaria de aproximacao da bola ao meio do campo para que esta nao atravesse as
    //delimitacoes do campo para casos nao-triviais
    if(b_y2>cy2[8]){
        py=cy2[8];
        px=py*(b_x2/b_y2);
        if(px<=cx2[8])return(sqrt((b_y2-py)*(b_y2-py)+(b_x2-px)*(b_x2-px)));
    }
    if(b_x2>cx2[11]){
        px=cx2[11];
        py=px*(b_y2/b_x2);
        if(py>=cy2[11])return(sqrt((b_y2-py)*(b_y2-py)+(b_x2-px)*(b_x2-px)));
    }
    if(b_y2>cy2[9]){
        px=(cy2[8]-tg*cx2[8])/(b_y2/b_x2-tg);
        if(px>cx2[8]&&px<cx2[9]&&px<=b_x2){
            py=px*(b_y2/b_x2);
            return(sqrt((b_y2-py)*(b_y2-py)+(b_x2-px)*(b_x2-px)));
        }
    }
    if(b_x2>=cx2[9]){
        px=cx2[9];
        py=px*(b_y2/b_x2);
        if(py>=cy2[10]&&py<=cy2[9])return(sqrt((b_y2-py)*(b_y2-py)+(b_x2-px)*(b_x2-px)));
    }
    if(b_y2>=cy2[10]){
        py=cy2[10];
        px=py*(b_x2/b_y2);
        if(px>cx2[10]&&px<cx2[11])return(sqrt((b_y2-py)*(b_y2-py)+(b_x2-px)*(b_x2-px)));
    }
    return(0);
}
    
float dist_overlap_field_robot(float cx[16], float cy[16], float ra_x, float ra_y, float ra_a);


float dist_overlap_field_robot(float cx[16], float cy[16], float ra_x, float ra_y, float ra_a){
    
    float cx2[16],cy2[16],vertx[4],verty[4],diagp2,dist=0,px,py,tg;
    int i;

    //calculando a metade da diagonal do robo
    diagp2=(ROBOR_SIDE*sqrt(2))/2;
    
    //deslocando a origem das coordenadas cartesianas para o meio do campo
    for(i=0;i<4;i++){cx2[i]=cx[i+8]-cx[13]/2; cy2[i]=cy[i+8]-cy[7]/2;}
    ra_x2=ra_x-cx[13]/2;
    ra_y2=ra_y-cy[7]/2;
    ra_a2=ra_a;
    if(ra_x<0)ra_a2=PI-ra_a2;
    if(ra_y<0)ra_a2-=2*ra_a2;
    
    //calculando a tangente da reta que liga os pontos c2[8] e c2[9]
    tg=(cy2[1]-cy2[0])/(cx2[1]-cx2[0]);
    
    //tornando as coordenadas x e y positivas, visto que esta
    //consideracao nao interfere no valor fornecido pela funcao
    ra_x=fabs(ra_x);
    ra_y=fabs(ra_y);
    
    //saindo da funcao e retornando valor zero caso se verifique facilmente que o robo
    //se encontra totalmente dentro do campo
    if(ra_x<=cx2[0]+(cx2[1]-cx2[0])/2-diagp2&&ra_y<=cy2[1]+(cx2[0]-cx2[1])/2-diagp2)
        return(0);
    if(ra_x<=cx2[3]-diagp2&&ra_y<=cy2[2]-diagp2)
        return(0);
    
    //armazenando as coordenadas dos vertices do robo
    for(i=0;i<4;i++){
        vertx[i]=ra_x+diagp2*cos(ra_a2+PI/4+i*PI/2);
        verty[i]=ra_y+diagp2*sin(ra_a2+PI/4+i*PI/2);
    }
    
    //tornando as coordenadas dos vertices do robo positivas, visto
    //que esta consideracao nao interfere no valor fornecido pela funcao
    for(i=0;i<4;i++){
        vertx[i]=fabs(vertx[i]);
        verty[i]=fabs(verty[i]);
    }
    
    //verificando qual o ponto de interseccao entre o segmento que liga os vertices do
    //robo ao meio do campo e as delimitacoes do campo (se esse ponto existir) e qual a
    //distancia necessaria de aproximacao do robo ao meio do campo para que este nao
    //atravesse as delimitacoes do campo
    for(i=0;i<4;i++){
        if(verty[i]>=cy2[0]){
            py=cy2[0];
            px=py*(vertx[i]/verty[i]);
            if(px<=cx2[0])if(dist<sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px)))
                               dist=sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px));
        }
        if(vertx[i]>=cx2[3]){
            px=cx2[3];
            py=px*(verty[i]/vertx[i]);
            if(py<=cy2[3])if(dist<sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px)))
                               dist=sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px));
        }
        if(verty[i]>cy2[1]){
            px=(cy2[0]-tg*cx2[0])/(ra_y/ra_x-tg);
            py=px*(ra_y/ra_x);
            
            sqrt((ra_y-py)*(ra_y-py)+(ra_x-px)*(ra_x-px))
            if(px>cx2[0]&&px<cx2[1]&&px<=vertx[i]){
                py=px*(verty[i]/vertx[i]);
                if(dist<sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px)))
                    dist=sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px));
            }
        }
        if(vertx[i]>=cx2[1]){
            px=cx2[1];
            py=px*(verty[i]/vertx[i]);
            if(py>=cy2[2]&&py<=cy2[1])
                if(dist<sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px)))
                    dist=sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px));
        }
        if(verty[i]>=cy2[2]){
            py=cy2[2];
            px=py*(vertx[i]/verty[i]);
            if(px>cx2[2]&&px<cx2[3])
                if(dist<sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px)))
                    dist=sqrt((verty[i]-py)*(verty[i]-py)+(vertx[i]-px)*(vertx[i]-px));
        }
    }
    return(dist);
}
