#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.h"
#include <thread>
#include <stb_image.h>
#include "glm/glm.hpp"
#include "main.h"




/*
    1. set up window
    2. vertex preparation
    3. set up shader
    4. import texture
    5. render loop
*/

int main()
{

    // 1. Set up window
    GLFWwindow*  window;
    try
    {
        window = glfwWindowSetup();    
    }catch(const std::runtime_error& e){
        std::cerr << "Error : " << e.what() <<"\n";
    }

    //-----------------------------------------------------------------------------------------------------------------
    
    // 2. vertex preparation

    //  define vertices 
    constexpr float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

    //EBO
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        0, 2, 3,   // first triangle
    }; 

    // Buffer generation, vertex array generation
    unsigned int VBO,VAO, EBO;
    
    loadBuffer( vertices,sizeof(vertices), indices, sizeof(indices), VBO, VAO, EBO);


    //-----------------------------------------------------------------------------------------------------------------
    
    // 3. set up shader    
    Shader theShader("src/shaders/shader.vs","src/shaders/shader.fs");

    //-----------------------------------------------------------------------------------------------------------------
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // 4. import texture

    //create and bind gl texture
    unsigned int texture;
    loadTexture(texture);
    
    //-----------------------------------------------------------------------------------------------------------------
    
    // 5. render loop

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

         // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        //activate shader program
        theShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    // clear all allocated resource
    glfwTerminate();

    return 0;
}


// 1. Set up window
GLFWwindow*  glfwWindowSetup()
{

    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // this is required for mac

    

    // ***!!!create window object!!!***
    GLFWwindow *window = glfwCreateWindow(800, 600, "Begin_OpenGl", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // load glad of opengl function pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // this function call use the resize callback fucntion to readjust the viewport to fit the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void loadBuffer( const float vertices[], size_t vertices_size , const unsigned int indices[], size_t indices_size , unsigned int& VBO, unsigned int& VAO, unsigned int& EBO)
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1,&VAO);

    // Bind VAO first
    glBindVertexArray(VAO);

    // buffer binding (bind VBO to GL_ARRAY_BUFFER)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // allocate the buffer to VRAM
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    // specified how OpenGL should interpret the vertex data 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    // specify color attribute vertex array pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  


    //  create element buffer object for specifying the order of drawing multiple triangle
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW); 

};

void loadTexture(unsigned int& texture)
{
    glGenTextures(1, &texture); 
    glBindTexture(GL_TEXTURE_2D, texture);

    //import the image data
    int containerWidth, containerHeight, nrChannels;
    unsigned char *data = stbi_load("textures/container.jpg", &containerWidth, &containerHeight, &nrChannels, 0); 

    if(data)
    {
        //generate texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, containerWidth, containerHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture\n";
    }

    //texture VAO
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  

    //we're done generating the texture so we'll delete the data (unsign char "container") 
    stbi_image_free(data);
}

// tell opengl about the render size everythime that user resize the window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
