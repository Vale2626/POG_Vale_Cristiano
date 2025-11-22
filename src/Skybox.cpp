#include <glad/glad.h>        // per glGenTextures, glBindTexture, glTexImage2D, ecc.
#include <vector>             // per std::vector
#include <string>             // per std::string
#include <iostream>           // per std::cout
#include <stb_image.h>        // per stbi_load

// Carica le 6 facce della cubemap e restituisce l'ID della texture
unsigned int loadCubemap(const std::vector<std::string> &facce)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for(unsigned int i = 0; i < facce.size(); i++)
    {
        unsigned char *data = stbi_load(facce[i].c_str(), &width, &height, &nrChannels, 0);
        if(data)
        {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std :: cout<<"Caricaento cubemap fallito: "<< facce[i] << std :: endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;

}
