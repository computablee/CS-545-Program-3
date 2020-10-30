//saving space by combining the head comment and the console output into a multiline string at the start of the program
//instead of duplicating all the text into both a string and a comment
//this is about the first time in years that i've wished a python feature would become normalized (multiline strings with """)
const char* info = ""
"Phillip Lane\n"
"CS 545 01\n"
"10/27/2020\n"
"Dr. Hauenstein\n"
"\n"
"Software used:\n"
"Windows 10 Pro\n"
"Visual Studio 2017 (v141)\n"
"Windows SDK Toolkit 10.0.18362.0\n"
"\n"
"Hardware used:\n"
"2x Opteron 6380\n"
"64GB DDR3\n"
"Nvidia Quadro K4200\n"
"\n"
"This program is a small paint-like program that has the ability of drawing several different shapes of randomized colors.\n"
"\n"
"Controls:\n"
" w - move up\n"
" s - move down\n"
" a - move left\n"
" d - move right\n"
" + - cycle through cubes, spheres, and triangles (default: cube)\n"
" o - reverse triangles' front face (default: CCW)\n"
" r - clear all shapes\n"
" l - toggle live cursor\n"
" space - draw current shape with a random color\n"
" esc - Quit\n"
"\n";

//Just some libraries we're gonna be using
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <limits.h>
#include "list.h"

//struct for the cursor location
typedef struct
{
	float x;
	float y;
	float z;
} cursor_location;

//struct for colors
typedef struct
{
	float red;
	float green;
	float blue;
} color;

//struct for the brushes available
typedef enum
{
	cube = 1, sphere, triangle
} brushes;

//struct for a drawn shape, contains the brush used, its location, and its color
typedef struct
{
	brushes brush;
	cursor_location location;
	color color; //c can recognize the difference between a type and a variable based on context, which i think is really cool actually cause some languages TOTALLY can't do this
} drawn_shape;

//just some globals, these should be pretty self-explanatory
cursor_location cursor;
color current_color;
brushes brush;
list shapes;
GLenum triangle_orientation;
bool live_cursor;

//this draws a shape to the screen
void draw_shape(drawn_shape shape)
{
	//set the color and translate to the correct position
	glColor3f(shape.color.red, shape.color.green, shape.color.blue);
	glLoadIdentity();
	glTranslatef(shape.location.x, shape.location.y, shape.location.z);

	//switch the brush
	switch(shape.brush)
	{
		//draw a cube
	case cube:
		glutWireCube(5.0f);
		break;
		//draw a sphere
	case sphere:
		glutWireSphere(2.5f, 10, 10);
		break;
		//draw a triangle
	case triangle:
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 2.5f, 0.0f);
		glVertex3f(-2.5f, -2.5f, 0.0f);
		glVertex3f(2.5f, -2.5f, 0.0f);
		glEnd();
		break;
		//printf a funny image of heavy from tf2, pause for 10 seconds, then crash the program
		//cause i think that's funny
	default:
		//this should never happen
		printf("https://i.imgflip.com/gt534.jpg");
		Sleep(10000);
		const int zero = 0; //this is because the string "1/0" is illegal in C, so we have to do this workaround
							//why am i dividing by zero? because C doesn't have a "throw"
							//yes i could do something with stderr probably but this is sillier and it brings me joy to cause a hardware exception
							//was tempted to do something like printf("%d", *(int*)0) to segfault but i kinda didn't wanna cause concern
		printf("%d", 1 / zero);
	}

	//pop the matrix
	glPopMatrix();
}

