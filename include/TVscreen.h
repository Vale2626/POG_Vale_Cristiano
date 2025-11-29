#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "Matrix4.h"

class TVscreen
{
    public:
        TVscreen();
        ~TVscreen();

        void addChannel(Texture* tex);

        //cambio canali
        void nextChannel();
        void prevChannel();
        void setChannel(int index);
        void ChangeChannel(GLFWwindow* window, double nowSeconds);        //cambio canali da tastiera

        void draw(GLuint shaderProgram, const Matrix4& model);

    private:

        VAO vao;
        VBO* vbo;

        std :: vector<Texture*> channels;
        int currentChannel;
        double lastChannelSwitch;
};
