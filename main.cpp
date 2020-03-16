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
static float **penghubung_sayap_kiri;
static float **penghubung_sayap_kanan;
static float **baling_baling_1;
static float **baling_baling_2;
static float **baling_baling_3;
static float **baling_baling_4;
static float **penghubung_baling_baling;

// angle of rotation for the camera direction
static float angle=0.0;
// actual vector representing the camera's direction
static float lx=0.0f,lz=-1.0f,ly=0.0f;
// XZ position of the camera
static float x=0.0f,z=15.0f,y=0.0f;

static float ax=0.0f,ay=0.0f,az=0.0f;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 3.0f, 3.0f, 3.0f, 0.0f };

const GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat mat_ambient[] = {1.0f, 0.5f, 0.31f, 1.0f};
const GLfloat mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
const GLfloat mat_diffuse[] = {1.0f, 0.5f, 0.31f, 1.0f};
const GLfloat mat_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat no_shininess = 0.0f;
const GLfloat low_shininess = 5.0f;
const GLfloat high_shininess = 100.0f;
const GLfloat mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};

static float* calculate_normal(float* v1, float* v2, float *v3)
{
    // create vector v1 - v2
    float* a = new float[3];
    a[0] = v1[0] - v2[0]; //x
    a[1] = v1[1] - v2[1]; //y
    a[2] = v1[2] - v2[2]; //z

    // create vector v2 - v3
    float* b = new float[3];
    b[0] = v2[0] - v3[0]; //x
    b[1] = v2[1] - v3[1]; //y
    b[2] = v2[2] - v3[2]; //z

    float* normal = new float[3];
    // calculate x component of normal vector
    normal[0] = (a[1]*b[2]) - (a[2]*b[1]);
    // calculate y component of normal vector
    normal[1] = (a[2]*b[0]) - (a[0]*b[2]);
    // calculate z component of normal vector
    normal[2] = (a[0]*b[1]) - (a[1]*b[0]);

    // normalize vector
    float length = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
    normal[0] = normal[0]/length;
    normal[1] = normal[1]/length;
    normal[2] = normal[2]/length;

    return normal;
}

static void readCube(char* filename, float** points_of_cube)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf ("Error opening the file %s\n\n", filename);
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
    glColor3f(cube_points[0][0], cube_points[0][1], cube_points[0][2]);
    float* normal;
    /***    - BAGIAN DEPAN -    ***/
    glBegin(GL_POLYGON);
        normal = calculate_normal(cube_points[1], cube_points[2], cube_points[3]);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(cube_points[1][0], cube_points[1][1], cube_points[1][2]);
        glVertex3f(cube_points[2][0], cube_points[2][1], cube_points[2][2]);
        glVertex3f(cube_points[3][0], cube_points[3][1], cube_points[3][2]);
        glVertex3f(cube_points[4][0], cube_points[4][1], cube_points[4][2]);
    glEnd();

    /***    - BAGIAN BELAKANG -    ***/
    glBegin(GL_POLYGON);
        normal = calculate_normal(cube_points[8], cube_points[7], cube_points[6]);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(cube_points[8][0], cube_points[8][1], cube_points[8][2]);
        glVertex3f(cube_points[7][0], cube_points[7][1], cube_points[7][2]);
        glVertex3f(cube_points[6][0], cube_points[6][1], cube_points[6][2]);
        glVertex3f(cube_points[5][0], cube_points[5][1], cube_points[5][2]);
    glEnd();

    /***    - BAGIAN ATAS -    ***/
    glBegin(GL_POLYGON);
        normal = calculate_normal(cube_points[4], cube_points[3], cube_points[7]);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(cube_points[4][0], cube_points[4][1], cube_points[4][2]);
        glVertex3f(cube_points[3][0], cube_points[3][1], cube_points[3][2]);
        glVertex3f(cube_points[7][0], cube_points[7][1], cube_points[7][2]);
        glVertex3f(cube_points[8][0], cube_points[8][1], cube_points[8][2]);
    glEnd();

    /***    - BAGIAN BAWAH -    ***/
    glBegin(GL_POLYGON);
        normal = calculate_normal(cube_points[2], cube_points[1], cube_points[5]);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(cube_points[2][0], cube_points[2][1], cube_points[2][2]);
        glVertex3f(cube_points[1][0], cube_points[1][1], cube_points[1][2]);
        glVertex3f(cube_points[5][0], cube_points[5][1], cube_points[5][2]);
        glVertex3f(cube_points[6][0], cube_points[6][1], cube_points[6][2]);
    glEnd();

    /***    - BAGIAN KIRI -    ***/
    glBegin(GL_POLYGON);
        normal = calculate_normal(cube_points[1], cube_points[4], cube_points[8]);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(cube_points[1][0], cube_points[1][1], cube_points[1][2]);
        glVertex3f(cube_points[4][0], cube_points[4][1], cube_points[4][2]);
        glVertex3f(cube_points[8][0], cube_points[8][1], cube_points[8][2]);
        glVertex3f(cube_points[5][0], cube_points[5][1], cube_points[5][2]);
    glEnd();


    /***    - BAGIAN KANAN -    ***/
    glBegin(GL_POLYGON);
        normal = calculate_normal(cube_points[3], cube_points[2], cube_points[6]);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(cube_points[3][0], cube_points[3][1], cube_points[3][2]);
        glVertex3f(cube_points[2][0], cube_points[2][1], cube_points[2][2]);
        glVertex3f(cube_points[6][0], cube_points[6][1], cube_points[6][2]);
        glVertex3f(cube_points[7][0], cube_points[7][1], cube_points[7][2]);
    glEnd();
}

