#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ICamera.h"

#include <vector>

//Default values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;

/**
*	Abstraction of a camera that allows to calculate the view matrix
*/
class Camera3D : public ICamera
{
private:
    //Angle (in degree) for the rotation along the y axis
    float _yaw;
    //Angle (in degree) for the rotation along the x axis
    float _pitch;

    //Configurable options
    float _movementSpeed;
    float _mouseSensitivity;

    //Vector for the position in the world
    glm::vec3 _position;
    //Vector pointing in front of the camera
    glm::vec3 _front;
    //Vector pointing the up of the camera
    glm::vec3 _up;
    //Vector pointing the up of the world
    glm::vec3 _worldUp;
    //Unit vector pointing the right of the camera
    glm::vec3 _right;
public:
    /**
    *	Creating all the camera vectors and initializing values (using vectors)
    *
    *	@param position Vector for the position in the world
    *	@param up Vector pointing the up of the world
    *   @param yaw Angle (in degree) for the rotation along the y axis
    *   @param pitch Angle (in degree) for the rotation along the x axis
    */
    Camera3D(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    /**
    *	Creating all the camera vectors and initializing values (using components)
    *
    *	@param posX X component for the vector of the position in the world
    *	@param posY Y component for the vector of the position in the world
    *	@param posZ Z component for the vector of the position in the world
    *	@param upX X component for the vector pointing the up of the world
    *	@param upY Y component for the vector pointing the up of the world
    *	@param upZ Z component for the vector pointing the up of the world
    *   @param yaw Angle (in degree) for the rotation along the y axis
    *   @param pitch Angle (in degree) for the rotation along the x axis
    */
    Camera3D(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    /**
    *   Moves the camera using its position vector based on delta time and speed
    */
    void ProcessKeyboard(CameraMovement direction, float deltaTime);

    /**
    *   Rotate the camera using its pitch and yaw based on mouse sensitivity and x/y offset
    */
    void ProcessMouseMovement(float xoffset, float yoffset);

    //Getters
    glm::mat4 GetViewMatrix() const { return glm::lookAt(_position, _position + _front, _up); };


private:
    /**
    *   Rotate the front vector and then recalculate the _up and _right vector
    */
    void UpdateCameraVectors();
};
#endif