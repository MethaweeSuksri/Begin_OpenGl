#include "shader.h"

//shader constructor
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{ 
    // this do
    // 1. get shader from shader file
    // 2. create program from shader 
    
    //for the souce shader code imported from files
    std::string vertexCode,fragmentCode;
    
    //for reading from file
    std::ifstream vShaderFile,fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        //open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        
        //read the string from opened file into streams
        std::stringstream vShaderStream,fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();

        //convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
         std::cout << "Vertex shader path: " << vertexPath << std::endl;
    std::cout << "Fragment shader path: " << fragmentPath << std::endl;
    std::cout << "Error: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile the shaders

    unsigned int vertexShader,fragmentShader;
    int success;
    char infoLog[512];

    //vert
    //create vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    // link vertexShader code to shader object
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

        // shader compile error check
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }


    //frag
    //create frag shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // link fragmentShader code to shader object
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

        // shader compile error check
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }


    // combine shader to program part
    // ID is in the shader class
    ID = glCreateProgram();

    // attach shader together
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

        // check shader linking error
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

    // after linking wee dont need these anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

}

void Shader::use() 
{ 
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 