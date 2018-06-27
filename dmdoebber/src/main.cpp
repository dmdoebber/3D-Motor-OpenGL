#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#include "Frames.h"

#define PI_2 6.28318531

#define SCREEN_X 1280
#define SCREEN_Y 720


int   polygonMode = 1;

float rx = 0, rz = 0;

float RPM = 0;
float FPS = 1000;
Frames *frames;


float ang =0.0;
float inc;

float abertura = 44.0;
float znear  = 1;
float zfar   = 20;
float aspect = 1.6;

class ponto{
public:
    float x, y, z;
};

ponto camera;


GLfloat mat_specular[] = { 1, 1, 1, 1 };
GLfloat mat_shininess[] = { 10 };

GLfloat light_0_position[] = { 0, 5, 5, 0};
GLfloat light_0_difuse[]   = { 1, 0, 0 };  //RED
GLfloat light_0_specular[] = { 0, 0, 1 };  //WHITE
GLfloat light_0_ambient[]  = { 0.2, 0.2, 0.2 };

GLfloat light_1_position[] = { 5, 5, 5, 0 };
GLfloat light_1_difuse[]   = { 0, 1, 0 };  //GREEN
GLfloat light_1_specular[] = { 1, 1, 1 };  //WHITE
GLfloat light_1_ambient[]  = { 0.2, 0.2, 0.2 };


void init()
{
    frames = new Frames();
    camera.x = 0;
    camera.y = 0;
    camera.z = 10;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluPerspective(abertura, aspect, znear, zfar);
   glMatrixMode(GL_MODELVIEW);

   glClearColor(0, 0, 0, 1);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /*
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_0_difuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
   glLightfv(GL_LIGHT0, GL_AMBIENT,  light_0_ambient);

   glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);
   glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_1_difuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, light_1_specular);
   glLightfv(GL_LIGHT1, GL_AMBIENT,  light_1_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
    */
   glEnable(GL_DEPTH_TEST);
}




void cilindro(float x1, float x2, float r){
    float y, z;
    float ang = PI_2 / 30.0;

    glShadeModel(GL_FLAT);

    glBegin(GL_QUAD_STRIP);

    for(float i  = 0; i <= PI_2; i+= ang){
        y = r * sin(i);
        z = r * cos(i);

        glVertex3f(x1, y, z);
        glVertex3f(x2, y, z);

    }
    glEnd();
}

void text(int x, int y, char  *txt)
{
    int tam = (int)strlen(t);
    int c;

    for(c=0; c<tam; c++){
        glRasterPos2f(x + c*0.1, y);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);

    }
}

////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );

   gluPerspective(abertura, aspect, znear, zfar);


   glMatrixMode(GL_MODELVIEW);

    glLoadIdentity( );

    gluLookAt(camera.x, camera.y, camera.z,  //from. Posicao onde a camera esta posicionada
              0, 0, 0,  //to. Posicao absoluta onde a camera esta vendo
              0, 1, 0); //up. Vetor Up.
    FPS = frames->getFrames();
       static char text[50];
    sprintf(text, "FPS:  %.0f", FPS);
    text(3, 3, text);


    glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
    glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);

    glColor3f(1, 1, 1);

    glRotatef ((GLfloat) ang, 1.0f, 0.0f, 0.0f);
    inc = ((RPM / 60) / FPS) * 600;
    ang += inc;

    cilindro(-1, 1, 0.3);
    glPushMatrix();

    glRotatef ((GLfloat) 90, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0, 1.0, 0.0);
    cilindro(1, 3, 0.3);

    glPushMatrix();

    glRotatef ((GLfloat) 90, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0, -3.0, 0.0);
    cilindro(1, 3, 0.3);

    glPushMatrix();

    glRotatef ((GLfloat) 90, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0, -3.0, 0.0);
    cilindro(1, 3, 0.3);

    glPushMatrix();

    glRotatef ((GLfloat) 90, 0.0f, 0.0f, 1.0f);
    glTranslatef(-3.0, -3.0, 0.0);
    cilindro(1, 3, 0.3);


    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

   glutSwapBuffers();
}


//faz a leitura da entrada do usuario
void keyboard(unsigned char key, int x, int y)
{
   key = tolower(key);

    switch(key)
    {
    case 27:
        exit(0);
        break;

    case 'f':
        if(polygonMode == 1)
        {
            polygonMode = 0;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else
        {
            polygonMode = 1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        break;
    case 'w':
        abertura -= 1;
        break;

    case 's':
        abertura += 1;
        break;

    case 'o':
        RPM += 60;
        printf("\nrpm = %.2f (inc = %f)", RPM, inc);
        break;
    case 'p':
        RPM -= 1;
        break;
    case 'v':
        printf("\n\nvoltas = %f", ang / 360);
        break;
    }
}

void MotionFunc(int x, int y)
{
    float dx, dy;
    rx = x;
    rz = y;
}

void MouseFunc(int botao, int estado, int x, int y)
{
    printf("\n%d %d %d %d", botao, estado, x, y);
}


int main ()
{
   int  argc=1;
   char *argv[1] = {"teste"};

   glutInit(&argc, argv);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowSize (SCREEN_X, SCREEN_Y);
   glutInitWindowPosition (0, 0);
   /* create window */

   glutCreateWindow ("Motor");
   init();
   printf("Digite W para mudar o modo de visualizacao: wireframe/fill");

   glutDisplayFunc(display);
   glutMotionFunc(MotionFunc);
   glutMouseFunc(MouseFunc);
   glutIdleFunc(display);
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}
