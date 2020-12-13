#include "zpr.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415927

/* Macro for checking OpenGL error state */

#define GLERROR                                                    \
    {                                                              \
        GLenum code = glGetError();                                \
        while (code!=GL_NO_ERROR)                                  \
        {                                                          \
            printf("%s\n",(char *) gluErrorString(code));          \
                code = glGetError();                               \
        }                                                          \
    }

/* From cube.c */

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void
drawBox(void)
{
    int i;

    for (i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 1.0);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void
init(void)
{
    /* Setup cube vertex data. */
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
}

/* end from cube.c */


/* Draw axes */

void drawAxes(void)
{
    /* Name-stack manipulation for the purpose of
       selection hit processing when mouse button
       is pressed.  Names are ignored in normal
       OpenGL rendering mode.                    */

    glPushMatrix();
    /* No name for grey sphere */

    glColor3f(0.3, 0.3, 0.3);
    glutSolidSphere(0.7, 20, 20);

    glPushMatrix();
    glPushName(1);            /* Red cone is 1 */
    glColor3f(1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(0.6, 4.0, 20, 20);
    glPopName();
    glPopMatrix();

    glPushMatrix();
    glPushName(2);            /* Green cone is 2 */
    glColor3f(0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.6, 4.0, 20, 20);
    glPopName();
    glPopMatrix();

    glColor3f(0, 0, 1);         /* Blue cone is 3 */
    glPushName(3);
    glutSolidCone(0.6, 4.0, 20, 20);
    glPopName();

    glPopMatrix();
}

void drawIndigoTriangle() {
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_TRIANGLES);
    glVertex3f(5, 1, 0);
    glVertex3f(10, 1, 0);
    glVertex3f(8, 10, 0);
    glEnd();
}

void draw_cylinder(GLfloat radius,
    GLfloat height,
    GLubyte R,
    GLubyte G,
    GLubyte B)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    glColor3ub(R-40, G-40, B);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle) + 14.0;
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius+ 14.0 , 0.0, height);
    glVertex3f(radius+ 14.0 , 0.0, 0.0);
    glEnd();

    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle) + 14.0;
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius + 14.0, 0.0, height);
    glEnd();

    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle) + 14.0;
        y = radius * sin(angle);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius + 14.0, 0.0, 0.0);
    glEnd();
}


void drawrectangle() {

    glBegin(GL_QUADS);              

    glColor3f(1.000, 0.412, 0.706);
    glVertex3f(-4.0, 1.0, -1.0);
    glVertex3f(-8.0, 1.0, -1.0);
    glVertex3f(-8.0, 1.0, 1.0);
    glVertex3f(-4.0, 1.0, 1.0);

    glVertex3f(-4.0, -1.0, 1.0);
    glVertex3f(-8.0, -1.0, 1.0);
    glVertex3f(-8.0, -1.0, -1.0);
    glVertex3f(-4.0, -1.0, -1.0);

    glVertex3f(-4.0, 1.0, 1.0);
    glVertex3f(-8.0, 1.0, 1.0);
    glVertex3f(-8.0, -1.0, 1.0);
    glVertex3f(-4.0, -1.0, 1.0);

    glVertex3f(-4.0, -1.0, -1.0);
    glVertex3f(-8.0, -1.0, -1.0);
    glVertex3f(-8.0, 1.0, -1.0);
    glVertex3f(-4.0, 1.0, -1.0);

    glVertex3f(-8.0, 1.0, 1.0);
    glVertex3f(-8.0, 1.0, -1.0);
    glVertex3f(-8.0, -1.0, -1.0);
    glVertex3f(-8.0, -1.0, 1.0);

    glVertex3f(-4.0, 1.0, -1.0);
    glVertex3f(-4.0, 1.0, 1.0);
    glVertex3f(-4.0, -1.0, 1.0);
    glVertex3f(-4.0, -1.0, -1.0);
    glEnd(); 
}

void drawdots() {

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    
    glVertex3f(-15, 0, 0);
    glVertex3f(-14, 0, 0);
    glVertex3f(-13, 0, 0);
    glVertex3f(-12, 0, 0);
    glVertex3f(-16, 0, 0);
    glVertex3f(-14, 2, 0);
    glVertex3f(-14, 1, 0);
    glVertex3f(-14, -1, 0);
    glVertex3f(-14, -2, 0);
    glVertex3f(-14, 0, -2);
    glVertex3f(-14, 0, -1);
    glVertex3f(-14, 0, 1);
    glVertex3f(-14, 0, 2);
    glEnd();
}

/* Callback function for drawing */

void display(void)
{
    GLERROR;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
   //drawAxes();
    drawBox();
    drawIndigoTriangle();
    drawrectangle();
    draw_cylinder(1.7, 5.0, 255, 215, 0);
    drawdots();

    glutSwapBuffers();

    GLERROR;
}


/* Callback function for pick-event handling from ZPR */

void pick(GLint name)
{
    printf("Pick: %d\n", name);
    fflush(stdout);
}

static GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//static GLfloat light_diffuse[]  = { 1.0, 0.0, 0.0, 1.0 };
static GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

static GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
static GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
static GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat high_shininess[] = { 100.0 };


/* Entry point */

int main(int argc, char* argv[])
{
    /* Initialise GLUT and create a window */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("GLT Mouse Zoom-Pan-Rotate");

    /* Configure GLUT callback functions */

    glutDisplayFunc(display);
    glPointSize(20.0);

    glScalef(0.25, 0.25, 0.25);

    /* Configure ZPR module */
    init();                         /* <- from cube.c               */
    zprInit();
    zprSelectionFunc(drawAxes);     /* Selection mode draw function */
    zprPickFunc(pick);              /* Pick event client callback   */

     /* Initialise OpenGL */

    GLERROR;

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    GLERROR;

    /* Enter GLUT event loop */

    glutMainLoop();

    return 0;
}
