#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//costruttore
// In src/Texture.cpp

// In src/Texture.cpp

//COSTRUTTORE

Texture::Texture(const std::string& path) : ID_texture(0)
{
    this->path = path;
    int tex_width, tex_height, tex_channels;

    stbi_set_flip_vertically_on_load(true); 
    
    // FORZA 4 CANALI (RGBA)
    unsigned char* data = stbi_load(path.c_str(), &tex_width, &tex_height, &tex_channels, 4);

    if (data)
    {
        std::cout << "DEBUG: Texture " << path << " caricata. Dimensioni: " << tex_width << "x" << tex_height << std::endl;
        
        // --- MODIFICA 1: Cambia il formato interno (più flessibile sul Mac) ---
        GLenum source_format = GL_RGBA;
        GLenum internal_format = GL_RGBA; // CAMBIATO: Da GL_RGBA8 a GL_RGBA
        
        glGenTextures(1, &ID_texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ID_texture);

        // --- MODIFICA 2: Cambia i filtri per supportare i Mipmaps ---
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // o GL_REPEAT, come preferisci
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // o GL_REPEAT

        // ABILITA MIPMAPS: usa GL_NEAREST_MIPMAP_LINEAR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); 
        // Filtro di ingrandimento più semplice
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

        // Ora questo è corretto (GL_RGBA, GL_RGBA)
        glTexImage2D(
            GL_TEXTURE_2D, 0, internal_format, 
            tex_width, tex_height, 0, 
            source_format, GL_UNSIGNED_BYTE, data
        );
        
        // --- MODIFICA 3: Genera i Mipmaps (ora richiesto dal filtro MIN) ---
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else
    {
        // Blocco errore fatale...
        std::cout << "\n\n--- ERRORE FATALE ---\n" << std::endl;
        std::cout << "Impossibile caricare la texture al percorso: " << path << std::endl;
        std::cout << "\n---------------------\n\n" << std::endl;
        stbi_image_free(data); 
        exit(1); 
    }
}

// --- Distruttore ---
Texture::~Texture()
{
    // Il distruttore pulisce la risorsa OpenGL
    glDeleteTextures(1, &ID_texture); // Usa la tua variabile
}

// --- Bind ---
void Texture::Bind(GLuint slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID_texture); // Usa la tua variabile
}

// --- Unbind ---s
void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}


