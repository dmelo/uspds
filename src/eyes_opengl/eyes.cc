/*
    USPDroidsSimulator
    (C) 2007  Diogo Oliveira de Melo
    (C) 2007  Anderson Henrique Constantino Maia
    (C) 2007  João Antônio Angelleti Guimarães

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    src/eyes_opengl/eyes.c
*/

#include"eyes.h"

pthread_mutex_t mutex;


float raio = 0.000001; //guarda o raio da rotação a partir do centro do objeto--> INCRÍVEL: se raio = 0, nao exibe nada na tela
float x[VETOR_TAM][2 * N_JOGADORES_POR_TIME];
float y[VETOR_TAM][2 * N_JOGADORES_POR_TIME];
float a[VETOR_TAM][2 * N_JOGADORES_POR_TIME];
float bx[VETOR_TAM], by[VETOR_TAM];
float altura = ((CAMPO_GOL_PROFUNDIDADE * 2) + CAMPO_LARGURA) / (2 * tanf(M_PI_4 / 2));
float altura0 = ((CAMPO_GOL_PROFUNDIDADE * 2) + CAMPO_LARGURA) / (2 * tanf(M_PI_4 / 2));
float xOBJ = CAMPO_GOL_PROFUNDIDADE + (CAMPO_LARGURA / 2);
float yOBJ = CAMPO_ALTURA / 2;
float zOBJ = 0.0;
float aOBJ = 0.0;
float xCAMPO = CAMPO_GOL_PROFUNDIDADE + (CAMPO_LARGURA / 2);
float yCAMPO = CAMPO_ALTURA / 2;
float zCAMPO = 0.0;
bool freeC = false;
float xfreeC;
float yfreeC;
float zfreeC;
float angfreexy;
float angfreez;
bool onBoard = false;
bool chase = false;
bool cont = true;
int t_visao = 0;
int idOnBoard;
int deltaT = 0;
float xCam = 0.0, yCam = sin(M_PI_4 - 0.5)*altura, zCam = cos(M_PI_4 - 0.5)*altura;
float dx = 0, dy = 0;
float orientacao_robo = 0;
int x_rotate_buffer = +30;
int z_rotate_buffer = 0;
float rotate_m = 0.1;
int msec_w = 19; // tempo de espera por quadro
int msec_p = 14; // tempo que ele leva para processar um quadro.
float vel_jogo = 0.5; // velocidade do jogo.
bool finish = false;


char avifile[400];
Revel_VideoFrame Frame;
bool to_avi = false;
int encoder_handle;

unsigned long int rc = 0; // record counter
unsigned long int sc = 0; // show counter
bool infinity = false;
bool alone = false;
char *hostname = new char[300];

/* joao begin */
const GLfloat luz_ambiente[] = { 0.1f, 0.1f, 0.1f, 1.0f };
const GLfloat luz_difusa[] = { 0.1f, 0.1f, 0.1f, 1.0f };
const GLfloat luz_especular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
const GLfloat luz_posicao0[] = { 0.1f, 0.0f, 2.5f, 0.0f };
const GLfloat luz_posicao1[] = { 0.1f + CAMPO_LARGURA / 2, 0.0f, 2.5f, 0.0f };
const GLfloat luz_posicao2[] = { 0.1f + CAMPO_LARGURA, 0.0f, 2.5f, 0.0f };
const GLfloat luz_posicao3[] = { 0.1f, CAMPO_ALTURA, 2.5f, 0.0f };
const GLfloat luz_posicao4[] = { 0.1f + CAMPO_LARGURA / 2, CAMPO_ALTURA, 2.5f, 0.0f };
const GLfloat luz_posicao5[] = { 0.1f + CAMPO_LARGURA, CAMPO_ALTURA, 2.5f, 0.0f };

const GLfloat mat_ambiente[] = { 0.6f, 0.6f, 0.6f, 1.0f };
const GLfloat mat_difusa[] = { 0.6f, 0.6f, 0.6f, 1.0f };
const GLfloat mat_especular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat brilho[] = { 80.0f };
/* joao end */


float angle_cam = 0;
int connectSocket;

campo *c = new campo();
float c_x[64];
float c_y[64];
float c_z[64];

GLuint face;

GLvoid initGL() {
    glClearColor(0.3, 0.3, 0.3, ALPHA);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
/* joao begin */
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    /* joao begin */
    glLightfv(GL_LIGHT0, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicao0);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT1, GL_POSITION, luz_posicao1);

    glLightfv(GL_LIGHT2, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT2, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT2, GL_POSITION, luz_posicao2);

    glLightfv(GL_LIGHT3, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT3, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT3, GL_POSITION, luz_posicao3);

    glLightfv(GL_LIGHT4, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT4, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT4, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT4, GL_POSITION, luz_posicao4);

    glLightfv(GL_LIGHT5, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT5, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT5, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT5, GL_POSITION, luz_posicao5);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
/* joao end */

/* joao end */

}

void global_init() {
    xCAMPO = CAMPO_GOL_PROFUNDIDADE + (CAMPO_LARGURA / 2);
    yCAMPO = CAMPO_ALTURA / 2;
    zCAMPO = 0.0;
}

