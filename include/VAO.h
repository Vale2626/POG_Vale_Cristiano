#pragma once
#include <glad/glad.h>  // per GLuint
#include "VBO.h"        // per il tipo VBO

class VAO {
public:
    GLuint ID;

    VAO();
    void LinkVBO(VBO& vbo, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};