static void drawAxis(void)
{
    // X AXIS
    glBegin(GL_LINES);
        glVertex3f(-100.0, 0.0f, 0.0f);
        glVertex3f(100.0, 0.0f, 0.0f);
        // arrow
        glVertex3f(100.0, 0.0f, 0.0f);
        glVertex3f(99.0, 1.0f, 0.0f);
        glVertex3f(100.0, 0.0f, 0.0f);
        glVertex3f(99.0, -1.0f, 0.0f);
    glEnd();

    // Y AXIS
    glBegin(GL_LINES);
        glVertex3f(0.0, -100.0f, 0.0f);
        glVertex3f(0.0, 100.0f, 0.0f);
        // arrow
        glVertex3f(0.0, 100.0f, 0.0f);
        glVertex3f(1.0, 99.0f, 0.0f);
        glVertex3f(0.0, 100.0f, 0.0f);
        glVertex3f(-1.0, 9.0f, 0.0f);
    glEnd();

    // Z AXIS
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0f ,-100.0f );
        glVertex3f(0.0, 0.0f ,100.0f );
        // arrow
        glVertex3f(0.0, 0.0f ,100.0f );
        glVertex3f(0.0, 1.0f ,99.0f );
        glVertex3f(0.0, 0.0f ,100.0f );
        glVertex3f(0.0, -1.0f ,99.0f );
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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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

    // DRAWING COORDINATE (FOR DEBUGGING PROCESS ONLY)
    // drawAxis();

    // DRAWING PHASE
    drawCube(badan);
    drawCube(sayap_atas);
    drawCube(sayap_bawah);
    drawCube(ekor_horizontal);
    drawCube(ekor_vertical);
    drawCube(penghubung_sayap_kiri);
    drawCube(penghubung_sayap_kanan);
    drawCube(baling_baling_1);
    drawCube(baling_baling_2);
    drawCube(baling_baling_3);
    drawCube(baling_baling_4);
    drawCube(penghubung_baling_baling);

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

    // DEFINE SAYAP ATAS
    sayap_atas = new float*[9];
    for (int i = 0; i < 9; i++) {
        sayap_atas[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\sayap_atas.txt", sayap_atas);

    // DEFINE SAYAP BAWAH
    sayap_bawah = new float*[9];
    for (int i = 0; i < 9; i++) {
        sayap_bawah[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\sayap_bawah.txt", sayap_bawah);

     // DEFINE BADAN PESAWAT
    badan = new float*[9];
    for (int i = 0; i < 9; i++) {
        badan[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\badan.txt", badan);

    // DEFINE EKOR HORIZONTAL
    ekor_horizontal = new float*[9];
    for (int i = 0; i < 9; i++) {
        ekor_horizontal[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\ekor_horizontal.txt", ekor_horizontal);

    // DEFINE EKOR VERTIKAL
    ekor_vertical = new float*[9];
    for (int i = 0; i < 9; i++) {
        ekor_vertical[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\ekor_vertical.txt", ekor_vertical);

    glutCreateWindow("Pesawat Tempur");

    // DEFINE PENGHUBUNG SAYAP DAN BADAN KIRI
    penghubung_sayap_kiri = new float*[9];
    for (int i = 0; i < 9; i++) {
        penghubung_sayap_kiri[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\penghubung_kiri.txt", penghubung_sayap_kiri);

    // DEFINE PENGHUBUNG SAYAP DAN BADAN KANAN
    penghubung_sayap_kanan = new float*[9];
    for (int i = 0; i < 9; i++) {
        penghubung_sayap_kanan[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\penghubung_kanan.txt", penghubung_sayap_kanan);

    // DEFINE BALING-BALING 1
    baling_baling_1 = new float*[9];
    for (int i = 0; i < 9; i++) {
        baling_baling_1[i] = new float[3];
    }
    readCube((char *)"..\\..\\model\\baling_baling_1.txt", baling_baling_1);

    // DEFINE BALING-BALING 2
    baling_baling_2 = new float*[9];
    for (int i = 0; i < 9; i++) {
        baling_baling_2[i] = new float[3];
    }
    readCube((char *)"./model/baling_baling_2.txt", baling_baling_2);
    
    // DEFINE BALING-BALING 3
    baling_baling_3 = new float*[9];
    for (int i = 0; i < 9; i++) {
        baling_baling_3[i] = new float[3];
    }
    readCube((char *)"./model/baling_baling_3.txt", baling_baling_3);
    
    // DEFINE BALING-BALING 4
    baling_baling_4 = new float*[9];
    for (int i = 0; i < 9; i++) {
        baling_baling_4[i] = new float[3];
    }
    readCube((char *)"./model/baling_baling_4.txt", baling_baling_4);

    // DEFINE PENGHUBUNG BALING-BALING
    penghubung_baling_baling = new float*[9];
    for (int i = 0; i < 9; i++) {
        penghubung_baling_baling[i] = new float[3];
    }
    readCube((char *)"./model/penghubung_baling_baling.txt", penghubung_baling_baling);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(processSpecialKeys);
    glutIdleFunc(idle);

    // Help menu
    helpMenu();

    // Add lightning to model
    if (argc == 1) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
    }

    glClearColor(0,0.7,1,1); // Background color
    glutMainLoop();

    return EXIT_SUCCESS;
}