void init_scene() {
    int i;
    face = glGenLists(2);

    glNewList(face, GL_COMPILE);
        glBegin(GL_POLYGON);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);
            glVertex3f(1, 1, 0);
            glVertex3f(0, 1, 0);
        glEnd();
    glEndList();

    for(i = 0; i < 32; i++) {
        c_x[i] = c->getX(i % 16);
        c_y[i] = c->getY(i % 16);
        if(i < 16)
            c_z[i] = 0;
        else
            c_z[i] = CAMPO_Z;
    }

    for(i = 32; i < 64; i++) {
        c_x[i] = c_x[i - 32];
        c_y[i] = c_y[i - 32];
        c_z[i] = c_z[i - 32];
    }
    //0
    c_x[32] -= CAMPO_THICK;
    c_x[48] -= CAMPO_THICK;
    c_y[32] -= CAMPO_THICK;
    c_y[48] -= CAMPO_THICK;

    //1
    c_x[33] -= CAMPO_THICK;
    c_x[49] -= CAMPO_THICK;
    c_y[33] -= CAMPO_THICK;
    c_y[49] -= CAMPO_THICK;

    //2
    c_x[34] -= CAMPO_THICK;
    c_x[50] -= CAMPO_THICK;
    c_y[34] -= CAMPO_THICK;
    c_y[50] -= CAMPO_THICK;

    //3
    c_x[35] -= CAMPO_THICK;
    c_x[51] -= CAMPO_THICK;
    c_y[35] -= CAMPO_THICK;
    c_y[51] -= CAMPO_THICK;

    //4
    c_x[36] -= CAMPO_THICK;
    c_x[52] -= CAMPO_THICK;
    c_y[36] += CAMPO_THICK;
    c_y[52] += CAMPO_THICK;

    //5
    c_x[37] -= CAMPO_THICK;
    c_x[53] -= CAMPO_THICK;
    c_y[37] += CAMPO_THICK;
    c_y[53] += CAMPO_THICK;

    //6
    c_x[38] -= CAMPO_THICK;
    c_x[54] -= CAMPO_THICK;
    c_y[38] += CAMPO_THICK;
    c_y[54] += CAMPO_THICK;

    //7
    c_x[39] -= CAMPO_THICK;
    c_x[55] -= CAMPO_THICK;
    c_y[39] += CAMPO_THICK;
    c_y[55] += CAMPO_THICK;

    //8
    c_x[40] += CAMPO_THICK;
    c_x[56] += CAMPO_THICK;
    c_y[40] += CAMPO_THICK;
    c_y[56] += CAMPO_THICK;

    //9
    c_x[41] += CAMPO_THICK;
    c_x[57] += CAMPO_THICK;
    c_y[41] += CAMPO_THICK;
    c_y[57] += CAMPO_THICK;

    //10
    c_x[42] += CAMPO_THICK;
    c_x[58] += CAMPO_THICK;
    c_y[42] += CAMPO_THICK;
    c_y[58] += CAMPO_THICK;

    //11
    c_x[43] += CAMPO_THICK;
    c_x[59] += CAMPO_THICK;
    c_y[43] += CAMPO_THICK;
    c_y[59] += CAMPO_THICK;

    c_x[44] += CAMPO_THICK;
    c_x[60] += CAMPO_THICK;
    c_y[44] -= CAMPO_THICK;
    c_y[60] -= CAMPO_THICK;

    c_x[45] += CAMPO_THICK;
    c_x[61] += CAMPO_THICK;
    c_y[45] -= CAMPO_THICK;
    c_y[61] -= CAMPO_THICK;

    c_x[46] += CAMPO_THICK;
    c_x[62] += CAMPO_THICK;
    c_y[46] -= CAMPO_THICK;
    c_y[62] -= CAMPO_THICK;

    c_x[47] += CAMPO_THICK;
    c_x[63] += CAMPO_THICK;
    c_y[47] -= CAMPO_THICK;
    c_y[63] -= CAMPO_THICK;
}

GLvoid window_display() {
    glMatrixMode(GL_MODELVIEW);
    //reseta-se a visualização e as coordenadas para o sistema REAL.
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(sc % 2 == 1) {
        if(x_rotate_buffer > 0) {
            x_rotate_buffer --;
            rotate('x', 1);
        }
        else if(x_rotate_buffer < 0) {
            x_rotate_buffer++;
            rotate('x', -1);
        }
        if(z_rotate_buffer > 0) {
            z_rotate_buffer --;
            rotate('z', 1);
        }
        else if(z_rotate_buffer < 0) {
            z_rotate_buffer++;
            rotate('z', -1);
        }
    }
    if(t_visao == 2) { // on board
        onBoard = true;
        chase = false;
        xOBJ = x[sc][idOnBoard];
        yOBJ = y[sc][idOnBoard];
        zOBJ = ROBO_ARESTA + 0.1;
        aOBJ = a[sc][idOnBoard];
        altura = 0.1;
    }
    else if(t_visao == 1) {
        onBoard = false;
        chase = true;
        xOBJ = x[sc][idOnBoard];
        yOBJ = y[sc][idOnBoard];
        zOBJ = ROBO_ARESTA;

    }
    else if(t_visao == 0) {
        onBoard = false;
        chase = false;
        xOBJ = xCAMPO;
        yOBJ = yCAMPO;
        zOBJ = zCAMPO;
    }

        if(t_visao < 3) 
        gluLookAt(xOBJ + ((1 - onBoard) * (xCam * (altura / altura0))) - (onBoard * 3 * cos(aOBJ) * ROBO_ARESTA), yOBJ + ((1 - onBoard) * (yCam * (altura / altura0))) - (onBoard * sin(aOBJ) * 3 * ROBO_ARESTA), zOBJ + ((1 - onBoard) * (zCam * (altura / altura0))),  xOBJ + (onBoard * cos(aOBJ)), yOBJ + (onBoard * sin(aOBJ)), zOBJ - (onBoard * 0.1),  ((1 - onBoard) * -xCam/altura), ((1 - onBoard) * -yCam/altura), ((1 - onBoard) * zCam / altura) + onBoard);
    else 
        gluLookAt(xfreeC, yfreeC, zfreeC, xfreeC + (cos(angfreexy)*cos(angfreez)), yfreeC + (sin(angfreexy)*cos(angfreez)), zfreeC + sin(angfreez), 0, 0, 1);


    if(sc == 0) 
        animation();
    else
        render_scene();
    glutSwapBuffers();
}

GLvoid window_reshape(GLsizei width, GLsizei height) {
    if(height == 0)
        height = 1;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLdouble)width / (GLdouble)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void sair() {
    pthread_mutex_lock(&mutex);
    close(connectSocket);
    pthread_mutex_unlock(&mutex);
}

