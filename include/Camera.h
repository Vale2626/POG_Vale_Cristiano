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
        Camera(float initialRadius = 2.0, float initialYaw = 0.0f, float initialY = 0.0f);
        
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

        private:

            float camRadius;
            float camYaw;
            float camY;

            // ---- Posizione Calcolata ----
            Vector3 cam_Position;       //posizione eye calcolata
            Vector3 cam_target;         //punto che la camera guarda (fisso a 0,0,0)
            Vector3 cam_up;             //vettore "up" fisso a 0,1,0


            /*
            camRadius = distanza dall’oggetto (↑ ↓)
            camYaw = angolo attorno all’oggetto (← →)
            camY = altezza camera(W/S)
            */

            // ---- Impostazioni di Movimento ----
            float cam_Orbit_Speed;
            float cam_Zoom_Speed;
            float cam_Pan_Speed;        //velocità di movimento verticale della camera
            float cam_Min_Radius;

            void updateCameraVectors();     //funzione privata per ricalcolare la posizione della camera

};

#endif