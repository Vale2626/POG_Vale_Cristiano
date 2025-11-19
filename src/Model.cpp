#include "Model.h"
#include <iostream>
#include <cstring>

Model :: Model(std :: string path)
{
    directory = path.substr(0, path.find_last_of('/'));     //Salva la directory (es. "modelli/") per trovare i file .jpg
    loadModel(path);        //path è la posizione del file del modello 3D sul tuo computer.
}

void Model :: Draw()        //Scorre tutti i mesh contenuti nel modello e li disegna
{
    for(unsigned int i = 0; i < meshes.size(); i++)  
    {
        meshes[i].Draw();
    }
}

void Model :: Delete()      //Scorre tutti i mesh e chiama la loro funzione Delete()
{
    for(unsigned int i = 0; i< meshes.size(); i++)
    {
        meshes[i].Delete();
    }
}

void Model :: loadModel(std :: string path)
{
    Assimp :: Importer importer;        //creazione di un istanza di Assimp

    //Lettura del file
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // aiProcess_Triangulate: Se il modello non è fatto di triangoli, li crea.
    // aiProcess_FlipUVs: Inverte le coordinate Y delle texture (spesso necessario)

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)    //controllo errori
    {
        std::cout << "ERRORE::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);       //Inizia a processare i nodi dalla radices
}

void Model :: processNode(aiNode *node, const aiScene *scene)
{
    // Processa tutti i mesh del nodo corrente
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        //scene->mMeshes contiene tutti i mesh, 
        //node->mMeshes[i] è solo un indice per quella lista
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        
       
        meshes.push_back(processMesh(mesh, scene));
    }

    // Fa lo stesso per tutti i "figli" di questo nodo
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

//traduzione di Assimp nella mia libreria
 
Mesh Model :: processMesh(aiMesh *mesh, const aiScene *scene)
{
    std :: vector<Vertex> vertici;
    std :: vector<unsigned int> indici;
    std :: vector<std :: shared_ptr<Texture>> texture;     //shared_ptr evita cancellazioni multiple della stessa texture

    //processa i vertici
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex; // Il nostro struct Vertex!
        vertex.Position = Vector3(mesh -> mVertices[i].x, mesh -> mVertices[i].y, mesh -> mVertices[i].z);       //TRADUZIONE: // Assimp (aiVector3D) -> MIO (Vector3)

        //mVertices[i] È un nome di variabile che appartiene alla libreria Assimp. È un membro pubblico della classe aiMesh che Assimp ci fornisce.

        //Normali
        if(mesh -> HasNormals())
        {
            vertex.Normal = Vector3(mesh -> mNormals[i].x, mesh -> mNormals[i].y, mesh -> mNormals[i].z);
        }

        //Coordinate Texture
        if(mesh -> mTextureCoords[0])
        {
            vertex.TexCoords = Vector2(mesh -> mTextureCoords[0][i].x, mesh -> mTextureCoords[0][i].y);
        }
        else
        {
            vertex.TexCoords = Vector2(0.0f, 0.0f);
        }

        //Colori (i modelli raramente li usano)
        vertex.Color = Vector3(1.0f, 1.0f, 1.0f);

        vertici.push_back(vertex);

    }

    // 2. Processa gli Indici
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // Assimp si assicura (con aiProcess_Triangulate) che ogni faccia
        // abbia 3 indici, li aggiungiamo alla nostra lista
        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indici.push_back(face.mIndices[j]);
        }
    }

    // 3. Processa i Materiali (Texture) --> DA FARE ANCORA

        if(mesh -> mMaterialIndex >= 0)
        {
            aiMaterial* material = scene -> mMaterials[mesh -> mMaterialIndex];

            //Caricamento solo della texture DIFFUSE (colore base)
            std :: vector<std :: shared_ptr<Texture>> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE);
            texture.insert(texture.end(), diffuseMaps.begin(), diffuseMaps.end());

        // (posso fare lo stesso per le mappe speculari se il mio shader le supporta)
        // std::vector<Texture> specularMaps = loadMaterialtexture(material, aiTextureType_SPECULAR);
        // texture.insert(texture.end(), specularMaps.begin(), specularMaps.end());
    }
 
   
    // 4. Crea e restituisce il nostro oggetto Mesh
    return Mesh(vertici, indici, texture);
}

std :: vector<std :: shared_ptr<Texture>> Model :: loadMaterialTexture(aiMaterial *mat, aiTextureType Type)
{
    std::cout << "--- Trovate " << mat->GetTextureCount(Type) << " texture di tipo " << Type << " ---" << std::endl;
    std :: vector<std :: shared_ptr<Texture>> texture;
    for(unsigned int i = 0; i < mat -> GetTextureCount(Type); i++)
    {
        aiString str;
        mat -> GetTexture(Type, i, &str);   /// Ottiengo così il nome del file (es. "backpack_diffuse.jpg")

       std :: string pathCompleto = this -> directory + '/' + std :: string(str.C_Str());
        // --- Ottimizzazione: controlla se l'abbiamo già caricATA ---
        bool skip = false;
        for(unsigned int j = 0; j < texture_loaded.size(); j++)
        {
            // Per far funzionare questo, la tua classe Texture
            // DEVE avere un membro: public: std::string path;
            if(std::strcmp(texture_loaded[j]->path.data(), pathCompleto.c_str()) == 0)
            {
                texture.push_back(texture_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        { 
            // Se non è in cache, creala e salvala
            auto tex = std :: make_shared<Texture>(pathCompleto.c_str()); // Usa il costruttore di Texture

            //Texture è il nome del vettore (dichiarato all'inizio della funzione processMesh o loadMaterialTextures).
            //tex è il singolo oggetto texture (che hai creato con Texture texture(pathCompleto.c_str());).
            // !! IMPORTANTE !!
            // Aggiungi 'public: std::string path;' alla tua classe Texture.h
            // e salvalo qui per far funzionare la cache
            tex->path = pathCompleto; 
            
            texture.push_back(tex);
            texture_loaded.push_back(tex); // Aggiungi alla cache
        }
    }
    return texture;
}
