// ogl_learning.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cad_example.h"


cad_example cad;


void init_1()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,50,0,50,-100,100);
	
	glMatrixMode(GL_MODELVIEW);
	
}

//void display_1()
//{
//	GLfloat vertices[3][3]={{0.0,0.0,0.0},{25.0,50.0,0.0},{50.0,0.0,0.0}};
//	int i,j,k;
//	int rand();
//	GLfloat p[3]={7.5,3.0,0.0};
//	glViewport(0,0,200,200);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0,0,0);
//	glBegin(GL_LINES);
//		GLfloat l[3]={0,0,0};
//		glVertex3fv(l);
//		GLfloat l1[3]={25,50,0};
//		glVertex3fv(l1);
//		
//	glEnd();
//	glBegin(GL_LINES);
//		glVertex3fv(l1);
//		GLfloat l2[3]={50,0,0};
//		glVertex3fv(l2);
//	glEnd();
//	glBegin(GL_LINES);
//		glVertex3fv(l2);
//		glVertex3fv(l);
//	glEnd();
//	glBegin(GL_LINES);
//		glVertex3fv(l1);
//		GLfloat l3[3]={25,0,0};
//		glVertex3fv(l3);
//	glEnd();
//
//	glColor3f(1.0,0.0,0.0);
//	glBegin(GL_POINTS);
//	for(int i=0;i<10000;i++)
//	{
//		j=rand()%3;
//
//		p[0]=(p[0]+vertices[j][0])/2.0;
//		p[1]=(p[1]+vertices[j][1])/2.0;
//
//		glVertex3fv(p);
//	}
//	GLfloat o[3]={0,0,0};
//	glColor3f(0,0,0);
//	glVertex3fv(o);
//	glColor3f(1.0,0.0,0.0);
//
//	glEnd();
//	glFlush();
//}


GLfloat v[4][3]={{0,0,1},{0,0.942809,-0.333333},{-0.816497,-0.471405,-0.333333},{0.816497,-0.471405,-0.333333}};

GLfloat colors[4][3]={{1,0,0},{0,1,0},{0,0,1},{0,0,0}};

int n=4;

void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}

void tetra(GLfloat *a,GLfloat *b, GLfloat *c, GLfloat *d)
{
	glColor3fv(colors[0]);
	triangle(a,b,c);
	glColor3fv(colors[1]);
	triangle(a,c,d);
	glColor3fv(colors[2]);
	triangle(a,d,b);
	glColor3fv(colors[3]);
	triangle(b,d,c);
}

void divide_tetra(GLfloat *a,GLfloat *b,GLfloat *c, GLfloat *d,int m)
{
	GLfloat mid[6][3];
	int j=0;
	if(m>0)
	{
		for(j=0;j<3;j++) mid[0][j]=(a[j]+b[j])/2;
		for(j=0;j<3;j++) mid[1][j]=(a[j]+c[j])/2;
		for(j=0;j<3;j++) mid[2][j]=(a[j]+d[j])/2;
		for(j=0;j<3;j++) mid[3][j]=(b[j]+c[j])/2;
		for(j=0;j<3;j++) mid[4][j]=(c[j]+d[j])/2;
		for(j=0;j<3;j++) mid[5][j]=(b[j]+d[j])/2;

		divide_tetra(a,mid[0],mid[1],mid[2],m-1);
		divide_tetra(mid[0],b,mid[3],mid[5],m-1);
		divide_tetra(mid[1],mid[3],c,mid[4],m-1);
		divide_tetra(mid[2],mid[4],d,mid[5],m-1);
	}
	else
		tetra(a,b,c,d);
}


void myReshape(int w,int h)
{
	cad.myReshape(w,h);
	/*glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2,2,-2*(GLfloat)h/(GLfloat)w,2*(GLfloat)h/(GLfloat)w,-10,10);
	else
		glOrtho(-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();*/
}

//void display_2()
//{
//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	glBegin(GL_TRIANGLES);
//	divide_tetra(v[0],v[1],v[2],v[3],n);
//	glEnd();
//	glFlush();
//}

void myMouse(int button, int state, int x, int y)
{
	/*if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
		exit(0);*/
	cad.myMouse(button,state,x,y);
}

void myDisplay()
{
	cad.myDisplay();
}

void myMotion(int x,int y)
{
	cad.myMotion(x,y);
}
void color_menu(int index)
{
	cad.color_menu(index);
}

void main_menu(int index)
{
	cad.main_menu(index);
}


int _tmain(int argc, _TCHAR* argv[])

{

	int c_menu;

	glutInit(&argc,(char**)argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("CAD Example");
	
	glutDisplayFunc(myDisplay);
	cad.init();

	c_menu=glutCreateMenu(color_menu);

	glutAddMenuEntry("Black",0);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAddMenuEntry("Cyan",4);
	glutAddMenuEntry("Megenta",5);
	glutAddMenuEntry("Yellow",6);
	glutAddMenuEntry("White",7);

	glutCreateMenu(main_menu);
	glutAddMenuEntry("new Polygon",1);
	glutAddMenuEntry("end Polygon",2);
	glutAddMenuEntry("delete Polygon",3);
	glutAddMenuEntry("move Polydon",4);
	glutAddMenuEntry("quit",5);
	glutAddSubMenu("Colors",c_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(myReshape);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutMainLoop();



	/*glutInit(&argc,(char**)argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(300,200);
	glutCreateWindow("My gl_learning_1");
	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display_2);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,1);
	glutMainLoop();*/

	return 0;
}





