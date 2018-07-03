#ifndef PISTAO_H_INCLUDED
#define PISTAO_H_INCLUDED

#include "ponto.h"

class pistao{
public:
    int tam_biela = 3;
    int tam_pistao = 1;
    float raio = 0.3;
    float precisao_encaixe = 0.1;
    ponto encaixePistao;

    void render(){
        glPushMatrix();

        glColor3f(0, 0, 1);

        glTranslated(encaixePistao.x, encaixePistao.y + tam_pistao - precisao_encaixe, encaixePistao.z);
        glRotated(90, 1, 0, 0);
        gluCylinder(gluNewQuadric(), raio, raio, tam_pistao, 50, 1);

        glPopMatrix();
    }
};

#endif // PISTAO_H_INCLUDED
