#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY)
{
    _position = position;
    _worldUp = up;
    _yaw = yaw;
    _pitch = pitch;
    UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY)
{
    _position = glm::vec3(posX, posY, posZ);
    _worldUp = glm::vec3(upX, upY, upZ);
    _yaw = yaw;
    _pitch = pitch;
    UpdateCameraVectors();
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = _movementSpeed * deltaTime;
    if (direction == CameraMovement::FORWARD)
        _position += _front * velocity;
    if (direction == CameraMovement::BACKWARD)
        _position -= _front * velocity;
    if (direction == CameraMovement::LEFT)
        _position -= _right * velocity;
    if (direction == CameraMovement::RIGHT)
        _position += _right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw += xoffset;
    _pitch += yoffset;

    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}