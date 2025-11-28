#include "Mesh.h"
#include <cstddef> // Per usare 'offsetof'
#include <string>

Mesh :: Mesh(std :: vector<Vertex> vertici, std :: vector <unsigned int> indici, std :: vector<std :: shared_ptr<Texture>> textures):

    vertici(vertici),
    indici(indici),
    textures(textures),
    vao(),
    vbo(vertici.data(), vertici.size() * sizeof(Vertex)),   // Costruisce vbo con i dati
    ebo(indici.data(), indici.size() * sizeof(unsigned int))  // Costruisce ebo con i dati

    //.data() restituisce un puntatore (un indirizzo di memoria) al primo elemento dell'array
    //interno che std::vector usa per memorizzare tutti i suoi dati.

{
    setupMesh();    //// Chiama la funzione privata per configurare i buffer OpenGL
}

//implementazione della funzione setupMesh().  Qui c'è la logica che prima stava nel main
void Mesh::setupMesh()
{
    //Associa il VAO
    vao.Bind();

    //Associa VBO e EBO (ora sono già creati!

    vbo.Bind();
    ebo.Bind();

    GLsizei stride = sizeof(Vertex); // lo stride totale, ovvero distanza tra l'inizio di un vertice e l'inizio del successivo, sara 44 byte (V3+V3+V3+V2)

    // Attributo 0: Posizione (3 float)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    // Attributo 1: Colore (3 float)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(1);

    // Attributo 2: Normale (3 float)
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);

    // Attributo 3: Coordinate Texture (2 float)
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(3);

    vao.Unbind();   //consigliato sbloccare il VAO, VBO e EBO
    vbo.Unbind();
    ebo.Unbind();

}

//Implementazione della funzione Draw

void Mesh::Draw()
{
    
    //Attiva tutte le texture caricate dalla mesh
    unsigned int unit = 0;
    bool hasUnlitTexture = false;
    for (auto& tex : textures)   // <— il vettore si chiama "textures"
    {
       if (tex)
       {
            tex->Bind(unit);
            // Bypassa l'illuminazione su texture piatte o vetro
            if (tex->path.find("TextureMaterial_baseColor.png") != std::string::npos ||
                tex->path.find("glass") != std::string::npos) {
                hasUnlitTexture = true;
            }
       }
       unit++;
    }

    // Se lo shader supporta l'uniform forceUnlit, impostalo per questa mesh
    GLint currentProg = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProg);
    if (currentProg != 0) {
        GLint unlitLoc = glGetUniformLocation(static_cast<GLuint>(currentProg), "forceUnlit");
        if (unlitLoc != -1) {
            glUniform1i(unlitLoc, hasUnlitTexture ? 1 : 0);
        }
    }

    // Disegna la mesh
    vao.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indici.size()), GL_UNSIGNED_INT, 0);
    vao.Unbind();

    glActiveTexture(GL_TEXTURE0);  // reset opzionale
}


void Mesh :: Delete()
{
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}