void rotate(char axis, int passo) {
    float n_xCam, n_yCam, n_zCam, incremento = (passo * M_PI) / 180;
    switch(axis)
    {
        case 'x':
            n_yCam = (cos(incremento)*yCam) + (sin(incremento)*zCam);
            n_zCam = (cos(incremento)*zCam) - (sin(incremento)*yCam);
            yCam = n_yCam;
            zCam = n_zCam;
            break;
        case 'z':
            n_xCam = (cos(incremento)*xCam) + (sin(incremento)*yCam);
            n_yCam = (cos(incremento)*yCam) - (sin(incremento)*xCam);
            xCam = n_xCam;
            yCam = n_yCam;
            break;

    }
    glutPostRedisplay();
}


void robo(int id, float px, float py, float ang)
{
    static GLUquadric* quadric = gluNewQuadric(); //para poder gerar o cilindro

    ang = ang*180/M_PI;//altera o ang de radianos para graus
    
    /*construção do cubo face a face*/ 
    glPushMatrix();

       glTranslatef(px, py, ROBO_ARESTA/2);
         glScalef(ROBO_ARESTA/2, ROBO_ARESTA/2, ROBO_ARESTA/2);

         glRotatef(ang, 0.0, 0.0, 1.0);
       glRotatef(90, 1.0, 0.0, 0.0);//muda para o eixo xy



        /*face superior do cubo*/
        glBegin(GL_POLYGON);
            if(id <= 2)               //define a cor do time de acordo com o id do robo
               glColor3f(AZUL);                    
            else
               glColor3f(AMARELO)   ;
               
            glVertex3f( 1.0f,   1.0f, -1.0f);            
            glVertex3f( 0.5f, 1.0f, -1.0f);
            glVertex3f( -1.0f,  1.0f, 0.5f); 
            glVertex3f(-1.0f, 1.0f, 1.0f);                
            glVertex3f( -0.5f, 1.0f, 1.0f);
            glVertex3f( 1.0f, 1.0f, -0.5f);
        glEnd();
        

        glBegin(GL_TRIANGLES);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, 1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, 0.5f);
            
            switch(id % 3)
            {
                case 0: glColor3f(VERMELHO);
                        break;
                case 1: glColor3f(VERDE);
                        break;
                case 2: glColor3f(CYAN);
                        break;
            }            
                        
                        
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -0.5f);
            glVertex3f(-0.5f, 1.0f, 1.0f);
        
        glEnd();
        

        /*desenha as outras faces do cubo*/
        glBegin(GL_QUADS);                                    
            glColor3f(0.4f, 0.4f, 0.4f);
            glVertex3f( 1.0f,-1.0f, 1.0f);                    // Top Right Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f, 1.0f);                    // Top Left Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f,-1.0f);                    // Bottom Left Of The Quad (Bottom)
            glVertex3f( 1.0f,-1.0f,-1.0f);                    // Bottom Right Of The Quad (Bottom)
        
            glColor3f(0.4f, 0.4f, 0.4f);
            glVertex3f( 1.0f, 1.0f, 1.0f);                    // Top Right Of The Quad (Front)
            glVertex3f(-1.0f, 1.0f, 1.0f);                    // Top Left Of The Quad (Front)
            glVertex3f(-1.0f,-1.0f, 1.0f);                    // Bottom Left Of The Quad (Front)
            glVertex3f( 1.0f,-1.0f, 1.0f);                    // Bottom Right Of The Quad (Front)
        
            glColor3f(0.4f, 0.4f, 0.4f);
            glVertex3f( 1.0f,-1.0f,-1.0f);                    // Top Right Of The Quad (Back)
            glVertex3f(-1.0f,-1.0f,-1.0f);                    // Top Left Of The Quad (Back)
            glVertex3f(-1.0f, 1.0f,-1.0f);                    // Bottom Left Of The Quad (Back)
            glVertex3f( 1.0f, 1.0f,-1.0f);                    // Bottom Right Of The Quad (Back)
        
            glColor3f(0.2f, 0.2f, 0.2f);
            glVertex3f(-1.0f, 1.0f, 1.0f);                    // Top Right Of The Quad (Left)
            glVertex3f(-1.0f, 1.0f,-1.0f);                    // Top Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f,-1.0f);                    // Bottom Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f, 1.0f);                    // Bottom Right Of The Quad (Left)
            
            glColor3f(0.2f, 0.2f, 0.2f);
            glVertex3f( 1.0f, 1.0f,-1.0f);                    // Top Right Of The Quad (Right)
            glVertex3f( 1.0f, 1.0f, 1.0f);                    // Top Left Of The Quad (Right)
            glVertex3f( 1.0f,-1.0f, 1.0f);                    // Bottom Left Of The Quad (Right)
            glVertex3f( 1.0f,-1.0f,-1.0f);                    // Bottom Right Of The Quad (Right)
        glEnd();
        

    /*desenho do cone ("eixo" das rodas)*/
    glPushMatrix();
      glColor3f(0, 0, 0);
      glTranslatef(0, -0.5, -1.125);
      gluCylinder(quadric, 0.5, 0.5, 2.25, 30, 30);
    glPopMatrix();

   /*calota da roda esquerda*/
   glPushMatrix();
      glColor3f(0.8, 0.8, 0.8);
      glTranslatef(0, -0.5, 1.125);
      glutSolidCone(0.5, 0.05, 30, 30 );
   glPopMatrix();

   /*calota da roda direita*/
   glPushMatrix();
      glColor3f(0.8, 0.8, 0.8);
      glTranslatef(0, -0.5, -1.125);
      glScalef(1, 1, -1);
      glutSolidCone(0.5, 0.05, 30, 30 );
   glPopMatrix();

   glPopMatrix();    


}

