
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <algorithm> // std::max
#include <cmath>     // sinf, cosf
#include <fstream>
#include <sstream>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4.h>
#include "Camera.h"
#include "Texture.h"
#include <vector>
#include "Model.h"

Camera camera(0.0f, 0.0f, 0.48f);        //del tipo z, x , y.  --> distanza, angolo iniziale dela camera (rotazione attorno all asse Y), ALTEZZA CAMERA

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

        camera.ProcessInput(window);

}

    //funzione per legegre file di testo
    std::string loadTextFile(const char* filePath) {
    std::ifstream file(filePath);
    std::stringstream buf;
    buf << file.rdbuf();
    return buf.str();
    }

     // Funzione per controllare errori di compilazione/linkinig degli shader. Nel terminale, se scrivo ./app, mi compilerà il programma e mi dira quali errori sono presenti
    void checkShaderErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERRORE::SHADER_COMPILATION_ERROR di tipo: " << type << "\n" << infoLog << "\n -- -------------------------- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERRORE::PROGRAM_LINKING_ERROR di tipo: " << type << "\n" << infoLog << "\n -- ------------------ " << std::endl;
        }
    }
}



int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Progetto", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    int fbW, fbH;

    glfwGetFramebufferSize(window, &fbW, &fbH);
    glViewport(0, 0, fbW, fbH);     // su Mac (Retina) è fondamentale

    Matrix4 Projection = Matrix4::perspective(60.0f, (float)fbW/(float)fbH, 0.01f, 1000.0f);


    glEnable(GL_DEPTH_TEST);

    // --- Compilazione shader Oggetto ---
    std::string objectVSsrc = loadTextFile("shaders/default.vert"); // Assicurati che il percorso sia corretto!
    std::string objectFSsrc = loadTextFile("shaders/default.frag"); // Assicurati che il percorso sia corretto!

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* ovs = objectVSsrc.c_str();
    glShaderSource(vertexShader, 1, &ovs, nullptr);
    glCompileShader(vertexShader);
    checkShaderErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* ofs = objectFSsrc.c_str();
    glShaderSource(fragmentShader, 1, &ofs, nullptr);
    glCompileShader(fragmentShader);
    checkShaderErrors(fragmentShader, "FRAGMENT");

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkShaderErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // --- shader Luce ---
std::string lightVSsrc = loadTextFile("shaders/light.vert");
std::string lightFSsrc = loadTextFile("shaders/light.frag");

GLuint lightVS = glCreateShader(GL_VERTEX_SHADER);
const char* lvs = lightVSsrc.c_str();
glShaderSource(lightVS, 1, &lvs, nullptr);
glCompileShader(lightVS);
checkShaderErrors(lightVS, "VERTEX (Luce)");

GLuint lightFS = glCreateShader(GL_FRAGMENT_SHADER);
const char* lfs = lightFSsrc.c_str();
glShaderSource(lightFS, 1, &lfs, nullptr);
glCompileShader(lightFS);
checkShaderErrors(lightFS, "FRAGMENT (Luce)");

GLuint LightProgram = glCreateProgram();
glAttachShader(LightProgram, lightVS);
glAttachShader(LightProgram, lightFS);

glBindAttribLocation(LightProgram, 0, "aPos");

glLinkProgram(LightProgram);
checkShaderErrors(LightProgram, "PROGRAM (Luce)");

