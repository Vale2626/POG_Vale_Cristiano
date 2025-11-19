#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::ifstream vFile(vertexPath), fFile(fragmentPath);
    std::stringstream vbuf, fbuf; vbuf << vFile.rdbuf(); fbuf << fFile.rdbuf();
    std::string v = vbuf.str(), f = fbuf.str();
    const char* vs = v.c_str(); const char* fs = f.c_str();

    GLuint V = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(V, 1, &vs, nullptr);
    glCompileShader(V);

    GLuint F = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(F, 1, &fs, nullptr);
    glCompileShader(F);

    ID = glCreateProgram();
    glAttachShader(ID, V);
    glAttachShader(ID, F);
    glLinkProgram(ID);
    glDeleteShader(V);
    glDeleteShader(F);
}

void Shader::Use()   { glUseProgram(ID); }
void Shader::Delete(){ glDeleteProgram(ID); }
