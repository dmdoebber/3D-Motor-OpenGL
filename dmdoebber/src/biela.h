#ifndef BIELA_H_INCLUDED
#define BIELA_H_INCLUDED

#include "ponto.h"

#define PI_2 6.283185307179

class biela{
private:
    void SolidCylinder(float raio, float height, float div){
        glPushMatrix();

        glRotated(90, 1, 0, 0);

        glRotated(180, 0, 1, 0);
        gluDisk(gluNewQuadric(),     0, raio, div, 1);
        glRotated(180, 0, 1, 0);
        gluCylinder(gluNewQuadric(), raio, raio, height, div, 1);
        glTranslated(0, 0, height);
        gluDisk(gluNewQuadric(),     0, raio, div, 1);

        glPopMatrix();
    }

public:
    ponto encaixeVira;
    ponto encaixePistao;
    float tam_biela = 2.5;
    float ang = 0.0;

    void render(){
        glPushMatrix();

        glColor3f(0.75, 0.75, 0.75);
        ang = atan((encaixePistao.z - encaixeVira.z) / (encaixePistao.y - encaixeVira.y)) * 57.2958;
        glTranslated(encaixeVira.x, encaixePistao.y, 0);
        glRotated(ang, 1, 0, 0);
        SolidCylinder(0.2, tam_biela, 25);

        glPopMatrix();
    }
};

#endif // BIELA_H_INCLUDED
