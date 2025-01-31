
#include "core.h"
#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds

// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();
void DrawPolygon(int _x, int _y, int _sides, float _radius);
float randomFloat();
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


	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
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
	DrawPolygon(1, 2, 3, 4.5);


}

void DrawPolygon(int _x, int _y, int _sides, float _radius)
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

void movePoly()
{

}


float randomFloat() {
	return (float)rand() / (float)RAND_MAX;
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
void updateScene() {
}

