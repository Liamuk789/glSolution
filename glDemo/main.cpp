#define _USE_MATH_DEFINES

#include "core.h"

#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds
#include <cmath>

// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();

void drawTriangle();
void drawPolygon(int _x, int _y, int _sides, float _radius);
void drawStar(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points);
void drawTank(float _atX, float _atY, float _orientation);
void drawOcto(float _atX, float _atY, float _radius, float _points);
void drawOverLap();
void drawSemiCircle();


float randomFloat(float max);
void movePoly();

int main() {

	//
	// 1. Initialisation
	//

	//Seeded Random
	srand(time(NULL));

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();


	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black

	gluOrtho2D(-1, 1, -1, 1);

	//
	// 2. Main loop
	// 
	renderScene();

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		//renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}



// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render objects here...
	//Triangle 1
	/*
	glBegin(GL_TRIANGLES);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);

	//Triangle 2
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);

	glEnd();
	*/

	//drawTriangle();
	//drawPolygon(1, 2, 3, 4.5);
	//drawStar(0.0f, 0.0f, 0.4f, 0.8f, 5);
	//drawTank(0.1, 0.1, 0.1);
	//drawOcto(0.0f, 0.0f, 0.5f, 8.0f);
	drawOverLap();
	//drawSemiCircle();
}

void drawTriangle()
{
	glBegin(GL_TRIANGLES);

	glColor3ub(255, 0, 255);
	glVertex2f(-0.5f, -0.5f);
	glColor3ub(0, 255, 0);
	glVertex2f(0.0f, 0.5f);
	glColor3ub(0, 0, 255);
	glVertex2f(0.5f, -0.5f);


	glEnd();
}

void drawPolygon(int _x, int _y, int _sides, float _radius)
{
	//Colour Random
	//glColor3f(randomFloat(), randomFloat(), randomFloat());

	glBegin(GL_POLYGON);

	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);

	//glVertex2f(-randomFloat(), -randomFloat());
	//glVertex2f(-randomFloat(), randomFloat());
	//glVertex2f(randomFloat(), randomFloat());
	//glVertex2f(randomFloat(), -randomFloat());
	glEnd();

	//std::this_thread::sleep_for(std::chrono::seconds(1));

}

void drawStar(float _atX, float _atY, float _innerRadius,
	float _outerRadius, int _points)
{
	/*glBegin(GL_LINE_LOOP);

	glVertex2f(0.0, 0.25f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.25f, 0.08f);
	glVertex2f(0.15f, -0.05f);
	glVertex2f(0.25f, -0.25f);
	glVertex2f(0.0f, -0.125f);
	glVertex2f(-0.25f, -0.25f);
	glVertex2f(-0.15f, -0.05f);
	glVertex2f(-0.25f, 0.08f);
	glVertex2f(-0.1f, 0.1f);

	glEnd();*/

	// Start the line loop to create the star
	glBegin(GL_TRIANGLE_FAN);

	//glColor4f(1.0f, 1.0f, 1.0f,0.0f);
	glVertex2f(_atX, _atY);

	// Angle between each point on the star
	// Divide by _points to get angle between each outer point
	float angleStep = M_PI / _points;
	int starPoints = 2 * _points;
	// Loop to draw the star
	for (int i = 0; i <= starPoints; ++i) 
	{
		
		float angle = i * angleStep;
		float radius = (i % 2 == 0) ? _outerRadius : _innerRadius; // Alternate between outer and inner radius

		// Calculate x and y based on angle and radius
		float x = _atX + cos(angle) * radius;
		float y = _atY + sin(angle) * radius;

		// Pass the vertex to OpenGL
		if (i % 2 == 0)
		{
			glColor3f(randomFloat(1.0), randomFloat(1.0), randomFloat(1.0));
		}
		//glColor3f(randomFloat(1.0), randomFloat(1.0), randomFloat(1.0));
		glVertex2f(x, y);
	}

	// End the line loop to finish drawing the star
	glEnd();

}

void drawTank(float _atX, float _atY, float _orientation) 
{
	// Render body
	glBegin(GL_LINE_LOOP);

	glVertex2f(-0.75f, 0.4f);
	glVertex2f(0.75f, 0.4f);
	glVertex2f(0.75f, -0.4f);
	glVertex2f(-0.75f, -0.4f);

	glEnd();

	// Render gun
	glBegin(GL_LINE_LOOP);

	glVertex2f(-0.5f, 0.3f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(-0.5f, -0.3f);

	glEnd();

}

void drawOcto(float _atX, float _atY, float _radius, float _points)
{
	const float  thetaStepSize = (2.0f * M_PI) / 8.0f;

	glBegin(GL_TRIANGLE_FAN);

	//glVertex2f(_atX, _atY);

	float angleStep = 2 * M_PI / _points;
	
	for (int i = 0; i < _points; i++)
	{
		float x = cosf(thetaStepSize * float(i));
		float y = sinf(thetaStepSize * float(i));

		glVertex2f(x, y);
	}

	glEnd();

}

void drawOverLap()
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glBegin(GL_QUADS);
	glColor3ub(0, 255, 0);
	glVertex2f(-0.9f, -0.9f);
	glVertex2f(-0.9f, 0.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.1f, -0.9f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 255);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex2f(-0.2f, -0.9f);
	glVertex2f(-0.2f, 0.2f);
	glVertex2f(0.9f, 0.2f);
	glVertex2f(0.9f, -0.9f);
	glEnd();

}

void drawSemiCircle()
{
	glShadeModel(GL_FLAT);

	glBegin(GL_TRIANGLE_STRIP);

	glColor3ub(0, 255, 255);
	glVertex2f(-0.25f, 0.0f);

	glColor3ub(0, 255, 255);
	glVertex2f(-0.75f, 0.0f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.216506351f, 0.125f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.649519053f, 0.375f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.125, 0.216506351f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.375f, 0.649519053f);

	glColor3ub(0, 255, 0);
	glVertex2f(0.0f, 0.25f);

	glColor3ub(0, 255, 0);
	glVertex2f(0.0f, 0.75f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.125f, 0.216506351f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.375f, 0.649519053f);

	glColor3ub(0, 0, 255);
	glVertex2f(0.216506351f, 0.125f);

	glColor3ub(0, 0, 255);
	glVertex2f(0.649519053f, 0.375f);

	glColor3ub(255, 0, 255);
	glVertex2f(0.25f, 0.0f);

	glColor3ub(255, 0, 255);
	glVertex2f(0.75f, 0.0f);

	glEnd();
}

void movePoly()
{

}


float randomFloat(float max) {
	return (float)rand() / (float)RAND_MAX * max;
}

int randomInt() {
	return (int)rand() / (int)RAND_MAX;
}



// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;

		default:
		{
		}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() 
{

}

