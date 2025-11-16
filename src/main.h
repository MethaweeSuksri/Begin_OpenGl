#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.h"
#include <thread>
#include <stb_image.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLFWwindow* glfwWindowSetup();
void loadBuffer(const float[], size_t,
                const unsigned int[], size_t, 
                unsigned int&, unsigned int&, unsigned int&);

void loadTexture(unsigned int&,unsigned int&);

void framebuffer_size_callback(GLFWwindow *, int , int );
void processInput(GLFWwindow *window);
