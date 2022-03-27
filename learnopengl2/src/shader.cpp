#include "shader.h"

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    unsigned int vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Shader::createShader(std::string shaderPath, unsigned int shaderType) {
    std::string shaderCodeString = getShaderCode(shaderPath);
    const char* shaderCode = shaderCodeString.c_str();
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int status, infoLength;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        char info[infoLength];
        glGetShaderInfoLog(shader, infoLength, NULL, info);
        std::cout << "Failed to compile shader " << shaderPath << ": " << info << std::endl;
        return 0;
    }
    return shader;
}

std::string Shader::getShaderCode(std::string shaderPath) {
    std::fstream inputFile(shaderPath);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string sourceString = buffer.str();
    return sourceString;
}

void Shader::setUniform1i(std::string name, int value) {
    use();
    int uniformLocation = glGetUniformLocation(shaderID, name.c_str());
    glUniform1i(uniformLocation, value);
}

void Shader::setUniformMatrix4fv(std::string name, glm::mat4 value) {
    use();
    int uniformLocation = glGetUniformLocation(shaderID, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::use() {
    glUseProgram(shaderID);
}

Shader::~Shader()
{
    glDeleteProgram(shaderID);    
}