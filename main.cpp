#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void resize_window(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* initialize_GL() {
	
	// Initalize Library;
	glfwInit();
	// Set version to 3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Set version to x.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set profile to core profile in order to use smaller core functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "Playground", NULL, NULL);
	if (window == NULL) {
		cout << "Couldn't create GLFW Window" << endl;
		glfwTerminate();
		return NULL;
	}

	// set created window to glfw's context
	glfwMakeContextCurrent(window);

	// Get OS specific function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Couldn't initalize GLAD" << endl;
		return NULL;
	}
	
	glViewport(0, 0, 800, 600);
	
	// resize callback
	glfwSetFramebufferSizeCallback(window, resize_window);

	return window;
}


int main(){

	GLFWwindow* window = initialize_GL();
	if (window == NULL) return -1;

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}