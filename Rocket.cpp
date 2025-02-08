/*
Ilgýn Tandoðan
22203709
Section 3

Additional Functions:

Stars are moving randomly.
Accelaretion of the rocket can be changed by left or right arrow button.
The flame of the rocket gets bigger when rocket accelaretes.
Planets move up when you click right button of the mouse.
Planets move down when you click left buttom of the mouse.
If the rocket passed the screen while moving upwards, it will need to exit apper from below.
The color of the name on the label changes randomly.

*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define TIMER_PERIOD   20   // Period for the timer
#define TIMER_ON        1   // 0:Disable timer, 1:Enable timer

#define PI 3.1415



// Global variables for Template File

int  winWidth, winHeight; // Current Window width and height
int speed = 3; //To adjust the speed of the rocket
int locH = 0;//To change the position of the planets in the y coordinate

// Global variables
bool activeTimer = true;//for the rocket to stop or continue its movement.
bool speedcheck = false;//To adjust the speed of the rocket

int xR = -WINDOW_WIDTH / 2, yR = 0; //Rocket's initial position

// To draw a filled circle, centered at (x,y) with radius r
void circle(int x, int y, int r) {
	float angle;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void vprint(int x, int y, void* font, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, str[i]);
}


// FUNCTIONS TO DISPLAY SHAPES
void drawRectangle() {
	glRectf(-200, -100, 200, 100);
}

void drawTriangle() {
	glBegin(GL_TRIANGLES);
	glVertex2f(-200, -100);
	glVertex2f(0, 100);
	glVertex2f(200, -100);
	glEnd();
}

void drawRocket()
{

	// rocket body
	glColor3f(0.7, 0.7, 0.7); // White
	glRectf(xR - 230, yR - 30, xR - 50, yR + 30);//x,y,x,y


	//windows of the rocket
	glColor3f(0, 0.7, 1.2);
	circle(xR - 80, yR, 20);

	glColor3f(0, 0.7, 1.2);
	circle(xR - 140, yR, 20);

	glColor3f(0, 0.7, 1.2);
	circle(xR - 200, yR, 20);

	// tip of rocket
	glColor3f(1, 1, 1); // white
	glBegin(GL_TRIANGLES);
	glVertex2f(xR, yR);//x,y
	glVertex2f(xR - 50, yR + 30);//x,y
	glVertex2f(xR - 50, yR - 30);//x,y
	glEnd();

	// flames of the rocket
	if (speedcheck)//If rocket accelerates, a darker and larger flame will emerge.
	{
		glColor3ub(255, 100, 0); // dark orange
		glBegin(GL_TRIANGLES);
		glVertex2f(xR - 230, yR - 25);
		glVertex2f(xR - 300, yR);
		glVertex2f(xR - 230, yR + 25);
		glEnd();

	}

	else //If it slows down, a lighter and smaller flame will emerge.
	{
		glColor3ub(255, 144, 0); // orange
		glBegin(GL_TRIANGLES);
		glVertex2f(xR - 230, yR - 15);
		glVertex2f(xR - 260, yR);
		glVertex2f(xR - 230, yR + 15);
		glEnd();
	}




	//for the wings of the rocket
	glColor3f(1.0, 1, 1); // red
	glBegin(GL_TRIANGLES);
	glVertex2f(xR - 200, yR + 30);//x,y
	glVertex2f(xR - 230, yR + 45);//x,y
	glVertex2f(xR - 230, yR + 30);//x,y
	glEnd();

	glColor3f(1.0, 1, 1); // red
	glBegin(GL_TRIANGLES);
	glVertex2f(xR - 200, yR - 30);//x,y 
	glVertex2f(xR - 230, yR - 30);//x,y
	glVertex2f(xR - 230, yR - 45);//x,y
	glEnd();
}



// To display onto window using OpenGL commands
void display() {
	// Clear window to black
	glClearColor(0, 0, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	//sun
	glColor3f(1, 1, 0);
	circle(-175, 125 + locH, 75);

	glColor3ub(255, 255, 255);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(-175, 200 + locH);
	glVertex2f(-175, 400 + locH);
	glEnd();



	//moon
	glBegin(GL_LINES);
	glVertex2f(0, 150 + locH);
	glVertex2f(0, 400 + locH);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	circle(0, 150 + locH, 30);

	glColor3ub(1, 1, 1);
	glLineWidth(3);


	//Neptune
	glColor3ub(255, 255, 255);
	glBegin(GL_LINES);
	glVertex2f(175, -150 + locH);
	glVertex2f(175, 400 + locH);
	glEnd();

	glColor3f(0.0, 1.0, 1.0);
	circle(175, -150 + locH, 40);

	glColor3ub(1, 1, 1);
	glLineWidth(3);




	//for randomly positioned stars
	int cordinateX,
		cordinateY;
	double r,
		g,
		b;

	srand(time(NULL));
	glBegin(GL_POINTS);

	for (int i = 0; i < 200; i++)
	{
		cordinateX = rand() % 800 - 400;
		cordinateY = rand() % 800 - 400;

		glColor3f(1, 1, 1);
		glPointSize(10);

		glVertex2f(cordinateX, cordinateY);
	}
	glEnd();


	drawRocket();

	glColor3f(1, 1, 1); // White

	//bottom of frame
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(400, -250);
	glVertex2f(400, -300);
	glVertex2f(-400, -300);
	glVertex2f(-400, -250);
	glEnd();

	//left of frame
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(-400, -300);
	glVertex2f(-350, -300);
	glVertex2f(-350, 300);
	glVertex2f(-400, 300);
	glEnd();

	//top of frame
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(-400, 300);
	glVertex2f(400, 300);
	glVertex2f(400, 250);
	glVertex2f(-400, 250);
	glEnd();

	
	

	//right of frame
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(400, 300);
	glVertex2f(400, -300);
	glVertex2f(350, -300);
	glVertex2f(350, 300);
	glEnd();

	//for circles in the frame
	for (int i = -365; i < 400; i += 147)
	{
		glColor3f(0.2, 0.2, 0.2);
		circle(i, 275, 15);
		circle(i, -275, 15);
	}

	for (int i = -180; i < 250; i += 120)
	{
		glColor3f(0.2, 0.2, 0.2);
		circle(-375, i, 15);
		circle(375, i, 15);
	}

	glColor3f(0.7, 0.7, 0.7); // White
	glRectf(-300, -183, -150, -150);//x,y,x,y

	srand(time(NULL));
	
	
	for (int i = 0; i < 200; i++)//to change the color of my name randomly
	{
		r = rand() % 2 ;
		g = rand() % 2;

		b = rand() % 2;

		glColor3f(r, g, b);
		vprint(-286, -170, GLUT_BITMAP_9_BY_15, "Ilgin Tandogan");//to display my name
	}
	
	
	glutSwapBuffers();
}

// Key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
void onKeyDown(unsigned char key, int x, int y) {
	// Exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y) {
	// Exit when ESC is pressed.
	if (key == 27)
		exit(0);

	else if (key == ' ')//To change the active time to stop when you press the space
		activeTimer = !activeTimer;
	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
void onSpecialKeyDown(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT) {
		if (speedcheck)
			speedcheck = !speedcheck;
		speed = 1;//speed down
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (!speedcheck)
			speedcheck = !speedcheck;
		speed += 20; //speed up
	}

	//To change the y coordinates with the up and down keys
	else if (key == GLUT_KEY_UP)
		yR += 10;
	else if (key == GLUT_KEY_DOWN)
		yR -= 10;


	// To refresh the window it calls display() function
	glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {//To move the planets down with the left button on the mouse
		locH -= 5;
	}
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {//To move the planets up with the right mouse button
		// Map from GLUT coordinate system to OpenGL Coordinate System
		locH += 5;
	}
	// To refresh the window it calls display() function
	glutPostRedisplay();
}

/*
   This function is called when the window size changes.
   w : is the new width of the window in pixels
   h : is the new height of the window in pixels
*/
void onResize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // Refresh window
}

#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);

	if (activeTimer)
	{
		if (xR + 130 <= winWidth)//for the rocket to continue moving if it does not pass the window.
			xR += speed;
		else if (xR + 130 > winWidth)//If the rocket has passed the screen, it will continue to move from the left side.
			xR = -winWidth / 2;


		if (yR - 30 > winHeight - 50)//If the rocket passed the screen while moving upwards, it will need to appear again from below.
			yR = -280;

	}

	//to refresh the window it calls display() function
	glutPostRedisplay(); //display()

}
#endif

void init() {
	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rocket Simulator");


	// Window Events
	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	// Keyboard Events
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);


	// Mouse Events
	glutMouseFunc(onClick);


#if TIMER_ON == 1
	// Timer Event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	// Initialize random generator
	srand(time(0));

	glutDisplayFunc(display);

	init();
	glutMainLoop();
	return 0;
}