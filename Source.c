/* Phillip Lane
 * CS 545 01
 * 10/7/2020
 * Dr. Hauenstein
 *
 * Software used:
 * Windows 10 Pro
 * Visual Studio 2017 (v141)
 * Windows SDK Toolkit 10.0.18362.0
 * 
 * Hardware used:
 * 2x Opteron 6380
 * 64GB DDR3
 * Nvidia Quadro K4200
 *
 * This program is a miniature game written in OpenGL. You move a sphere with WASD into a box, whose position is random on the board.
 * Moving the sphere into the box triggers text to appear saying "You win!" You can also speed up and slow down the animation of the sphere.
 *
 * Controls:
 *   W  - move up
 *   A  - move left
 *   S  - move down
 *   D  - move right
 *   +  - speed up the animation
 *   -  - slow down the animation
 *  esc - Quit
 */

//Just some libraries we're gonna be using
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "list.h"

//Handler for drawing the scene
void drawScene(void)
{
	//clear color and depth buffer, set color to that same pretty purple I used in the previous program
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
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

//Set up the vertex array for drawing
void setup(void)
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_FILL);
	glPointSize(5.0);
	srand(time(NULL));
}

//Handler for ASCII input
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
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
	glutCreateWindow("hey mom i made a game without an engine :o");

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