glDeleteShader(lightVS);
glDeleteShader(lightFS);



    // Vertici e indici per un parallelepipedo
    //Per ogni faccia, l’ordine dei vertici deve essere anti-orario (CCW) guardando la faccia di fronte. IMPORTANTISSIMO

    //RICORDA che l'orientamento delle coordinate UV delle texture vanno da destra --> verso sinistra <--

    /*std :: vector<Vertex> vertici =         //modifica dei vertici per il caricamento di un modello 3D,  ora abbiamod egli array dinamici
                                            //Un std::vector è un oggetto C++ che può crescere dinamicamente
    {
            //COORDINATE (Vector3)                          //COLORE (Vector3)                              //NORMALI (Vector3)                             TEXTURE UV (Vector2)


             //Faccia Davanti
             { Vector3 (-1.5f, -1.0f,  1.5f),               Vector3(1.0f, 0.0f, 0.0f),                      Vector3(0.0, 0.0, 1.0),                         Vector2(0.0f, 0.0f)},      //0
             { Vector3 (1.5f, -1.0f,  1.5f),                Vector3(1.0f, 0.0f, 0.0f),                      Vector3(0.0, 0.0, 1.0),                         Vector2(1.0f, 0.0f)},       //1
             { Vector3 (1.5f,  1.0f,   1.5f),               Vector3(1.0f, 0.0f, 0.0f),                      Vector3(0.0, 0.0, 1.0),                         Vector2(1.0f, 1.0f)},      //2
             { Vector3 (-1.5f,  1.0f,  1.5f),               Vector3(1.0f, 0.0f, 0.0f),                      Vector3(0.0, 0.0, 1.0),                         Vector2(0.0f, 1.0f)},      //3


            //Faccia Dietro
            { Vector3 (-1.5f, -1.0f, -1.5f),                Vector3(0.0f, 1.0f, 0.0f),                       Vector3(0.0, 0.0, -1.0),                       Vector2(0.0f, 0.0f)},      //4      
            { Vector3 (1.5f, -1.0f, -1.5f),                 Vector3(0.0f, 1.0f, 0.0f),                       Vector3(0.0, 0.0, -1.0),                       Vector2(1.0f, 0.0f)},      //5
            { Vector3 (1.5f,  1.0f, -1.5f),                 Vector3(0.0f, 1.0f, 0.0f),                       Vector3(0.0, 0.0, -1.0),                       Vector2(1.0f, 1.0f)},      //6
            { Vector3 (-1.5f, 1.0f, -1.5f),                 Vector3(0.0f, 1.0f, 0.0f),                       Vector3(0.0, 0.0, -1.0),                       Vector2(0.0f, 1.0f)},      //7


             //Faccia sinistra
            { Vector3 ( -1.5f, -1.0f, -1.5f),               Vector3(0.0f, 0.0f, 1.0f),                      Vector3(-1.0, 0.0, 0.0),                        Vector2(0.0f, 0.0f)},      //8
            { Vector3 (-1.5f, -1.0f,  1.5f),                Vector3(0.0f, 0.0f, 1.0f),                      Vector3(-1.0, 0.0, 0.0),                        Vector2(1.0f, 0.0f)},      //9
            { Vector3 (-1.5f,  1.0f,  1.5f),                Vector3(0.0f, 0.0f, 1.0f),                      Vector3(-1.0, 0.0, 0.0),                        Vector2(1.0f, 1.0f)},      //10
            { Vector3 (-1.5f,  1.0f, -1.5f),                Vector3(0.0f, 0.0f, 1.0f),                      Vector3(-1.0, 0.0, 0.0),                        Vector2(0.0f, 1.0f)},      //11


            // Faccia Destra
            { Vector3( 1.5f, -1.0f,  1.5f),                 Vector3(1.0f, 1.0f, 0.0f),                      Vector3(1.0f, 0.0f, 0.0f),                      Vector2(0.0f, 0.0f) },     // 12
            { Vector3( 1.5f, -1.0f, -1.5f),                 Vector3(1.0f, 1.0f, 0.0f),                      Vector3(1.0f, 0.0f, 0.0f),                      Vector2(1.0f, 0.0f) },     // 13
            { Vector3( 1.5f,  1.0f, -1.5f),                 Vector3(1.0f, 1.0f, 0.0f),                      Vector3(1.0f, 0.0f, 0.0f),                      Vector2(1.0f, 1.0f) },     // 14
            { Vector3( 1.5f,  1.0f,  1.5f),                 Vector3(1.0f, 1.0f, 0.0f),                      Vector3(1.0f, 0.0f, 0.0f),                      Vector2(0.0f, 1.0f) },     // 15


            // Faccia Sopra
            { Vector3(-1.5f,  1.0f,  1.5f),                 Vector3(1.0f, 0.0f, 1.0f),                      Vector3(0.0f, 1.0f, 0.0f),                      Vector2(0.0f, 0.0f) },      // 16
            { Vector3( 1.5f,  1.0f,  1.5f),                 Vector3(1.0f, 0.0f, 1.0f),                      Vector3(0.0f, 1.0f, 0.0f),                      Vector2(1.0f, 0.0f) },      // 17
            { Vector3( 1.5f,  1.0f, -1.5f),                 Vector3(1.0f, 0.0f, 1.0f),                      Vector3(0.0f, 1.0f, 0.0f),                      Vector2(1.0f, 1.0f) },      // 18
            { Vector3(-1.5f,  1.0f, -1.5f),                 Vector3(1.0f, 0.0f, 1.0f),                      Vector3(0.0f, 1.0f, 0.0f),                      Vector2(0.0f, 1.0f) },      // 19

            // Faccia Sotto (BASE)
            { Vector3(-1.5f, -1.0f,  1.5f),                 Vector3(0.0f, 1.0f, 1.0f),                      Vector3(0.0f, -1.0f, 0.0f),                     Vector2(0.0f, 0.0f) },      // 20
            { Vector3( 1.5f, -1.0f,  1.5f),                 Vector3(0.0f, 1.0f, 1.0f),                      Vector3(0.0f, -1.0f, 0.0f),                     Vector2(1.0f, 0.0f) },      // 21
            { Vector3( 1.5f, -1.0f, -1.5f),                 Vector3(0.0f, 1.0f, 1.0f),                      Vector3(0.0f, -1.0f, 0.0f),                     Vector2(1.0f, 1.0f) },      // 22
            { Vector3(-1.5f, -1.0f, -1.5f),                 Vector3(0.0f, 1.0f, 1.0f),                      Vector3(0.0f, -1.0f, 0.0f),                     Vector2(0.0f, 1.0f) }        // 23


    };


    std :: vector<unsigned int> indici = {
        0, 1, 2,
        0, 3, 2,
        4, 6, 5,
        4, 7, 6,
        8, 9, 10,
        8, 11, 10,
        12, 13, 14,
        12, 15, 14,
        16, 17, 18,
        16, 19, 18,
        20, 21, 22, 
        20, 23, 22
    };*/

    //Texture testTex("Modello3D/diffuse.png");
    Model Modello3D("big-room/Room-A.obj");
    Model IronMan("iron_man/ironMan.obj");
    

    GLfloat VerticiLuci[] =                         
    {       
        -0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, -0.1f,
        0.1f,  0.1f, -0.1f,
        -0.1f,  0.1f, -0.1f,
        -0.1f, -0.1f,  0.1f,
        0.1f, -0.1f,  0.1f,
        0.1f,  0.1f,  0.1f,
        -0.1f,  0.1f,  0.1f
 
    };

    GLuint IndiciLuci[] = 
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        0, 1, 5,
        0, 5, 4,
        1, 5, 6,
        1, 6, 2, 
        3, 2, 6,
        3, 6, 7,
        4, 5, 6,
        4, 6, 7,

    };

        //Crea il Mesh del cubo grande. TUTTO il setup (VAO, VBO, Attrib)
        //è ora gestito dal costruttore della classe Mesh.
        
       // Mesh cubo(vertici, indici);

        // --- Setup (lascia EBO bound al VAO, opzionale togliere Unbind) ---
        /*VAO vao;
        vao.Bind();

        VBO vbo(vertici, sizeof(vertici));
        EBO ebo(indici, sizeof(indici));*/

        // ===== CUBO LUCE =====
        VAO lightVAO;
        lightVAO.Bind();

        VBO lightVBO(VerticiLuci, sizeof(VerticiLuci));
        EBO lightEBO(IndiciLuci, sizeof(IndiciLuci));

        // solo posizione
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        lightVAO.Unbind();

    //Texture textureMuro("texture/muro.png");

    // Collega la texture al sampler tex0
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex0"), 0);

    const float bigRoomScale = 0.008f; // scala per portare la stanza a dimensioni gestibili
    Vector3 modelOffset = Vector3(0.0f, 0.0f, 0.0f);          // porta la stanza al centro del sistema
    Vector3 lightPos(modelOffset.x, modelOffset.y  + 3.0f, modelOffset.z + 0.6);       //luce direttamente sopra al modello

    //SPOT LIGHT DALL'ALTO 
    glUseProgram(shaderProgram);
    glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.position"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.direction"), 0.0f, -1.0f, 0.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.cutOff"), std::cos(20.5f * M_PI / 180.0f));
    glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.outerCutOff"), std::cos(18.5f * M_PI / 180.0f));
    glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.ambient"), 0.1f, 0.1f, 0.1f);
    glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.linear"), 0.09f);
    glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.quadratic"), 0.032f);

    // Posizione iniziale camera: dentro la stanza guardando il centro
    Vector3 roomCenter = modelOffset;
    Vector3 eyeStart = roomCenter.sommaVett(Vector3(0.0f, 0.0f, 0.0f)); // più in alto lungo Y e leggermente davanti
    float yawStart = std::atan2(roomCenter.x - eyeStart.x, roomCenter.z - eyeStart.z);
    camera.SetPositionAndYaw(eyeStart, yawStart);


   
        // Loop principale
        while (!glfwWindowShouldClose(window)) {
        processInput(window);

      
        //colore finestra
        glClearColor(0.3f, 0.07f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

        glUseProgram(shaderProgram);
      

    // Oggetto fermo
    Matrix4 scaleModel = Matrix4::scale(bigRoomScale);
    Matrix4 translateModel = Matrix4::traslate(modelOffset);
    Matrix4 Model = translateModel.prod_mat_mat(scaleModel);     // scalatura + traslazione per riportare il modello al centro

    // Posizione camera in orbita
    Matrix4 View = camera.GetViewMatrix();
    Vector3 eye = camera.GetPosition();
   

    // === DISEGNA CUBO GRANDE (OGGETTO) ===
    glUseProgram(shaderProgram);

    // invio matrici
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "Model"), 1, GL_TRUE, Model.data());
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "View"), 1, GL_TRUE, View.data());
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "Projection"), 1, GL_TRUE, Projection.data());      //Projection.data() dice a OpenGL dove inizia la mia matrice in memoria (a)

    // invio luce + camera
    glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"),  lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "camPos"),     eye.x, eye.y, eye.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "ambientColor"), 1.0f, 1.0f, 1.0f); // luce ambiente bianca

    /*
    effetto torcia con spotlight
    glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.position"), eye.x, eye.y, eye.z);
    Vector3 dir = camera.GetFront();
    glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.direction"), dir.x, dir.y, dir.z);
    */



    // texture
   //textureMuro.Bind(0);

    //cubo.Draw();
    Modello3D.Draw();

    Matrix4 ironScale = Matrix4 :: scale(0.0002f);
    Matrix4 ironTranslate = Matrix4 :: traslate(Vector3(3.0f, 0.0f, -0.7f));        //posizione dentro la stanza
    Matrix4 ironModel = ironTranslate.prod_mat_mat(ironScale);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "Model"), 1, GL_TRUE, ironModel.data());
    IronMan.Draw();
   


    glUseProgram(LightProgram);

    // 1) colore bianco per la luce
    GLint lightColorLoc = glGetUniformLocation(LightProgram, "lightColor");
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);  // bianco puro

    // 2) MVP per il cubo luce (posizionato in lightPos)
    Matrix4 lightModel = Matrix4::Identity();
    lightModel = Matrix4::traslate(lightPos);       //traslazione cubo piccolo 
    Matrix4 lightMVP = (Projection.prod_mat_mat(View)).prod_mat_mat(lightModel);


    GLint mvpLocL = glGetUniformLocation(LightProgram, "MVP");
    glUniformMatrix4fv(mvpLocL, 1, GL_TRUE, lightMVP.data());

    // 3) disegno cubo luce
    //lightVAO.Bind();
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

    //cubo.Delete();
    Modello3D.Delete();
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
