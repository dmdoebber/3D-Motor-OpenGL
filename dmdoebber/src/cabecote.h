#ifndef CABECOTE_H_INCLUDED
#define CABECOTE_H_INCLUDED

class cabecote{

public:
    float tam_cabecote;
    ponto pos_cabecote;

    void render(){
        glPushMatrix();
            glColor3f(0.2, 0.8, 0.9);

            glTranslated(pos_cabecote.x, pos_cabecote.y + 3.9, pos_cabecote.z);
            glRotated(90, 1, 0, 0);
            gluCylinder(gluNewQuadric(), 1.01, 1.01, tam_cabecote, 50, 1);

        glPopMatrix();

    }


};


#endif // CABECOTE_H_INCLUDED
