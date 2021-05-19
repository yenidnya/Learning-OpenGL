#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void resize_window(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow *initialize_GL()
{

	// Initalize Library;
	glfwInit();
	// Set version to 3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Set version to x.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set profile to core profile in order to use smaller core functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Playground", NULL, NULL);
	if (window == NULL)
	{
		cout << "Couldn't create GLFW Window" << endl;
		glfwTerminate();
		return NULL;
	}

	// set created window to glfw's context
	glfwMakeContextCurrent(window);

	// Get OS specific function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Couldn't initalize GLAD" << endl;
		return NULL;
	}

	glViewport(0, 0, 800, 600);

	// resize callback
	glfwSetFramebufferSizeCallback(window, resize_window);

	return window;
}

void inputHandler(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

const char *vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
const char *fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";

int main()
{

	GLFWwindow *window = initialize_GL();
	if (window == NULL)
		return -1;

	float veritces[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f};

	// Create Vertex Shader;
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader; 
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// create shader program where shaders get linked
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// we can delete shader objects after linking them;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create Vertex Buffer Object and Vertex Array Object
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	// Set VAO as current state's object
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(veritces), veritces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the 
	// vertex attribute's bound vertex buffer object so afterwards we can safely unbind	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		inputHandler(window);

		glClearColor(0.2f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}