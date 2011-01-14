#include "StdAfx.h"
#include "cad_example.h"


cad_example::cad_example(void)
{
	picking=false;
	moving=false;

	in_polygon=-1;
	present_color=0;

	wh=500;
	ww=500;

	

	for(int i=0;i<8;i++)
		for(int j=0;j<3;j++)
		{
			if((i*3+j)<12&&(i*3+j)%4==3)
				colors[i][j]=1;
			else
				colors[i][j]=0;
			if((i*3+j)>=12&&(i*3+j)%4==0)
				colors[i][j]=0;
			else
				colors[i][j]=1;
		}		
		

}


cad_example::~cad_example(void)
{
}

void cad_example::myReshape(int w,int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,(GLdouble)w,0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0,w,h);

	ww=w;
	wh=h;
}

void cad_example::init()
{

	glClearColor(0.5,0.5,0.5,1);

	for(int i=0;i<MAX_POLYGONS;i++) polygons[i].used=false;
}

void cad_example::myMouse(int btn,int state,int x,int y)
{
	int i,j;
	y=wh-y;
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && !picking&&!moving)
	{
		moving=false;
		if(in_polygon>=0)
			if(polygons[in_polygon].nvertices==MAX_VERTICES)
			{
				cout<<"too many vertices"<<endl;
				exit(0);
			}
			i=polygons[in_polygon].nvertices;
			polygons[in_polygon].x[i]=x;
			polygons[in_polygon].y[i]=y;
			polygons[in_polygon].nvertices++;
	}
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && picking&&!moving)
	{
		picking=false;
		moving=false;
		j=pick_polygon(x,y);
		if(j>=0)
		{
			polygons[j].used=false;
			in_polygon=-1;
			glutPostRedisplay();
		}
	}
}


int cad_example::pick_polygon(int x,int y)
{
	int i;
	for(i=0;i<MAX_POLYGONS;i++)
	{
		if(polygons[i].used)
			if((x>=polygons[i].xmin)&&(x<=polygons[i].xmax)&&(y>=polygons[i].ymin)&&(y<=polygons[i].ymax))
			{
				in_polygon=i;
				moving=true;
				return i;
			}
	cout<<"not in a polygon"<<endl;
	return -1;
	}

}

void cad_example::myMotion(int x,int y)
{
	float dx,dy;
	int i,j;
	if(moving)
	{
		y=wh-y;
		j=pick_polygon(x,y);
		if(j<0)
		{
			cout<<"not in a polygon"<<endl;
			return;
		}

		dx=x-polygons[j].xc;
		dy=y-polygons[j].yc;
		for(i=0;i<polygons[j].nvertices;i++)
		{
			polygons[j].x[i]+=dx;
			polygons[j].y[i]+=dy;
		}


		polygons[j].xc+=dx;
		polygons[j].yc+=dy;
		if(dx>0)polygons[j].xmax+=dx;
		else polygons[j].xmin=+dx;
		if(dy>0)polygons[j].ymax+=dy;
		else polygons[j].ymin=+dy;

		glutPostRedisplay();

		}
}

void cad_example::color_menu(int index)
{
	present_color=index;
	if(in_polygon>=0) polygons[in_polygon].color=index;
}

void cad_example::main_menu(int index)
{
	int i;
	switch(index)
	{
		case(1):
			{
				moving=false;
				for(i=0;i<MAX_POLYGONS;i++)
					if(polygons[i].used==false)break;
				if(i==MAX_POLYGONS)
				{
					cout<<"MAX polygons"<<endl;
					exit(0);
				}
				polygons[i].color=present_color;
				polygons[i].used=true;
				polygons[i].nvertices=0;
				in_polygon=i;
				picking=false;
				break;
			}
		case(2):
			{
				moving=false;
				if(in_polygon>=0)
				{
					polygons[in_polygon].xmax=polygons[in_polygon].xmin=polygons[in_polygon].x[0];
					polygons[in_polygon].ymax=polygons[in_polygon].ymin=polygons[in_polygon].y[0];
					polygons[in_polygon].xc=polygons[in_polygon].x[0];
					polygons[in_polygon].yc=polygons[in_polygon].y[0];
					for(i=1;i<polygons[in_polygon].nvertices;i++)
					{
						if(polygons[in_polygon].x[i]<polygons[in_polygon].xmin) polygons[in_polygon].xmin=polygons[in_polygon].x[i];
						else
							if(polygons[in_polygon].x[i]>polygons[in_polygon].xmax) polygons[in_polygon].xmax=polygons[in_polygon].x[i];
						if(polygons[in_polygon].y[i]<polygons[in_polygon].ymin) polygons[in_polygon].ymin=polygons[in_polygon].y[i];
						else
							if(polygons[in_polygon].y[i]>polygons[in_polygon].ymax) polygons[in_polygon].ymax=polygons[in_polygon].y[i];

						polygons[in_polygon].xc+=polygons[in_polygon].x[i];
						polygons[in_polygon].yc+=polygons[in_polygon].y[i];
					}

					polygons[in_polygon].xc=polygons[in_polygon].xc/polygons[in_polygon].nvertices;
					polygons[in_polygon].yc=polygons[in_polygon].yc/polygons[in_polygon].nvertices;

				}
				in_polygon=-1;
				glutPostRedisplay();
				break;
			}
		case(3):
			{
				picking=true;
				moving=true;
				break;
			}
		case(4):
			{
				moving=true;
				break;
			}
		case(5):
			{
				exit(0);
				break;

			}
	}
}

void cad_example::myDisplay()
{
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0;i<MAX_POLYGONS;i++)
	{
		if(polygons[i].used)
		{
			glColor3fv(colors[polygons[i].color]);
			glBegin(GL_POLYGON);
			for(j=0;j<polygons[i].nvertices;j++)
				glVertex2i(polygons[i].x[j],polygons[i].y[j]);
			glEnd();
		}
	}
	glFlush();
}


