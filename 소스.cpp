#include <GL/glut.h>    // includes gl.h glu.h 
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
using namespace std;
#define TILESIZE1 75
#define TILESIZE2 20
#define TILESIZE3 35
class Tile {
public:
	float x;
	float y;
	float z;
	int num;
	bool type;
};
Tile** tile = new Tile*[5];

bool flag = false;
bool jump = false;
float size = 1;
float LeftShape = 0;
float RightShape = 0;
float All = 0;
int a, b, c = 0;
GLvoid InitTile(Tile** tile);
GLvoid CollideChect();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid SpecialKeyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);
GLfloat color = 0.0;
GLvoid SpecialKeyboard(unsigned char key, int x, int y);

GLvoid InitTile(Tile** tile)
{
	for (int i = 0; i < 5; ++i)
	{
		tile[i] = new Tile[100];
	}
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{

			tile[i][j].x = -60 + (i * 30);
			tile[i][j].y = -60;
			tile[i][j].z = 150 + (j * -25);
			tile[i][j].type = false;
			tile[i][j].num = 1;
		}
	}


	tile[0][0].num = 0;
	tile[4][0].num = 0;
	tile[0][3].num = 0;
	tile[2][13].num = 0;
	tile[2][14].num = 0;
	tile[2][15].num = 0;
	tile[2][16].num = 0;
	tile[3][7].num = 2;
	tile[1][5].num = 2;
}

void main(int argc, char *argv[]) {   //초기화 함수들  
	srand(unsigned(time(NULL)));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);  // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정 
	glutCreateWindow("Example2");    // 윈도우 생성 (윈도우 이름)  
	InitTile(tile);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(SpecialKeyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정   
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수 
GLvoid drawScene(GLvoid) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);



	///////////////////바닥/////////////////
	glPushMatrix();
	glTranslatef(0, 0, a);
	glColor3f(0, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (tile[i][j].num == 1)
			{
				glBegin(GL_QUADS);
				glColor3f(0, 0, 1);
				glVertex3f(tile[i][j].x - 15, tile[i][j].y, tile[i][j].z); //v1  
				glVertex3f(tile[i][j].x - 15, tile[i][j].y, tile[i][j].z - 25);  //v2   
				glVertex3f(tile[i][j].x + 15, tile[i][j].y, tile[i][j].z - 25); //v3    
				glVertex3f(tile[i][j].x + 15, tile[i][j].y, tile[i][j].z);  //v4
				glEnd();
			}
			/*if (tile[i][j].num == 1)
			{
			glPushMatrix();
			glTranslatef(tile[i][j].x, tile[i][j].y, tile[i][j].z);
			glutSolidCube(30);
			glPopMatrix();
			}*/
			if (tile[i][j].num == 2)
			{
				glBegin(GL_QUADS);
				glVertex3f(tile[i][j].x - 15, tile[i][j].y, tile[i][j].z); //v1  
				glVertex3f(tile[i][j].x - 15, tile[i][j].y, tile[i][j].z - 25);  //v2   
				glVertex3f(tile[i][j].x + 15, tile[i][j].y, tile[i][j].z - 25); //v3    
				glVertex3f(tile[i][j].x + 15, tile[i][j].y, tile[i][j].z);  //v4
				glEnd();

				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslatef(tile[i][j].x, tile[i][j].y + 25, tile[i][j].z);
				glutSolidCube(25);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(b, -50 + c, 150);
	glutSolidSphere(10, 20, 20);
	glPopMatrix();

	glFlush();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1, 1.0, 1000.0);
	glTranslatef(0, 0, -300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void SpecialKeyboard(unsigned char key, int x, int y)
{
	if (key == 'e')
		b -= 5;
	if (key == 'r')
		b += 5;
	if (key == 'b')
	{
		jump = true;
	}

}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void TimerFunction(int value)
{
	//All += 10;
	a += 3;


	glutPostRedisplay();   // 화면 재 출력 
	glutTimerFunc(50, TimerFunction, 1);
	CollideChect();

}

GLvoid CollideChect()
{
	int Z = 0;
	int X = 0;
	Z = a / 25;
	X = (b + 130) / 30;
	if (tile[X - 2][Z].num == 0)
		c -= 10;
	if (tile[X - 2][Z].num == 2)
		cout << "충돌" << endl;

}

GLvoid SpecialKeyboard(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		b -= 5;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		b += 5;
	}
	printf("%s", key);
}
