#pragma once

#define MAX_POLYGONS 8
#define MAX_VERTICES 10

class cad_example
{
public:
	cad_example(void);
	~cad_example(void);

	bool picking;
	bool moving;

	int in_polygon;
	int present_color;

	GLsizei wh,ww;

	int draw_mode;

	GLfloat colors[8][3];
	struct polygon
	{
		int color;
		bool used;
		int xmin,xmax,ymin,ymax;
		float xc,yc;
		int nvertices;
		int x[MAX_VERTICES];
		int y[MAX_VERTICES];
	};

	polygon polygons[MAX_POLYGONS];

	

	void myMouse(int,int,int,int); 
	void myMotion(int,int);
	void myDisplay();
	void myReshape(int,int);
	void color_menu(int);
	void main_menu(int);
	int pick_polygon(int,int);

	void init();

	

	
};

