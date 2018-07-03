#ifndef VIRABREQUIM_H_INCLUDED
#define VIRABREQUIM_H_INCLUDED

#include "ponto.h"

class virabrequim{
private:
    float tam_base = 1.5;
    float raio = 0.2;
    float tam_eixos = 1;
    float tam_terminal = 1;

    void SolidCylinder(float raio, float height){
        glPushMatrix();

        glRotated(90, 0, 1, 0); //alinhar no eixo x

        glutSolidCone(raio, 0, 15, 1);
        gluCylinder(gluNewQuadric(), raio, raio, height, 20, 1);
        glTranslated(0, 0, height);
        glRotated(180, 0, 1, 0);
        glutSolidCone(raio, 0, 15, 1);

        glPopMatrix();
    }
public:
    ponto encaixe1;
    ponto encaixe2;
    float angbiela1;
    float angbiela2;

    virabrequim(){

        encaixe1.x = -1.5;
        encaixe1.y = 0;
        encaixe1.z = 0;

        encaixe2.x = 1.5;
        encaixe2.y = 0;
        encaixe2.z = 0;
    }

    void render(){
        glPushMatrix();
        glTranslated(-0.75, 0, 0); //centraliza o desenho do virabrequim

        glColor3f(0.3, 0.3, 0.3);

        glPushMatrix();
        glRotated(-90, 0, 0, 1);
        glTranslated(0, 1.5, 0);
        SolidCylinder(raio, tam_eixos);
        glutSolidCube(0.4);
        glPopMatrix();

        glPushMatrix();
        glTranslated(1.5, -1, 0);
        SolidCylinder(raio, tam_base);
        glutSolidCube(raio*2);

        glTranslated(0.5, 0, 0); //encaixe 1
        SolidCylinder(0.3, 0.5);

        glPopMatrix();

        glPushMatrix();
        glTranslated(3, -1, 0);
        glutSolidCube(raio*2);
        glPopMatrix();

        glPushMatrix();
        glRotated(-90, 0, 0, 1);
        glTranslated(0, 3, 0);
        SolidCylinder(0.2, tam_eixos);
        glutSolidCube(raio*2);
        glPopMatrix();

        glPushMatrix();
        glTranslated(3, 0, 0);
        SolidCylinder(0.2, 1);
        glPopMatrix();

        SolidCylinder(0.2, tam_base); // meio

        glPushMatrix();
        glTranslated(0, 1, 0);
        glutSolidCube(raio*2);
        glPopMatrix();

        glPushMatrix();
        glRotated(90, 0, 0, 1);
        SolidCylinder(0.2, tam_eixos);
        glutSolidCube(raio*2);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.5, 1, 0);
        SolidCylinder(0.2, tam_base);
        glutSolidCube(raio*2);

        glTranslated(0.5, 0, 0); //encaixe 0
        SolidCylinder(0.3, 0.5);

        glPopMatrix();

        glPushMatrix();
        glRotated(90, 0, 0, 1);
        glTranslated(0, 1.5, 0);
        SolidCylinder(0.2, tam_eixos);
        glutSolidCube(raio*2);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-2.5, 0, 0);
        SolidCylinder(0.2, tam_terminal);
        glPopMatrix();

        glPopMatrix();
    }
};

#endif // VIRABREQUIM_H_INCLUDED
