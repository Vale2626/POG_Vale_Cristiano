#include "TVscreen.h"
#include <iostream> // opzionale

TVscreen::TVscreen()
    : vbo(nullptr)
    , currentChannel(0)
    , lastChannelSwitch(0.0)
{
    // rettangolo piccolo (solo fronte) con posizioni + UV
    float width = 0.2671f;
    float height = 0.29f;

    // UV ribaltati in verticale e specchiati in orizzontale per avere testo orientato correttamente
    float vertici[] = {
        -width / 2, -height / 2, 0.0f, 1.0f, 1.0f,
         width / 2, -height / 2, 0.0f, 0.0f, 1.0f,
         width / 2,  height / 2, 0.0f, 0.0f, 0.0f,

         width / 2,  height / 2, 0.0f, 0.0f, 0.0f,
        -width / 2,  height / 2, 0.0f, 1.0f, 0.0f,
        -width / 2, -height / 2, 0.0f, 1.0f, 1.0f
    };

    vao.Bind();

    vbo = new VBO(vertici, sizeof(vertici));

    // posizioni
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // UV (location 3 nello shader default)
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);
    // valori costanti per colore e normale per non lasciare attributi sporchi
    glDisableVertexAttribArray(1);
    glVertexAttrib3f(1, 1.0f, 1.0f, 1.0f);
    glDisableVertexAttribArray(2);
    glVertexAttrib3f(2, 0.0f, 0.0f, 1.0f);

    vao.Unbind();
}

TVscreen::~TVscreen()
{
    if (vbo) {
        vbo->Delete();
        delete vbo;
        vbo = nullptr;
    }
}

void TVscreen::addChannel(Texture* tex)
{
    if (tex) {
        channels.push_back(tex);
    }
}

void TVscreen::ChangeChannel(GLFWwindow* window, double nowSeconds)
{
   
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) setChannel(0);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) setChannel(1);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) setChannel(2);
}

void TVscreen::nextChannel()
{
    if (channels.empty()) return;
    currentChannel = (currentChannel + 1) % static_cast<int>(channels.size());
}

void TVscreen::prevChannel()
{
    if (channels.empty()) return;
    currentChannel = (currentChannel - 1 + static_cast<int>(channels.size())) % static_cast<int>(channels.size());
}

void TVscreen::setChannel(int index)
{
    if (index < 0 || index >= static_cast<int>(channels.size())) return;
    currentChannel = index;
}

void TVscreen::draw(GLuint shaderProgram, const Matrix4& model)
{
    if (channels.empty()) return;

    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    channels[currentChannel]->Bind(0);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "Model");
    if (modelLoc != -1) {
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.data());
    }

    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.Unbind();
}
