#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>
#include <stb_image.h>    //implementazione del codice di stb_image una sola volta

class Texture
{
    public:

        std :: string path;
        // Il costruttore carica la texture dal percorso specificato
        Texture(const std::string& path);

        ~Texture();    //distruttore che pulisce la memoria della GPU. Viene definito con la sintassi tilde (~).

        // Collega la texture a una specifica "unità" o "slot" di texture
        void Bind(GLuint slot = 0) const;

        void Unbind() const;

     private:
        GLuint ID_texture; // ID della texture (generato da OpenGL)
    
};

#endif // TEXTURE_H