void animation() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    d_campo();
    if(rc >0)
        sc++;
    glPopMatrix();

}

void render_scene() {
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    
    if(infinity) {
        sc = rc - 1;
        if(sc == -1)
            sc = VETOR_TAM - 1;
        
    }
    else {
        while((sc >= rc)&&(sc >0))
            sc--;
    }
    d_campo();
    pthread_mutex_lock(&mutex);
    for(i = 0; i < 2 * N_JOGADORES_POR_TIME; i++) {
        robo(i, x[sc][i], y[sc][i], a[sc][i]);
    }
    bola(bx[sc], by[sc]);
    if(sc < rc)
        sc += cont;
    if((deltaT < 0)&&(sc > 1)) {
        sc -= (1+cont);
        deltaT++;
    }
    if((deltaT > 0)&&(sc < rc)) {
        sc++;
        deltaT--;
    }

    glPopMatrix();

    if(to_avi) {
	int frameSize;
	glReadPixels(0, 0, WIDTH, HEIGHT, GL_ABGR_EXT, GL_UNSIGNED_INT_8_8_8_8, Frame.pixels);
	for(int i = 0; i < (HEIGHT * WIDTH) / 2; i++)
	    swap(((int *) Frame.pixels)[i], ((int *) Frame.pixels)[(HEIGHT * WIDTH) - 1 - i]);
	Revel_EncodeFrame(encoder_handle, &Frame, &frameSize);
	printf("framesize: %d. realsize: %d\n", frameSize, WIDTH * HEIGHT * 4);
    }
    pthread_mutex_unlock(&mutex);


}

void Timer(int value) {
    //render_scene();
    window_display();
    glutSwapBuffers();
    glutTimerFunc(19 + (int) (((1/vel_jogo) - (float)1) * 33), Timer, 1);
}

void circulo(float x, float y, float z, float raio) {
    int n_lados = 100;
    float inc = (2 * M_PI) / ((float) n_lados);
    float angulo = 0;

    glBegin(GL_POLYGON);
    for(int i = 0; i < n_lados; i++) {
        glVertex3f(x + (cos(angulo) * raio), y + (sin(angulo) * raio), z);
        angulo += inc;
    }
    glEnd();
}

void cruz(float x, float y, float z) {
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
        glVertex3f(x - (CAMPO_LINE_THICK / 2), y + 0.025, z);
        glVertex3f(x + (CAMPO_LINE_THICK / 2), y + 0.025, z);
        glVertex3f(x + (CAMPO_LINE_THICK / 2), y - 0.025, z);
        glVertex3f(x - (CAMPO_LINE_THICK / 2), y - 0.025, z);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(x - 0.025, y - (CAMPO_LINE_THICK / 2), z);
        glVertex3f(x + 0.025, y - (CAMPO_LINE_THICK / 2), z);
        glVertex3f(x + 0.025, y + (CAMPO_LINE_THICK / 2), z);
        glVertex3f(x - 0.025, y + (CAMPO_LINE_THICK / 2), z);
    glEnd();
}

void free_ball(float x, float y, float z) {
    glColor3f(1, 1, 1);
    circulo(x, y, z, 0.005 + CAMPO_LINE_THICK);
    glColor3f(0.5, 0.5, 0.5);
    circulo(x, y, z + 0.001, 0.01);
}

