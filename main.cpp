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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;

/** CUBE SHAPE VARIABLE **/
static float **sayap_atas;
static float **sayap_bawah;
static float **badan;
static float **ekor_horizontal;
static float **ekor_vertical;

// angle of rotation for the camera direction
static float angle=0.0;
// actual vector representing the camera's direction
static float lx=0.0f,lz=-1.0f,ly=0.0f;
// XZ position of the camera
static float x=0.0f,z=5.0f,y=1.0f;

static float ax=0.0f,ay=0.0f,az=0.0f;

static void readCube(char* filename, float** points_of_cube)

{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf ("Error opening the file\n\n");
        exit(EXIT_FAILURE);
    }
    else {
        int i = 0;
        int status_file;
        status_file = fscanf(file, "%f %f %f\n", &points_of_cube[i][0], &points_of_cube[i][1], &points_of_cube[i][2]);
        while (status_file != EOF) {
            i++;
            status_file = fscanf(file, "%f %f %f\n", &points_of_cube[i][0], &points_of_cube[i][1], &points_of_cube[i][2]);
        }
    }
    fclose(file);
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
    glLoadIdentity();
    gluLookAt(	x, y, z,
			x+lx, y+ly,  z+lz,
			0.0f, 1.0f,  0.0f);

    // cout << x << y << z << endl;

    glRotatef(ay,0.0f,1.0f,0.0f);
    glRotatef(ax,1.0f,0.0f,0.0f);
    glRotatef(az,0.0f,0.0f,1.0f);

    glColor3d(1,0,0);

    // DRAWING PHASE
    drawCube(sayap_atas);
    drawCube(sayap_bawah);
    drawCube(badan);
    drawCube(ekor_horizontal);
    drawCube(ekor_vertical);

    glutSwapBuffers();
}

static void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
            x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}


static void key(unsigned char key, int xx, int yy)
{

    float fraction = 0.1f;
    int rotate_rate = 1;

	switch (key) {
		case 'a' :
			x += lz * fraction;
            z -= lx * fraction;
			break;
		case 'd' :
			x -= lz * fraction;
            z += lx * fraction;
			break;
		case 'w' :
			y += fraction;

			break;
		case 's' :
			y -= fraction;

			break;
        case 'i' :
			ax = (float)(((int)ax + rotate_rate)%360);

			break;
        case 'j' :
			ay = (float)(((int)ay - rotate_rate)%360);

			break;
        case 'k' :
			ax = (float)(((int)ax - rotate_rate)%360);

			break;
        case 'l' :
			ay = (float)(((int)ay + rotate_rate)%360);

			break;
        case 'u' :
			az = (float)(((int)az + rotate_rate)%360);

			break;
        case 'o' :
			az = (float)(((int)az - rotate_rate)%360);

			break;
	}
    glutPostRedisplay();
}

static void helpMenu(void)
{
    printf("             HELP\n");
    printf("-------------------------------\n");
    printf("Camera control:\n");
    printf("    \'w\' : Move up\n");
    printf("    \'s\' : Move down\n");
    printf("    \'a\' : Move left\n");
    printf("    \'d\' : Move right\n");
    printf("    arrow-up : Zoom in\n");
    printf("    arrow-down : Zoom out\n");
    printf("    arrow-left : Look left\n");
    printf("    arrow-right : Look right\n\n");
    printf("Object control:\n");
    printf("    \'i\' : Rotate right on X axis\n");
    printf("    \'k\' : Rotate left on X axis\n");
    printf("    \'j\' : Rotate left on Y axis\n");
    printf("    \'l\' : Rotate right on Y axis\n");
    printf("    \'u\' : Rotate left on Z axis\n");
    printf("    \'o\' : Rotate right on Z axis\n");
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
    readCube((char *)"..\\..\\sayap_atas.txt", sayap_atas);
    sayap_bawah = new float*[8];
    for (int i = 0; i < 8; i++) {
        sayap_bawah[i] = new float[3];
    }
    readCube((char *)"..\\..\\sayap_bawah.txt", sayap_bawah);

     //Define badan pesawat
    badan = new float*[8];
    for (int i = 0; i < 8; i++) {
        badan[i] = new float[3];
    }
    readCube("..\\..\\badan.txt", badan);

    //Define ekor horizontal pesawat
    ekor_horizontal = new float*[8];
    for (int i = 0; i < 8; i++) {
        ekor_horizontal[i] = new float[3];
    }
    readCube("..\\..\\ekor_horizontal.txt", ekor_horizontal);

    //Define ekor_vertical pesawat
    ekor_vertical = new float*[8];
    for (int i = 0; i < 8; i++) {
        ekor_vertical[i] = new float[3];
    }
    readCube("..\\..\\ekor_vertical.txt", ekor_vertical);

    glutCreateWindow("Pesawat Tempur");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(processSpecialKeys);
    glutIdleFunc(idle);

    // Help menu
    helpMenu();

    glClearColor(0,0.7,1,1); // Background color
    glutMainLoop();

    return EXIT_SUCCESS;
}
