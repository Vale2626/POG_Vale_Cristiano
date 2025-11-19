#pragma once
#include <glad/glad.h>

class EBO {
public:
    GLuint ID;

    EBO(const void* data, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
};
