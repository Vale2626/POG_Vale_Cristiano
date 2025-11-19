#include "Camera.h"

Camera::Camera(float initialRadius, float initialYaw, float initialY)

{
    //valori di stato inizialii
    camRadius = initialRadius;
    camYaw = initialYaw;
    camY = initialY;

    //costanti
    cam_target = Vector3(0.0f, 0.0f, 0.0f);
    cam_up = Vector3(0.0f, 1.0f, 0.0f);

    //impostazioni di velocità, possono essere cambiate qui:
    cam_Orbit_Speed = 0.02f;
    cam_Zoom_Speed = 0.05f;
    cam_Pan_Speed = 0.03f;
    cam_Min_Radius = 0.5f;

    //calcolo della posizione iniziale
    updateCameraVectors();

}
    // Funzione che gestisce l'input
void Camera::ProcessInput(GLFWwindow* window)
{
    // orbit orizzontale
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camYaw += cam_Orbit_Speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camYaw -= cam_Orbit_Speed;

    // zoom (distanza), con limite minimo
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camRadius = std::max(cam_Min_Radius, camRadius - cam_Zoom_Speed);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camRadius += cam_Zoom_Speed;

    // alza/abbassa camera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camY += cam_Pan_Speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camY -= cam_Pan_Speed;

    // Ricalcola la posizione dopo ogni input
    updateCameraVectors();
}

// Calcola la posizione 'eye' in base a raggio, yaw e altezza
void Camera::updateCameraVectors()
{
    float camX = std::sinf(camYaw) * camRadius;
    float camZpos = std::cosf(camYaw) * camRadius;

    // Aggiorna il membro m_position
    cam_Position = Vector3(camX, camY, camZpos);
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