void d_campo() {
    int i;

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
        glVertex3f(-CAMPO_THICK, -CAMPO_THICK, 0);
        glVertex3f((2 * CAMPO_GOL_PROFUNDIDADE) + CAMPO_LARGURA + CAMPO_THICK, -CAMPO_THICK, 0);
        glVertex3f((2 * CAMPO_GOL_PROFUNDIDADE) + CAMPO_LARGURA + CAMPO_THICK, CAMPO_ALTURA + CAMPO_THICK, 0);
        glVertex3f(-CAMPO_THICK, CAMPO_ALTURA + CAMPO_THICK, 0);
    glEnd();    
    
    glColor3f(1, 1, 1);
    
    //linha central.
    glBegin(GL_POLYGON);
        glVertex3f((c_x[0] + c_x[15] - CAMPO_LINE_THICK) / 2, 0, 0.003);
        glVertex3f((c_x[0] + c_x[15] + CAMPO_LINE_THICK) / 2, 0, 0.003);
        glVertex3f((c_x[0] + c_x[15] + CAMPO_LINE_THICK) / 2, c_y[7], 0.003);
        glVertex3f((c_x[0] + c_x[15] - CAMPO_LINE_THICK) / 2, c_y[7], 0.003);
    glEnd();
    //linhas laterais
    glBegin(GL_POLYGON);
        glVertex3f(c_x[2] - CAMPO_LINE_THICK, c_y[2], 0.001);
        glVertex3f(c_x[2], c_y[2], 0.001);
        glVertex3f(c_x[5], c_y[5], 0.001);
        glVertex3f(c_x[5] - CAMPO_LINE_THICK, c_y[5], 0.001);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[13] + CAMPO_LINE_THICK, c_y[13], 0.001);
        glVertex3f(c_x[13], c_y[13], 0.001);
        glVertex3f(c_x[10], c_y[10], 0.001);
        glVertex3f(c_x[10] + CAMPO_LINE_THICK, c_y[10], 0.001);
    glEnd();

    //grande área
    glBegin(GL_POLYGON);
        glVertex3f(c_x[2], c_y[2] - 0.15, 0.001);
        glVertex3f(c_x[2], c_y[2] - 0.15 - CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[2] + 0.15 + CAMPO_LINE_THICK, c_y[2] - 0.15 - CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[2] + 0.15 + CAMPO_LINE_THICK, c_y[2] - 0.15, 0.001);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[5], c_y[5] + 0.15, 0.001);
        glVertex3f(c_x[5], c_y[5] + 0.15 + CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[5] + 0.15 + CAMPO_LINE_THICK, c_y[5] + 0.15 + CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[5] + 0.15 + CAMPO_LINE_THICK, c_y[5] + 0.15, 0.001);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[5] + 0.15, c_y[5] + 0.15, 0.001);
        glVertex3f(c_x[5] + 0.15 + CAMPO_LINE_THICK, c_y[5] + 0.15, 0.001);
        glVertex3f(c_x[2] + 0.15 + CAMPO_LINE_THICK, c_y[2] - 0.15, 0.001);
        glVertex3f(c_x[2] + 0.15, c_y[2] - 0.15, 0.001);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[13], c_y[13] - 0.15, 0.001);
        glVertex3f(c_x[13], c_y[13] - 0.15 - CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[13] - 0.15 - CAMPO_LINE_THICK, c_y[13] - 0.15 - CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[13] - 0.15 - CAMPO_LINE_THICK, c_y[13] - 0.15, 0.001);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[10], c_y[10] + 0.15, 0.001);
        glVertex3f(c_x[10], c_y[10] + 0.15 + CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[10] - 0.15 - CAMPO_LINE_THICK, c_y[10] + 0.15 + CAMPO_LINE_THICK, 0.001);
        glVertex3f(c_x[10] - 0.15 - CAMPO_LINE_THICK, c_y[10] + 0.15, 0.001);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[10] - 0.15, c_y[10] + 0.15, 0.001);
        glVertex3f(c_x[10] - 0.15 - CAMPO_LINE_THICK, c_y[10] + 0.15, 0.001);
        glVertex3f(c_x[13] - 0.15 - CAMPO_LINE_THICK, c_y[13] - 0.15, 0.001);
        glVertex3f(c_x[13] - 0.15, c_y[13] - 0.15, 0.001);
    glEnd();

    //circunferência central
    glColor3f(0.1, 0.1, 0.1);
    circulo((c_x[7] + c_x[8]) / 2, c_y[7] / 2, 0.002, 0.2);
    circulo(c_x[2] + 0.075, (c_y[2] + c_y[5]) / 2, 0.00015, 0.125);
    circulo(c_x[13] - 0.075, (c_y[2] + c_y[5]) / 2, 0.00015, 0.125);


    glBegin(GL_POLYGON);
        glVertex3f(c_x[5], c_y[5], 0.0002);
        glVertex3f(c_x[5] + 0.15, c_y[5], 0.0002);
        glVertex3f(c_x[5] + 0.15, c_y[2], 0.0002);
        glVertex3f(c_x[5], c_y[2], 0.0002);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[4], c_y[4], 0.0002);
        glVertex3f(c_x[5] - CAMPO_LINE_THICK, c_y[5], 0.0002);
        glVertex3f(c_x[5] - CAMPO_LINE_THICK, c_y[2], 0.0002);
        glVertex3f(c_x[4], c_y[2], 0.0002);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[10], c_y[10], 0.0002);
        glVertex3f(c_x[10] - 0.15, c_y[10], 0.0002);
        glVertex3f(c_x[10] - 0.15, c_y[13], 0.0002);
        glVertex3f(c_x[10], c_y[13], 0.0002);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(c_x[11], c_y[11], 0.0002);
        glVertex3f(c_x[10] + CAMPO_LINE_THICK, c_y[10], 0.0002);
        glVertex3f(c_x[10] + CAMPO_LINE_THICK, c_y[13], 0.0002);
        glVertex3f(c_x[11], c_y[13], 0.0002);
    glEnd();

    glColor3f(1, 1, 1);
    circulo((c_x[7] + c_x[8]) / 2, c_y[7] / 2, 0.001, 0.2 + CAMPO_LINE_THICK);
    circulo(c_x[2] + 0.075, (c_y[2] + c_y[5]) / 2, 0.0001, 0.125 + CAMPO_LINE_THICK);
    circulo(c_x[13] - 0.075, (c_y[2] + c_y[5]) / 2, 0.0001, 0.125 + CAMPO_LINE_THICK);

    float x_cruz = c_x[2] + 0.375;
    float y_cruz = c_y[0] + 0.25;

    for(int i = 0; i < 3; i++) {
        cruz(x_cruz, y_cruz, 0.0002);
        cruz(x_cruz + 0.75, y_cruz, 0.0002);
        if(i != 1) {
            free_ball(x_cruz - 0.2, y_cruz, 0.0002);
            free_ball(x_cruz + 0.2, y_cruz, 0.0002);
            free_ball(x_cruz - 0.2 + 0.75, y_cruz, 0.0002);
            free_ball(x_cruz + 0.2 + 0.75, y_cruz, 0.0002);
        }
        y_cruz += 0.4;
    }

    
        

    for(i = 0; i < 16; i++) {
        int a = i;
        int b = (i + 1) % 16;
        int c = ((i + 1) % 16) + 16;
        int d = (i + 16);
        int e = i + 48;
        int f = i + 32;
        int g = ((i + 1) % 16) + 32;
        int h = ((i + 1) % 16) + 48;

        //faces internas das laterais.
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
            glVertex3f(c_x[a], c_y[a], c_z[a]);
            glVertex3f(c_x[b], c_y[b], c_z[b]);
            glVertex3f(c_x[c], c_y[c], c_z[c]);
            glVertex3f(c_x[d], c_y[d], c_z[d]);
        glEnd();

        //faces superiores das barras laterais.
        glColor3f(0.2, 0.2, 0.2);    
        glBegin(GL_POLYGON);
            glVertex3f(c_x[d], c_y[d], c_z[d]);
            glVertex3f(c_x[c], c_y[c], c_z[c]);
            glVertex3f(c_x[h], c_y[h], c_z[h]);
            glVertex3f(c_x[e], c_y[e], c_z[e]);
        glEnd();

        //faces externas das barras laterais.
        glBegin(GL_POLYGON);
            glVertex3f(c_x[e], c_y[e], c_z[e]);
            glVertex3f(c_x[f], c_y[f], c_z[f]);
            glVertex3f(c_x[g], c_y[g], c_z[g]);
            glVertex3f(c_x[h], c_y[h], c_z[h]);
        glEnd();
    }



}


