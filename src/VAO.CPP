#include "VAO.h"
#include "VBO.h"

VAO::VAO() { glGenVertexArrays(1, &ID); }

void VAO::LinkVBO(VBO& vbo, GLuint layout) {
    glBindVertexArray(ID);
    vbo.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
    glBindVertexArray(0);
}

void VAO::Bind()   { glBindVertexArray(ID); }
void VAO::Unbind() { glBindVertexArray(0); }
void VAO::Delete() { glDeleteVertexArrays(1, &ID); }
