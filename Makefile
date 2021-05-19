CXX = g++

CXXFLAGS = -Wall -pedantic -g -fsanitize=address -Iinclude
GLFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl 

OBJ_ROOT = Objects
SRC = main.cpp include/glad/glad.c

playground: clean glad.o glfw3.o 
	$(CXX) $(CXXFLAGS) $(GLFLAGS) $(SRC) -o playground && ./playground

glad.o: include/glad/glad.h
	$(CXX) $(CXXFLAGS) $(GLFLAGS) -c include/glad/glad.h -o glad.o

glfw3.o: include/GLFW/glfw3.h
	$(CXX) $(CXXFLAGS) $(GLFLAGS) -c include/GLFW/glfw3.h -o glfw3.o

clean:
	rm -rf *.o playground