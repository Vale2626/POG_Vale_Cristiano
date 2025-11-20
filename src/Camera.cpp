#include "Camera.h"

Camera::Camera(float initialDistance, float initialYaw, float initialY)

{
    //valori di stato inizialii
    camYaw = initialYaw;
    camY = initialY;

    //costanti
    cam_Position = Vector3(0.0f, camY, initialDistance);
    cam_front = Vector3(0.0f, 0.0f, -1.0f);
    cam_target = cam_Position.sommaVett(cam_front);
    cam_up = Vector3(0.0f, 1.0f, 0.0f);

    //impostazioni di velocità, possono essere cambiate qui:
    cam_Orbit_Speed = 0.02f;
    cam_Move_Speed = 0.05f;

    //calcolo della direzione iniziale
    updateCameraVectors();

}
    // Funzione che gestisce l'input
void Camera::ProcessInput(GLFWwindow* window)
{
    // orbit orizzontale (rotazione yaw)
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camYaw += cam_Orbit_Speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camYaw -= cam_Orbit_Speed;

    // direzione aggiornata per i movimenti
    updateCameraVectors();

    Vector3 right = cam_front.ProdVett(cam_up).normalized();
    float move = cam_Move_Speed;

    // avanti / indietro (W/S oppure frecce su/giù)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        cam_Position = cam_Position.sommaVett(Vector3(cam_front.x * move, 0.0f, cam_front.z * move));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        cam_Position = cam_Position.diffVett(Vector3(cam_front.x * move, 0.0f, cam_front.z * move));
    }

    // destra / sinistra (A/D)
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cam_Position = cam_Position.sommaVett(Vector3(right.x * move, 0.0f, right.z * move));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cam_Position = cam_Position.diffVett(Vector3(right.x * move, 0.0f, right.z * move));
    }

    // mantieni la camera sul piano Y costante
    cam_Position.y = camY;

    // aggiorna la direzione dopo aver spostato la camera
    updateCameraVectors();
}

// Calcola la posizione 'eye' in base a raggio, yaw e altezza
void Camera::updateCameraVectors()
{
    Vector3 front(std::sinf(camYaw), 0.0f, std::cosf(camYaw));
    cam_front = front.normalized();
    cam_target = cam_Position.sommaVett(cam_front);
}

// Restituisce la matrice View
Matrix4 Camera::GetViewMatrix()
{
    // Usa la funzione LookAt che hai già creato!
    return Matrix4::LookAt(cam_Position, cam_target, cam_up);
}

// Restituisce la posizione
Vector3 Camera::GetPosition()
{
    return cam_Position;
}

Vector3 Camera::GetFront()
{
    return cam_front;
}
