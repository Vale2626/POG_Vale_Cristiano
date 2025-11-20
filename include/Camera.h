#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include "Matrix4.h"
#include"Vector3.h"
#include<cmath>
#include<algorithm> //per std::max


class Camera
{
    public:
        Camera(float initialDistance = 2.0f, float initialYaw = 0.0f, float initialY = 0.0f);
        
        /*
            initialRadius = distanza INIZIALE dall’oggetto (↑ ↓)
            initialYaw = È l'angolo di rotazione orizzontale INIZIALE. (← →)
            initialY = È l'altezza INIZIALE della telecamera.
        */

        // Funzione che gestisce l'input da tastiera
        void ProcessInput(GLFWwindow * window);

        // Restituisce la matrice View (LookAt) calcolata
        Matrix4 GetViewMatrix();

        // Restituisce la posizione attuale della camera (l'"occhio")
        Vector3 GetPosition();

        Vector3 GetFront();

        // Imposta manualmente posizione e yaw iniziale (per spawn dentro una stanza)
        void SetPositionAndYaw(const Vector3& position, float yaw);

        private:
            float camYaw;
            float camY;
            float cam_Move_Speed;

            // ---- Posizione Calcolata ----
            Vector3 cam_Position;       //posizione eye calcolata
            Vector3 cam_front;
            Vector3 cam_target;         //punto che la camera guarda
            Vector3 cam_up;             //vettore "up" fisso a 0,1,0


            // ---- Impostazioni di Movimento ----
            float cam_Orbit_Speed;

            void updateCameraVectors();     //funzione privata per ricalcolare la posizione della camera

};

#endif