void bola(float px, float py) {
    glPushMatrix();
        glTranslatef(px, py, BOLA_RAIO);
        glColor3f(LARANJA);
        glutSolidSphere(BOLA_RAIO, 32, 32);
    glPopMatrix();

}

static void window_key(unsigned char key, int x, int y) {
    switch(key) {
        case 'V':
            vel_jogo += 0.1;
            break;
        case 'v':
            vel_jogo -= 0.1;
            break;
        case 'z':
            z_rotate_buffer--;
            break;
        case 'Z':
            z_rotate_buffer++;
            break;
        case 'x':
            x_rotate_buffer--;
            break;
        case 'X':
            x_rotate_buffer++;
            break;
        case '+':
            altura -= 0.05;
            break;
        case '-':
            altura += 0.05;
            break;
        case 'q':
            //system("sh terminar.sh");
            finish = true;
            break;
        case 'o':
            t_visao = 2;
            idOnBoard ++;
            idOnBoard = idOnBoard % 6;
            onBoard = true;
            chase = false;
            freeC = false;
            break;
        case 'O':
            t_visao = 0;
            onBoard = false;
            chase = false;
            freeC = false;
            altura = altura0;
            global_init();
            break;
        case 'c':
            t_visao = 1;
            idOnBoard++;
            idOnBoard = idOnBoard % 6;
            chase = true;
            onBoard = false;
            freeC = false;
            break;
        case 'C':
            t_visao = 0;
            chase = false;
            onBoard = false;
            freeC = false;
            altura = altura0;
            global_init();
            break;
        case 'f':
            t_visao = 3;
            freeC = true;
            chase = false;
            onBoard = false;
            xfreeC = xCAMPO;
            yfreeC = -1;
            zfreeC = +0.8;
            angfreexy = M_PI_2;
            angfreez = -0.5;
            break;
        case 'F':
            t_visao = 0;
            freeC = false;
            chase = false;
            onBoard = false;
            global_init();
            break;
        case 'p':
            if(cont == true)
                cont = false;
            else
                cont = true;
            break;
        case 's':
            pthread_mutex_lock(&mutex);
            sc = 1;
            pthread_mutex_unlock(&mutex);
            break;
        case 'u':
            xfreeC += cos(angfreez) * cos(angfreexy) * 0.05;
            yfreeC += cos (angfreez) * sin(angfreexy) * 0.05;
            zfreeC += sin(angfreez) * 0.05;
            break;
        case 'j':
            xfreeC -= cos(angfreez) * cos(angfreexy) * 0.05;
            yfreeC -= cos(angfreez) * sin(angfreexy) * 0.05;
            zfreeC -= sin(angfreez) * 0.05;
            break;
        case 'k':
            angfreexy -= 0.03;
            break;
        case 'h':
            angfreexy += 0.03;
            break;
        case 'y':
            angfreez += 0.03;
            break;
        case 'b':
            angfreez -= 0.03;
            break;
        case ',':
            if(deltaT >= -30)
                deltaT -=5;
            break;
        case '.':
            if(deltaT <= 30)
                deltaT +=5;
            break;


        



            
    }
}

void *opengl_main(void *p) {
    int argc = 0;
    char **argv = NULL;


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_WINDOW_RGBA);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Eyes");

    glutDisplayFunc(&window_display);
    glutReshapeFunc(&window_reshape);
    glutKeyboardFunc(&window_key);

    glutTimerFunc(0, Timer, 1);
    initGL();
    init_scene();
/* joao begin */
    glLightfv(GL_LIGHT0, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicao0);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT1, GL_POSITION, luz_posicao1);

    glLightfv(GL_LIGHT2, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT2, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT2, GL_POSITION, luz_posicao2);

    glLightfv(GL_LIGHT3, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT3, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT3, GL_POSITION, luz_posicao3);

    glLightfv(GL_LIGHT4, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT4, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT4, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT4, GL_POSITION, luz_posicao4);

    glLightfv(GL_LIGHT5, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT5, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT5, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT5, GL_POSITION, luz_posicao5);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
/* joao end */

    glutMainLoop();
}

void record_avi_start(char *filename) {

    pthread_mutex_lock(&mutex);

    Revel_CreateEncoder(&encoder_handle);
    strcpy(avifile, filename);
    Revel_Params revParams;
    Revel_InitializeParams(&revParams);
    revParams.width = WIDTH;
    revParams.height = HEIGHT;
    revParams.frameRate = 30.0f;
    revParams.quality = 1.0f;
    revParams.codec = REVEL_CD_XVID;
    revParams.hasAudio = 0;

    Revel_EncodeStart(encoder_handle, avifile, &revParams);

    Frame.width = WIDTH;
    Frame.height = HEIGHT;
    Frame.bytesPerPixel = 4;
    Frame.pixelFormat = REVEL_PF_RGBA;
    Frame.pixels = new int[WIDTH * HEIGHT];
    memset(Frame.pixels, 0, WIDTH * HEIGHT * 4);
    /*
    int frameSize;
    for(int i = 0; i < 50; i++) {
	for(int j = 0; j < WIDTH; j++) {
	    for(int k = 0; k < HEIGHT; k++) {
		((int *) Frame.pixels)[(j * WIDTH) + k] = 0x0ff0 + (0x0010 * i);
	    }
	}
	Revel_EncodeFrame(encoder_handle, &Frame, &frameSize);
	printf("%d %d\n", i, frameSize);
    }*/
    to_avi = true;

    pthread_mutex_unlock(&mutex);
}

