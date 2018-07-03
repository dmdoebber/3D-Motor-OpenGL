    #include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <string>

#include "Frames.h"
#include "virabrequim.h"
#include "biela.h"
#include "pistao.h"
#include "ponto.h"
#include "camera.h"

#define PI_2 6.28318531

#define SCREEN_X 1280
#define SCREEN_Y 720

int   polygonMode = 1;

float rx = 0, rz = 0;

float RPM = 0;
float FPS = 500;

float angR = 0.0;
float ang = 0.0;
float inc = 0.0;
float tam_biela = 2.0;

Frames *frames;

virabrequim vira;

biela biela1;
biela biela2;

pistao pistao1;
pistao pistao2;

camera cam;

GLfloat mat_specular[] = { 1, 1, 1, 1 };
GLint mat_shininess = 10;

GLfloat mat_pistao[] = {0, 0, 0, 1};
GLfloat mat_biela[] = {1, 0, 0, 1};

GLfloat light_0_position[] = { 50, 50, 10, 1};
GLfloat light_0_difuse[]   = { 0.7, 0.7, 0.7, 1};
GLfloat light_0_specular[] = { 1, 1, 1, 1};
GLfloat light_0_ambient[]  = { 0.2, 0.2, 0.2, 1};

void init(){
    frames = new Frames();

    cam.abertura = 70.0;
    cam.znear = 1;
    cam.zfar = 20;
    cam.aspect = 1.6;

    cam.pos.x = 0;
    cam.pos.y = 0;
    cam.pos.z = 10;

    pistao1.encaixePistao.x = -1.5;
    pistao2.encaixePistao.x = 1.5;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMateriali(GL_FRONT_AND_BACK,  GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_0_difuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_0_ambient);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_SPECULAR);
    glEnable(GL_DIFFUSE);
    glEnable(GL_AMBIENT);
    glEnable(GL_SHININESS);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
}

void text(int x, int y, char  *t){
    glColor3f(0.8,0,0);
    for (char *c = t; *c != '\0'; c++){
		glRasterPos2f(x,y);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		x = x + glutBitmapWidth(GLUT_BITMAP_HELVETICA_18,*c);
	}
}

void line(int x1, int y1, int x2, int y2){
   glBegin(GL_LINES);
      glVertex2d(x1, y1);
      glVertex2d(x2, y2);
   glEnd();
}

void circle( int x, int y, int raio, int div ){
    float ang, x1, y1;
    float inc = PI_2/div;
    glBegin(GL_LINE_LOOP);
    for(ang=0; ang<6.27; ang+=inc){
        x1 = (cos(ang)*raio);
        y1 = (sin(ang)*raio);
        glVertex2d(x1+x, y1+y);
    }
    glEnd();
}

void startGUI(){
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_X, SCREEN_Y, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void endGUI(){
    glPopMatrix();
    glPopAttrib();
}

void drawFPS(){
    static char txt[50];
    sprintf(txt, "FPS:  %.0f", FPS);
    text(10, 20, txt);
    sprintf(txt, "%.0f", RPM);
    text(115, SCREEN_Y - 150, txt);
}

void drawContador(){
    glColor3f(0, 1, 0);
    float x1,  y1, x2, y2;
    circle(130, SCREEN_Y - 130, 105, 100);

    for(float i = -PI_2/8 ; i < (5*(PI_2/8)); i+= fmod(PI_2 / 24, PI_2) ){
        x1 = 90 * cos(-i) + 130;
        y1 = 90 * sin(-i) + (SCREEN_Y - 130);

        x2 = 100 * cos(-i) + 130;
        y2 = 100 * sin(-i) + (SCREEN_Y - 130);

        line(x1, y1, x2, y2);
    }

    text(70, SCREEN_Y - 50, "0");
    text(155, SCREEN_Y - 50, "1000");

    x2 = 80 * -cos(((RPM * (3*PI_2 / 4)) / 1000) - PI_2/8 ) + 130;
    y2 = 80 * -sin(((RPM * (3*PI_2 / 4)) / 1000) - PI_2/8 ) + (SCREEN_Y - 130);

    line(130, SCREEN_Y - 130, x2, y2);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(cam.abertura, cam.aspect, cam.znear, cam.zfar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /// POSIÇÃO DA CAMERA
    gluLookAt(cam.pos.x, cam.pos.y, cam.pos.z,
              0, 0, 0,
              0, 1, 0);

    /// CONTADOR DE FRAMES
    FPS = frames->getFrames();

    /// ROTAÇÃO DA CAMERA
    glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
    glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);

    /// CALCULO DE COORDENADAS POLARES PARA PEGAR OS PONTOS DE ENCAIXE COM O VIRABREQUIM
    vira.encaixe1.y = sin(-angR + ( PI_2 / 4));
    vira.encaixe1.z = cos(-angR + ( PI_2 / 4));

    vira.encaixe2.y = sin(-angR + (3 * (PI_2 / 4)));
    vira.encaixe2.z = cos(-angR + (3 * (PI_2 / 4)));

    ///SETA OS PONTOS DE ENCAIXE NO PISTAO E NA BIELA
    pistao1.encaixePistao.y = vira.encaixe1.y + tam_biela;
    pistao2.encaixePistao.y = vira.encaixe2.y + tam_biela;

    biela1.encaixeVira = vira.encaixe1;
    biela2.encaixeVira = vira.encaixe2;

    biela1.encaixePistao = pistao1.encaixePistao;
    biela2.encaixePistao = pistao2.encaixePistao;

    glPushMatrix();
        inc = ((RPM / 60) / FPS) * 360; /// INCREMENTO DO ANGULO EM RELAÇÃO AO RPM
        ang = fmod(ang += inc, 360);
        angR = ang * 0.0174533;

        glRotatef ((GLfloat) ang, 1.0f, 0.0f, 0.0f);
        vira.render();
    glPopMatrix();


    biela1.render();
    biela2.render();

    pistao1.render();
    pistao2.render();

    startGUI();

    drawFPS();
    drawContador();

    endGUI();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
   key = tolower(key);

    switch(key)
    {
    case 27:
        exit(0);
        break;

    case 'f':
        if(polygonMode == 1){
            polygonMode = 0;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }else{
            polygonMode = 1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        break;
    case 'w':
        cam.abertura -= 1;
        break;
    case 's':
        cam.abertura += 1;
        break;
    case 'o':
        if(RPM < 1000)
            RPM += 1;
        printf("\nrpm = %.2f (inc = %f)", RPM, inc);
        break;
    case 'p':
        if(RPM > 0)
            RPM -= 1;
        break;
    case 'v':
        printf("\n\nvoltas = %f FPS = %.0f", ang / 360, FPS);
        break;
    }
}

void MotionFunc(int x, int y){
    rx = x;
    rz = y;
}

void MouseFunc(int botao, int estado, int x, int y){
    //printf("\n%d %d %d %d", botao, estado, x, y);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowSize (SCREEN_X, SCREEN_Y);
    glutInitWindowPosition (300, 0);

    glutCreateWindow ("Motor");
    init();

    glutDisplayFunc(display);
    glutMotionFunc(MotionFunc);
    glutMouseFunc(MouseFunc);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
