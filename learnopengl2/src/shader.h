#ifndef APP_SHADER
#define APP_SHADER
#include <iostream>
#include <fstream>
#include <sstream>
#include "includes.h"

class Shader
{
private:
    unsigned int createShader(std::string shaderPath, unsigned int shaderType);
    std::string getShaderCode(std::string shaderPath);
public:
    unsigned int shaderID;
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    void use();
    void setUniform1i(std::string name, int value);
    ~Shader();
};
#endif