// Function to load a sound file for the sample movie's audio track.
// Once again, this is completely unrelated to using Revel, so don't
// worry about understanding it fully.
void LoadAudio(bool *hasAudio, int *audioBits, int *audioChannels,
               int *audioFormat, int *audioRate, char **audioBuffer,
               int *audioBufferSize)
{
    // chimes.raw is raw sample data.  The details of its sample format are
    // hard-coded into this file, so that I don't have to clutter
    // up the example code with a WAV-loading function.
    // ENDIAN ISSUE: chimes.raw is stored in little-endian format.  Running
    // this code on a big-endian system won't crash, but the audio will sound
    // pretty awful.  You've been warned!
    const char *audioFilename = "chimes.raw";
    *audioBits = 16;
    *audioChannels = 2;
    *audioFormat = REVEL_ASF_PCM;
    *audioRate = 22050;
    *hasAudio = false;
    FILE *audioFile = fopen(audioFilename, "rb");
    if (audioFile != NULL)
    {
        fseek(audioFile, 0, SEEK_END);
        *audioBufferSize = ftell(audioFile);
        fseek(audioFile, 0, SEEK_SET);
        *audioBuffer = new char[*audioBufferSize];
        *hasAudio = (fread(*audioBuffer, 1, *audioBufferSize, audioFile) == *audioBufferSize);
        fclose(audioFile);
    }
    
}

void record_avi_stop() {
    to_avi = false;
    int total_size, audioBits, audioChannels, audioFormat, audioRate, audioBufferSize, totalAudioBytes;
    char *audioBuffer = NULL;
    bool hasAudio = false;
    LoadAudio(&hasAudio, &audioBits, &audioChannels, &audioFormat, &audioRate, &audioBuffer, &audioBufferSize);
    Revel_EncodeAudio(encoder_handle, audioBuffer, audioBufferSize, &totalAudioBytes);
    Revel_EncodeAudio(encoder_handle, audioBuffer, audioBufferSize, &totalAudioBytes);
    Revel_EncodeEnd(encoder_handle, &total_size);
    Revel_DestroyEncoder(encoder_handle);
    printf("total_size: %d.\n", total_size);
}

