#ifndef ICAMERA_H
#define ICAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
*	Abstraction for all the movements to prevent it from bein OS specific
*/
enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class ICamera
{
public:
    /**
    *   Called by the Window when keyboard input is detected
    */
    virtual void ProcessKeyboard(CameraMovement direction, float deltaTime) {};

    /**
    *   Called by the Window when mouse is move
    */
    virtual void ProcessMouseMovement(float xoffset, float yoffset) {};


    //Used by the Window to get the view matrix out of the camera
    virtual glm::mat4 GetViewMatrix() { return glm::mat4(1.0f); };
};
#endif