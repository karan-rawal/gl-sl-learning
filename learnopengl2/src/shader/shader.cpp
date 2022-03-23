#include "includes.h"
#include "shader/shader.h"

Shader::Shader() {}

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
    unsigned int vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragmentShader);
    glLinkProgram(this->id);
}

unsigned int Shader::createShader(const char* shaderPath, unsigned int shaderType) {
    std::fstream inputFile(shaderPath);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string shaderCodeString = buffer.str();
    const char* shaderCode = shaderCodeString.c_str();

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        int infoLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        char infoMessage[infoLength];
        glGetShaderInfoLog(shader, infoLength, NULL, infoMessage);
        std::cout << "Failed to compile shader " << shaderPath << ": " << infoMessage << std::endl;
        inputFile.close();
        return -1;
    }

    inputFile.close();
    return shader;
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::uniform1f(const char *name, float value) {
    unsigned int uniformLocation = glGetUniformLocation(this->id, name);
    glUniform1f(uniformLocation, value);
}

void Shader::uniform2f(const char *name, float value1, float value2) {
    unsigned int uniformLocation = glGetUniformLocation(this->id, name);
    glUniform2f(uniformLocation, value1, value2);
}

void Shader::uniform3f(const char *name, float value1, float value2, float value3) {
    unsigned int uniformLocation = glGetUniformLocation(this->id, name);
    glUniform3f(uniformLocation, value1, value2, value3);
}

void Shader::uniform4f(const char *name, float value1, float value2, float value3, float value4) {
    unsigned int uniformLocation = glGetUniformLocation(this->id, name);
    glUniform4f(uniformLocation, value1, value2, value3, value4);
}

void Shader::dispose() {
    glDeleteProgram(this->id);
}