void *receve(void *p) {
    bool recever_ok = false;
    printf("modo receve ativado.\n");
    int socketEyes;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    struct hostent * hostInfo;
    socklen_t clientAddressLength;

    hostInfo = gethostbyname(hostname);
    if(hostname == NULL) {
	cerr << "Eyes: error: Cannot resolv the name " << hostname << endl;
	exit(1);
    }

    socketEyes = socket(AF_INET, SOCK_STREAM, 0);
    if(socketEyes < 0) {
	printf("erro: não pode criar socket.\n");
	exit(1);
    }

    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
    serverAddress.sin_port = htons(PORTA_GUI);
    if(connect(socketEyes, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
	cerr << "Eyes: error: Cannot connect to Simulator." << endl;
	exit(1);
    }

    printf("conectado! :D\n");
    pthread_mutex_lock(&mutex);
    rc = 0;
    sc = 0;
    pthread_mutex_unlock(&mutex);
    while(true) { // qual é a condição pra saber se ainda tem conexão???
        objeto::sleep2(29);
        int tamanho = 12 + (2 * 18 * N_JOGADORES_POR_TIME);
        
        char *msn = new char[tamanho];
	if(finish) {
	    close(socketEyes);
	    return NULL;
	}

        if(recv(socketEyes, msn, tamanho, MSG_DONTWAIT) != -1) {
            read_coordinates(msn);
        }

        delete []msn;
    }
}

void record_file(char *name) {
    string m;
    char filename[200];
    FILE *f;

    strcpy(filename, "uds/");
    strcat(filename, name);
    if((f = fopen(filename, "w")) == NULL) {
        printf("erro: não foi possível criar o arquivo .uds.\n");
        return;
    }

    fprintf(f, "#\n#\n#\n"); // espaço para comentários.
    for(int i = 0; i < rc; i++) {
        pthread_mutex_lock(&mutex);
        m = protocolo::encode(bx[i], by[i], N_JOGADORES_POR_TIME, x[i], y[i], a[i]);
        fputs(m.data(), f);
        pthread_mutex_unlock(&mutex);
    }

    fclose(f);
}

void read_coordinates(char *coordinates) {
    if((!infinity)&&(rc < VETOR_TAM)) {
        pthread_mutex_lock(&mutex);
        protocolo::decode(coordinates, &(bx[rc]), &(by[rc]), (float *) x[rc], (float *) y[rc], (float *) a[rc]);
        rc++;
        pthread_mutex_unlock(&mutex);
    }
    else {
        pthread_mutex_lock(&mutex);
        protocolo::decode(coordinates, &(bx[rc]), &(by[rc]), (float *) x[rc], (float *) y[rc], (float *) a[rc]);
        rc++;
        if(rc == VETOR_TAM)
            rc = 1;
        pthread_mutex_unlock(&mutex);
    }
}
    

void get_arq(char *filename) {
    FILE *f;
    int i;
    char *comments;
    char coordinates[300];
    if((f = fopen(filename, "r")) == NULL) {
            printf("erro: não foi possível abrir o arquivo %s.\n", filename);
        return;
    }

    comments = new char[300];
    
    //for(i = 0; (comments[i][0] == '#')&&(i < 50); i++) //Conferir se ele compara antes de incrementar...
    //    fgets(comments[i], 99, f);
    comments[0] = '#';
    while(comments[0] == '#')
        fgets(comments, 298, f);
    pthread_mutex_lock(&mutex);
    rc = 0;
    sc = 0;
    pthread_mutex_unlock(&mutex);

    while(fgets(coordinates, 298, f) != NULL) {
        read_coordinates(coordinates);
    }

    delete []comments;
}

void *command() {
    char comando[200];
    char prompt[90], mode[40], apend[40], c_mode[20];
    int state = 0;

    strcpy(mode, "");
    strcpy(c_mode, "");
    strcpy(apend, "user@uspdroids:~/$ ");
    usleep(1000);
    printf("\n\n\nUspDroidSimulator: Be welcome. I'm on the way.\n\n");
    usleep(1000);
    while(true) {
        printf("%s%s%s", mode, c_mode, apend);
        strcpy(comando, "");
        fgets(comando, 200, stdin);
        char cmd[200];
        sscanf(comando, " %s ", cmd);

        // comando para sair.
        if(strcmp(cmd, "exit") == 0) {
            //system("sh terminar.sh");
            finish = true;
            return NULL;
        }

        //comando save
        if(strcmp(cmd, "save") == 0) {
            char filename[200];

            sscanf(comando, " %s %s ", cmd, filename);
            record_file(filename);
            continue;
        }


	if(strcmp(cmd, "saveavi") == 0) {
	    char filename[200];
	    char state[200];

	    sscanf(comando, " %s %s %s ", cmd, state, filename);
	    if(strcmp(state, "start") == 0)
		record_avi_start(filename);
	    else if(strcmp(state, "stop") == 0)
		record_avi_stop();
	}
    
        if((strcmp(cmd, "ls") == 0)||(strcmp(cmd, "ls") == 0)) {
            FILE *f;
            
            system("sh makelist.sh");
            if((f = fopen("list.txt", "r")) == NULL) {
                printf("erro: não foi possivel listar os arquivos.\n");
                continue;
            }
            char arqname[200];
            while(fgets(arqname, 198, f) != NULL)
                printf("%s", arqname);
            continue;
        }

        if(strcmp(cmd, "load") == 0) {
            char name[200];
            char filename[200];

            sscanf(comando, " %s %s ", cmd, name);
            strcpy(filename, "uds/");
            strcat(filename, name);
            get_arq(filename);
            continue;
        }

        if(strcmp(cmd, "time") == 0) {
            int min, sec;
            int frame;
            int ac = sscanf(comando, " %s %d:%d ", cmd, &min, &sec);
            
            if(ac == 3) {
                sec += (60 * min);
                frame = sec * N_QUADROS_POR_SEGUNDO;
                pthread_mutex_lock(&mutex);
                if(rc >= frame)
                    sc = frame;
                else
                    printf("there are only %d mins and %d seconds recorded.\n", rc/(N_QUADROS_POR_SEGUNDO*60), (rc / N_QUADROS_POR_SEGUNDO) % 60);
                pthread_mutex_unlock(&mutex);
            }
            if(ac == 1)
                printf("sc: %d. rc: %d.\ntime: %d:%d | %d:%d.\n", sc, rc, sc / (60 * N_QUADROS_POR_SEGUNDO), (sc / N_QUADROS_POR_SEGUNDO) % 60,  rc / (60 * N_QUADROS_POR_SEGUNDO), (rc / N_QUADROS_POR_SEGUNDO) % 60);

            continue;
        }

        if((strcmp(cmd, "X") == 0)||(strcmp(cmd, "x") == 0)||(strcmp(cmd, "X\n") == 0)||(strcmp(cmd, "x\n") == 0)||
            (strcmp(cmd, "Y") == 0)||(strcmp(cmd, "y") == 0)||(strcmp(cmd, "Y\n") == 0)||(strcmp(cmd, "y\n") == 0)||
            (strcmp(cmd, "Z") == 0)||(strcmp(cmd, "z") == 0)||(strcmp(cmd, "Z\n") == 0)||(strcmp(cmd, "z\n") == 0)) {

            int passos;

            if(sscanf(comando, " %s %d ", cmd, &passos) == 2) {
                float aux_angulo = ((float)passos) / ((float)360 / (2 * M_PI));
                printf(" %c %d <-- .\n", cmd[0], passos);
                if((cmd[0] == 'x')||(cmd[0] == 'X'))
                    x_rotate_buffer -= passos;
                if((cmd[0] == 'z')||(cmd[0] == 'Z'))
                    z_rotate_buffer -= passos;
            }

            continue;
        }
        if((strcmp(cmd, "vel") == 0)||(strcmp(cmd, "vel\n") == 0)) {
            float n_vel;

            if(sscanf(comando, " %s %f ", cmd, &n_vel) == 2) {
                vel_jogo = n_vel;
            }
            else {
                printf("velocidade: %.1fx.\n", vel_jogo);
            }
            continue;
        }

        if(strcmp(cmd, "break") == 0) {
            char file_name[100];
            if(sscanf(comando, " %s %s ", cmd, file_name) == 2) {
                record_file(file_name);
                usleep(50000);
                sair();
                system("sh break.sh");
            }

            continue;
        }

        /*if(strcmp(comd, "zoom") == 0) {
            char mode[40];
            int p;

            if(sscanf(comando, " %s %s %d ", cmd, mode, &p) == 3) {
                tamanho = */
    }        
}

int main(int argc, char **argv) {
    pthread_attr_t attr;
    pthread_mutex_init(&mutex, NULL);
    pthread_t opengl_t, receve_t, get_arq_t, command_t;
    int status;
    int hostnamepos = 0;
    void *p;
    for(int i = 1; i < argc; i++) {
        if(strcmp("--alone", argv[i]) == 0) {
            printf("modo: alone.\n");
            alone = true;
        }
        if(strcmp("--infinity", argv[i]) == 0) {
            printf("modo: infinity.\n");
            infinity = true;
        }
    }

    hostnamepos = infinity + alone + 1;

    strcpy(hostname, argv[hostnamepos]);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&opengl_t, NULL, (void*(*)(void*))opengl_main, NULL);
    if(!alone)
        pthread_create(&receve_t, NULL, (void*(*)(void*))receve, NULL);
    pthread_create(&command_t, NULL, (void*(*)(void*))command, NULL);

    while(true) {
        sleep(1);
        if(finish)
            return 0;
    }

    pthread_join(opengl_t, (void **) &status);
    if(!alone)
        pthread_join(receve_t, (void **) &status);
    pthread_join(command_t, (void **) &status);

    return 0;
}
