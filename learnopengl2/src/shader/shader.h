#include "utils/disposable.h"

#ifndef APP_SHADER
#define APP_SHADER
class Shader: public Disposable {
    public:
        unsigned int id;
        Shader();
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        void use();
        void dispose() override;
        void uniform1f(const char* name, float value);
        void uniform2f(const char* name, float value1, float value2);
        void uniform3f(const char* name, float value1, float value2, float value3);
        void uniform4f(const char* name, float value1, float value2, float value3, float value4);
    private:
        unsigned int createShader(const char* shaderPath, unsigned int shaderType);
};
#endif