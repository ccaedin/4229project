#include "Shader.h"
#include <fstream>
#include <vector>

GLint Shader::compileShader(GLuint shaderID, const char *&shaderCode)
{
    GLint result;
    int logLength;

    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);

    // check
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    if (!result)
    {
        std::vector<char> error(logLength);
        glGetShaderInfoLog(shaderID, logLength, NULL, &error[0]);
        //get shader type
        GLint shaderType;
        glGetShaderiv(shaderID, GL_SHADER_TYPE, &shaderType);
        std::string shaderTypeStr;
        switch(shaderType)
        {
            case GL_VERTEX_SHADER:
                shaderTypeStr = "vertex";
                break;
            case GL_FRAGMENT_SHADER:
                shaderTypeStr = "fragment";
                break;
            case GL_GEOMETRY_SHADER:
                shaderTypeStr = "geometry";
                break;
            default:
                shaderTypeStr = "shader";
                break;
        }
        std::cout << "Failed to compile " << shaderTypeStr << " shader" << std::endl;
        std::cout << &error[0] << std::endl;
        this->error = 2;
    }
    return result;
}
Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile(vertexPath, std::ios::in);
    std::ifstream fShaderFile(fragmentPath, std::ios::in);

    if (vShaderFile.is_open())
    {
        //read entire file to string
        std::string line;
        while (getline(vShaderFile, line))
        {
            vertexCode += line + "\n";
        }
        vShaderFile.close();
    }
    else
    {
        std::cout << "Failed to open vertex shader file" << std::endl;
        error = 1;
    }


    if (fShaderFile.is_open())
    {
        //read entire file to string
        std::string line;
        while (getline(fShaderFile, line))
        {
            fragmentCode += line + "\n";
        }
        fShaderFile.close();
    }
    else
    {
        std::cout << "Failed to open fragment shader file" << std::endl;
        error = 1;
    }

    //compile
    const char *vShaderCode = vertexCode.c_str();
    compileShader(vertexShader, vShaderCode);
    const char *fShaderCode = fragmentCode.c_str();
    compileShader(fragmentShader, fShaderCode);

    //link
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    //check
    GLint result;
    int logLength;
    glGetProgramiv(ID, GL_LINK_STATUS, &result);
    glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &logLength);
    if (!result)
    {
        std::vector<char> error(logLength);
        glGetProgramInfoLog(ID, logLength, NULL, &error[0]);
        std::cout << "Failed to link shader program" << std::endl;
        std::cout << &error[0] << std::endl;
    }

    //cleanup
    glDetachShader(ID, vertexShader);
    glDetachShader(ID, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
    glDeleteProgram(ID);
}
