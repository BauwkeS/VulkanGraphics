
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Camera.h"

#include "TimeCount.h"
#include "InputSys.h"


Camera::Camera(const glm::vec3& origin, float fov, float aspectRatio) :
	m_Fov(fov),
	m_Origin(origin),
	m_OriginTarget(origin),
	m_AspectRatio(aspectRatio)
{
    UpdateMatrices();
}

void Camera::Update()
{
    const auto deltaTime{ TimeCount::Delta() };

    // Keyboard input
    {

        float speed{ 5.f * deltaTime };

        if (InputSys::KeyHeld(GLFW_KEY_LEFT_SHIFT))
        {
            speed *= 1.5f;
        }

        const float forwardInput = static_cast<float>(
            InputSys::KeyHeld(GLFW_KEY_W) - InputSys::KeyHeld(GLFW_KEY_S));
        m_OriginTarget += m_Forward * speed * forwardInput;

        const float rightInput = static_cast<float>(
            InputSys::KeyHeld(GLFW_KEY_A) - InputSys::KeyHeld(GLFW_KEY_D));
        m_OriginTarget += m_Right * speed * rightInput;

        const float UpInput = static_cast<float>(InputSys::KeyHeld(GLFW_KEY_E)
            - InputSys::KeyHeld(GLFW_KEY_Q));
        m_OriginTarget += m_Up * speed * UpInput;
    }

    // Mouse input
    {
        constexpr float sens{ .001f };
        auto&& mouseData{ InputSys::MouseData() };

        if (glm::length(mouseData) != 0
            && InputSys::ButtonHeld(GLFW_MOUSE_BUTTON_RIGHT))
        {
            m_TotalYawTarget -= mouseData.x * sens;
            m_TotalPitchTarget += mouseData.y * sens;

            m_TotalPitchTarget = glm::clamp(m_TotalPitchTarget,
                -.5f * glm::pi<float>(),
                .5f * glm::pi<float>());
        }
    }

    //Update to correct positions 
    m_Origin = lerpCamera(m_Origin, m_OriginTarget, deltaTime, .5f);
    m_TotalPitch = lerpCamera(m_TotalPitch, m_TotalPitchTarget, deltaTime, .5f);
    m_TotalYaw = lerpCamera(m_TotalYaw, m_TotalYawTarget, deltaTime, .5f);

    UpdateMatrices();
}

void Camera::aspectRatio(float newAspect)
{
    m_AspectRatio = newAspect;
    UpdateProjMatrix();
}

void Camera::SetYaw(float newYaw)
{
    m_TotalYaw = newYaw;
    m_TotalYawTarget = newYaw;
}

void Camera::SetPitch(float newPitch)
{
    m_TotalPitch = newPitch;
    m_TotalPitchTarget = newPitch;
}

void Camera::UpdateViewMatrix()
{
    glm::mat4 rot{ glm::yawPitchRoll(m_TotalYaw, m_TotalPitch, 0.f) };
    m_Right = rot[0];
    m_Up = rot[1];
    m_Forward = rot[2];

    m_ViewMatrix = glm::lookAt(m_Origin, m_Origin + m_Forward, m_Up);
}

void Camera::UpdateProjMatrix()
{
    m_ProjMatrix = glm::perspective(m_Fov, m_AspectRatio, m_zNear, m_zFar);
}

void Camera::UpdateMatrices()
{
    UpdateViewMatrix();
    UpdateProjMatrix();
}
