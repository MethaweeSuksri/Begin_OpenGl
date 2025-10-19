#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// vertex shader objst
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

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



int main()
{
    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // this is required for mac

    int success;
    char infoLog[512];

    // ***!!!create window object!!!***
    GLFWwindow *window = glfwCreateWindow(800, 600, "Begin_OpenGl", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // load glad of opengl function pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // this function call use the resize callback fucntion to readjust the viewport to fit the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //-----------------------------------------------------------------------------------------------------------------
    //  send vertices data to gpu
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    // Buffer generation, vertex array generation
    unsigned int VBO,VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1,&VAO);

    // Bind VAO first
    glBindVertexArray(VAO);

    // buffer binding (bind VBO to GL_ARRAY_BUFFER)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // allocate the buffer to VRAM
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // specified how OpenGL should interpret the vertex data 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    //-----------------------------------------------------------------------------------------------------------------
    //  create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // link vertexShader code to shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

        // shader compile error check
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

    // create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // link fragmentShader code to shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

        // shader compile error check
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

    // create shader program object (basically pipelining)
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // attach shader together
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

        // check shader linking error
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

    

    // after linking wee dont need these anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

    //-----------------------------------------------------------------------------------------------------------------
    
    
    //-----------------------------------------------------------------------------------------------------------------
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //activate shader program
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clear all allocated resource
    glfwTerminate();

    return 0;
}
