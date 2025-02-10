#define _USE_MATH_DEFINES

#include "core.h"
#include "MyShapes.h"

using namespace std;


// global variables
mt19937 engine;
uniform_real_distribution<float> range;
uniform_real_distribution<float> colourRange;

//vector<float> xValues;
//vector<float> yValues;

vector<glm::vec2> vertexCoords;
vector<glm::vec4> coordColour;


// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();

int currentFunction = 0;
void changeFunction();

/*void drawTriangle();
void drawPolygon(int _x, int _y, int _sides, float _radius);
void drawStar(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points);
void drawTank(float _atX, float _atY, float _orientation);
void drawOcto(float _atX, float _atY, float _radius, float _points);
void drawOverLap();
void drawSemiCircle();


float randomFloat(float max);
void movePoly();*/

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
		cout << "Failed to create GLFW window!\n";
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

	random_device rd;
	engine = mt19937(rd());
	range = uniform_real_distribution<float>(-1.0f, 1.0f);
	colourRange = uniform_real_distribution<float>(0.0f, 1.0f);

	//Create 2 vector objects containing 100 elements all initialised to 0.0
	//xValues = vector<float>(100, 0.0f);
	//yValues = vector<float>(100, 0.0f);

	//replacement vertexcoords container
	vertexCoords = vector<glm::vec2>(100, glm::vec2(0.0f, 0.0f));
	coordColour = vector<glm::vec4>(100, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

	// Iterate 100 times (once for each vertex) 
	//and calculate and store the random x and y values

	for (int i = 0; i < 100; i++)
	{
		float x = range(engine);
		float y = range(engine);

		float r = range(engine);
		float g = range(engine);
		float b = range(engine);
		float a = range(engine);

		//float size = range(engine);

		//xValues[i] = x;
		//yValues[i] = y;

		vertexCoords[i] = glm::vec2(x, y);
		coordColour[i] = glm::vec4(r, g, b, a);
	}

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

	glPointSize(randomFloat(100.0f));
	glColor3ub(0, 180, 0);

	glBegin(GL_POINTS);

	// Render objects here...

	for (int i = 0; i < 100; i++)
	{
		//glPointSize()
		glVertex2f(vertexCoords[i].x, vertexCoords[i].y);
		glColor4f(coordColour[i].r, coordColour[i].g, coordColour[i].b, coordColour[i].a);
	}

	glEnd();
	
	//drawTriangle();
	//drawPolygon(1, 2, 3, 4.5);
	//drawStar(0.0f, 0.0f, 0.4f, 0.8f, 5);
	//drawTank(0.1, 0.1, 0.1);
	//drawOcto(0.0f, 0.0f, 0.5f, 8.0f);
	//drawOverLap();
	//drawSemiCircle();
}


// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}

void changeFunction()
{
	currentFunction = (currentFunction + 1) % 7;

	switch (currentFunction)
	{
	case 0: drawTriangle();
		break;
	case 1: drawPolygon(1, 2, 3, 4.5);
		break;
	case 2: drawStar(0.0f, 0.0f, 0.4f, 0.8f, 5);
		break;
	case 3: drawTank(0.1, 0.1, 0.1);
		break;
	case 4: drawOcto(0.0f, 0.0f, 0.5f, 8.0f);
		break;
	case 5: drawOverLap();
		break;
	case 6: drawSemiCircle();
		break;

	default:
		break;
	}
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

		case GLFW_KEY_SPACE:
			changeFunction();
			break;

		case GLFW_KEY_LEFT_SHIFT:
			renderScene();
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

