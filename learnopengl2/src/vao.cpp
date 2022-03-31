#include "includes.h"
#include "vao.h"

VAO::VAO()
{
    glGenVertexArrays(1, &vao);
}

void VAO::bind() {
    glBindVertexArray(vao);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::setVertices(float vertices[], unsigned int size) {
    bind();
    this->vertices = vertices;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    unbind();
}

void VAO::setIndices(unsigned int indices[], unsigned int size) {
    bind();
    this->indices = indices;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    unbind();
}

void VAO::enablePointer(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) {
    bind();
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *) (offset * sizeof(float)));
    glEnableVertexAttribArray(index);
    unbind();
}

void VAO::disablePointer(unsigned int index) {
    bind();
    glDisableVertexAttribArray(index);
    unbind();
}

void VAO::draw(Shader shader) {
    shader.use();
    bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    unbind();
}

void VAO::drawArrays(Shader shader) {
    shader.use();
    bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    unbind();
}

VAO::~VAO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}