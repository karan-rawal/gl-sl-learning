#ifndef APP_VAO
#define APP_VAO
#include "shader.h"

class VAO
{
private:
    float *vertices;
    unsigned int *indices;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
public:
    VAO();
    void bind();
    void setVertices(float *vertices, unsigned int size);
    void setIndices(unsigned int *indices, unsigned int size);
    void unbind();
    void enablePointer(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset);
    void disablePointer(unsigned int index);
    void draw(Shader shader);
    ~VAO();
};
#endif