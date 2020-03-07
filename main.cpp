/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

/** CUBE SHAPE VARIABLE **/
static float **sayap_atas;
static float **sayap_bawah;

static void readCube(char* filename, float** points_of_cube)
{
    ifstream cube_file(filename);
    string line;
    int i = 0;
    int j = 0;
    while (getline(cube_file, line)) {
        int number = 0;
        int comma_number = 0;
        bool comma = false;
        int jumlah_comma = 1;
        bool negatif = false;
        for (unsigned int idx = 0; idx < line.size(); idx++) {
            if (line[idx] == '-') {
                negatif = true;
            }
            else if (line[idx] == ' ') {
                float result = number + (float)comma_number/jumlah_comma;
                if (negatif) {
                    result *= -1;
                }
                points_of_cube[i][j] = result;
                comma = false;
                negatif = false;
                comma_number = 0;
                number = 0;
                jumlah_comma = 1;
                j++;
            }
            else if (line[idx] == '.'){
                comma = true;
            }
            else {
                if (comma) {
                    comma_number *= 10;
                    comma_number += (float)((int)line[idx] - 48);
                    jumlah_comma *= 10;
                }
                else {
                    number *= 10;
                    number += (float)((int)line[idx] - 48);
                }
            }
        }
        i++;
        j = 0;
    }
    cube_file.close();
}

static void drawCube(float **cube_points)
{
    /***    - BAGIAN DEPAN -    ***/
    glBegin(GL_POLYGON);
        glVertex3f(cube_points[0][0], cube_points[0][1], cube_points[0][2]);
        glVertex3f(cube_points[1][0], cube_points[1][1], cube_points[1][2]);
        glVertex3f(cube_points[2][0], cube_points[2][1], cube_points[2][2]);
        glVertex3f(cube_points[3][0], cube_points[3][1], cube_points[3][2]);
    glEnd();

    /***    - BAGIAN BELAKANG -    ***/
    glBegin(GL_POLYGON);
        glVertex3f(cube_points[7][0], cube_points[7][1], cube_points[7][2]);
        glVertex3f(cube_points[6][0], cube_points[6][1], cube_points[6][2]);
        glVertex3f(cube_points[5][0], cube_points[5][1], cube_points[5][2]);
        glVertex3f(cube_points[4][0], cube_points[4][1], cube_points[4][2]);
    glEnd();

    /***    - BAGIAN ATAS -    ***/
    glBegin(GL_POLYGON);
        glVertex3f(cube_points[3][0], cube_points[3][1], cube_points[3][2]);
        glVertex3f(cube_points[2][0], cube_points[2][1], cube_points[2][2]);
        glVertex3f(cube_points[6][0], cube_points[6][1], cube_points[6][2]);
        glVertex3f(cube_points[7][0], cube_points[7][1], cube_points[7][2]);
    glEnd();

    /***    - BAGIAN BAWAH -    ***/
    glBegin(GL_POLYGON);
        glVertex3f(cube_points[1][0], cube_points[1][1], cube_points[1][2]);
        glVertex3f(cube_points[0][0], cube_points[0][1], cube_points[0][2]);
        glVertex3f(cube_points[4][0], cube_points[4][1], cube_points[4][2]);
        glVertex3f(cube_points[5][0], cube_points[5][1], cube_points[5][2]);
    glEnd();



    /***    - BAGIAN KIRI -    ***/
    glBegin(GL_POLYGON);
        glVertex3f(cube_points[3][0], cube_points[3][1], cube_points[3][2]);
        glVertex3f(cube_points[2][0], cube_points[2][1], cube_points[2][2]);
        glVertex3f(cube_points[7][0], cube_points[7][1], cube_points[7][2]);
        glVertex3f(cube_points[4][0], cube_points[4][1], cube_points[4][2]);
    glEnd();


    /***    - BAGIAN KANAN -    ***/
    glBegin(GL_POLYGON);
        glVertex3f(cube_points[2][0], cube_points[2][1], cube_points[2][2]);
        glVertex3f(cube_points[1][0], cube_points[1][1], cube_points[1][2]);
        glVertex3f(cube_points[5][0], cube_points[5][1], cube_points[5][2]);
        glVertex3f(cube_points[6][0], cube_points[6][1], cube_points[6][2]);
    glEnd();
}

/* GLUT callback Handlers */
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    // DRAWING PHASE
    drawCube(sayap_atas);
    drawCube(sayap_bawah);

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    sayap_atas = new float*[8];
    for (int i = 0; i < 8; i++) {
        sayap_atas[i] = new float[3];
    }
    readCube("..\\..\\sayap_atas.txt", sayap_atas);
    sayap_bawah = new float*[8];
    for (int i = 0; i < 8; i++) {
        sayap_bawah[i] = new float[3];
    }
    readCube("..\\..\\sayap_bawah.txt", sayap_bawah);

    glutCreateWindow("Pesawat Tempur");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0,0.7,1,1); // Background color
    glutMainLoop();

    return EXIT_SUCCESS;
}
