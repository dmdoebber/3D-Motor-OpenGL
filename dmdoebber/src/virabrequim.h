#ifndef VIRABREQUIM_H_INCLUDED
#define VIRABREQUIM_H_INCLUDED

#include "ponto.h"
#define PI_2 6.28318531


class virabrequim{
private:
    float tam_base = 1.5;
    float raio = 0.2;
    float tam_eixos = 1;
    float tam_terminal = 1;

    void gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width, GLint teeth, GLfloat tooth_depth) {
    /// https://www.opengl.org/archives/resources/code/samples/glut_examples/mesademos/gears.c
    GLint i;
    GLfloat r0, r1, r2;
    GLfloat angle, da;
    GLfloat u, v, len;

    r0 = inner_radius;
    r1 = outer_radius - tooth_depth / 2.0;
    r2 = outer_radius + tooth_depth / 2.0;

    da = 2.0 * (PI_2 /2)  / teeth / 4.0;


    glRotated(90, 0, 1, 0);
    glNormal3f(0.0, 0.0, 1.0);

    /* draw front face */
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i <= teeth; i++) {
            angle = i * 2.0 * (PI_2 /2) / teeth;
            glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
            glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
            glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
            glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
        }
    glEnd();

    /* draw front sides of teeth */
    glBegin(GL_QUADS);
        da = 2.0 * (PI_2 /2) / teeth / 4.0;
        for (i = 0; i < teeth; i++) {
            angle = i * 2.0 * (PI_2 /2) / teeth;
            glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
            glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
            glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
            glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
        }
    glEnd();

    glNormal3f(0.0, 0.0, -1.0);

    /* draw back face */
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i <= teeth; i++) {
            angle = i * 2.0 * (PI_2 /2) / teeth;
            glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
            glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
            glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
            glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
        }
    glEnd();

    /* draw back sides of teeth */
    glBegin(GL_QUADS);
        da = 2.0 * (PI_2 /2) / teeth / 4.0;
        for (i = 0; i < teeth; i++) {
            angle = i * 2.0 * (PI_2 /2) / teeth;

            glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
            glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
            glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
            glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
        }
    glEnd();

    /* draw outward faces of teeth */
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i < teeth; i++) {
            angle = i * 2.0 * (PI_2 /2) / teeth;

            glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
            glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
            u = r2 * cos(angle + da) - r1 * cos(angle);
            v = r2 * sin(angle + da) - r1 * sin(angle);
            len = sqrt(u * u + v * v);
            u /= len;
            v /= len;
            glNormal3f(v, -u, 0.0);
            glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
            glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
            glNormal3f(cos(angle), sin(angle), 0.0);
            glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
            glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
            u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
            v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
            glNormal3f(v, -u, 0.0);
            glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
            glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
            glNormal3f(cos(angle), sin(angle), 0.0);
        }

        glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
        glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

    glEnd();

    glShadeModel(GL_SMOOTH);

  /* draw inside radius cylinder */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++) {
        angle = i * 2.0 * (PI_2 /2) / teeth;

        glNormal3f(-cos(angle), -sin(angle), 0.0);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    }
    glEnd();

}

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
        SolidCylinder(0.4, 0.5);

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
        glTranslated(1, 0, 0);

        SolidCylinder(1.5, 0.2);
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
        SolidCylinder(0.4, 0.5);

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
        glTranslated(-0.2, 0, 0);

        glColor3f(0.5, 1, 0.5);
        gear(0.2, 1.5, 0.5, 20, 0.25);

        glPopMatrix();

        glPopMatrix();
    }
};

#endif // VIRABREQUIM_H_INCLUDED
