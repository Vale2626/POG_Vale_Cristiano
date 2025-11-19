#ifndef MESH_H
#define MESH_H

#include<vector>
#include<memory>
#include "Vector3.h"
#include <glad/glad.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

struct Vertex {     //la struct Vertex è come un contenitore che tiene tutte le 
                    //informazioni relative a un singolo vertice

    Vector3 Position;
    Vector3 Color;
    Vector3 Normal;
    Vector2 TexCoords;
};

class Mesh{

    public:
        std :: vector<Vertex> vertici;
        std :: vector<unsigned int> indici;
        std :: vector<std :: shared_ptr<Texture>> textures;    // shared_ptr evita cancellazioni multiple della stessa texture
        VAO vao;    //il VAO appartiene al MESH
        
        //COSTRUTTORE -->Prende un vettore di vertici e un vettore di indici e imposta i buffer OpenGL.
        Mesh(std :: vector<Vertex> vertici, std :: vector<unsigned int> indici, std :: vector<std :: shared_ptr<Texture>> textures);

        void Draw();        //disegna la MESH

        void Delete();

        private:
            VBO vbo;
            EBO ebo;

            void setupMesh();   //Funzione privata per configurare tutti i buffer OpenGL (VAO, VBO, EBO) e gli attributi dei vertici.
};

#endif