//Handler for drawing the scene
void drawScene(void)
{
	//clear everything
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//traverse the list and draw all the shapes
	for (unsigned int i = 0; i < shapes.length; i++)
		draw_shape(*(drawn_shape*)shapes.data[i]);

	//if we have a live cursor, draw the shape that the user would draw if they pressed space
	if (live_cursor)
		draw_shape((drawn_shape) { .brush = brush, .color = current_color, .location = cursor });
	//otherwise draw that point
	else
	{
		glLoadIdentity();
		glTranslatef(cursor.x, cursor.y, cursor.z);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f(cursor.x, cursor.y, cursor.z);
		glEnd();
		glPopMatrix();
	}

	//create the string to be printed concerning info about the currently selected brush
	char outp[16] = "Brush: ";
	strcat_s(outp, 16, brush == cube ? "Cube" :
		brush == sphere ? "Sphere" :
		brush == triangle ? "Triangle" :
		"uh oh");

	//print that string to the canvas
	glColor3f(0.0f, 0.0f, 0.0f);
	glLoadIdentity();
	glRasterPos3f(-48.0f, -48.0f, -50.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)outp);
	glPopMatrix();
	
	//Swap buffers because of double buffering
	glutSwapBuffers();
}

//Resizing handler
void resize(int width, int height)
{
	//Set the viewing box
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Set up everything
void setup(void)
{
	//set the polygon modes and point size
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_FILL);
	glPointSize(5.0);
	//seed RNG
	srand((unsigned int)time(NULL));
	//set the clear color to white
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//initialize the shapes list
	init_list(&shapes);
	//set the cursor to the origin
	cursor = (cursor_location) { 0.0f, 0.0f, -50.0f };
	//set the default brush to a cube, the triangle orientation to CCW, and randomize the current color
	brush = cube;
	triangle_orientation = GL_CCW;
	glFrontFace(triangle_orientation);
	current_color = (color) { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX };
	//set live_cursor to false, draw the scene, and print the data
	live_cursor = false;
	glutPostRedisplay();
	printf("%s", info);
}

//Handler for ASCII input
void keyInput(unsigned char key, int x, int y)
{
	drawn_shape shape; //have to declare this up here cause of stupid stuff about declarations not able to have labels
	switch (key)
	{
		//if +, cycle through the brushes
	case '+':
		if (brush == triangle)
			brush = cube;
		else
			brush++;
		glutPostRedisplay();
		break;
		//if o, toggle triangle orientation
	case 'o':
		if (triangle_orientation == GL_CCW)
			triangle_orientation = GL_CW;
		else
			triangle_orientation = GL_CCW;
		glFrontFace(triangle_orientation);
		glutPostRedisplay();
		break;
		//if w, move up
	case 'w':
		if (cursor.y + 5 <= 50)
			cursor.y += 5;
		glutPostRedisplay();
		break;
		//if s, move down
	case 's':
		if (cursor.y - 5 >= -50)
			cursor.y -= 5;
		glutPostRedisplay();
		break;
		//if a, move left
	case 'a':
		if (cursor.x - 5 >= -50)
			cursor.x -= 5;
		glutPostRedisplay();
		break;
		//if d, move right
	case 'd':
		if (cursor.x + 5 <= 50)
			cursor.x += 5;
		glutPostRedisplay();
		break;
		//if l, toggle live cursor
	case 'l':
		live_cursor = !live_cursor;
		glutPostRedisplay();
		break;
		//if space, draw the shape
	case ' ':
		shape = (drawn_shape) { .brush = brush, .color = current_color, .location = cursor }; //create the drawn_shape object
		current_color = (color) { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX }; //randomize a new color
		insert_back(&shapes, &shape, sizeof(drawn_shape)); //insert that shape to the back of the list
		glutPostRedisplay();
		break;
		//if r, free the list
	case 'r':
		free_list(&shapes);
		glutPostRedisplay();
		break;
		//If escape, quit
	case 27:
		exit(0);
	default: break;
	}
}

int main(int argc, char **argv)
{
	//Initialize the command line arguments
	glutInit(&argc, argv);

	//Set context version to 4.0 so that it'll play nicely with Dr. Hauenstein's PC (he can't run OpenGL 4.3)
	glutInitContextVersion(4, 0);
	//Compatibility profile, so that we can do glBegin and glEnd, among other things
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	//Set the window options, like display mode, size, position, and text
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MS Paint except written by a drunk undergrad");

	//Attach our handler functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	//Set this because glew doesn't like it when you don't, and initialize glew
	glewExperimental = GL_TRUE;
	glewInit();

	//Go to the setup function
	setup();

	//Start the main glut loop! We're off to the races!!
	glutMainLoop();
}