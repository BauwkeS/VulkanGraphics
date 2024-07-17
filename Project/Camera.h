//#pragma once
//#include "glm/glm.hpp"
//#include <glm/exponential.hpp>
//
//class Camera
//{
//public:
//    Camera(const glm::vec3& origin, float fov, float aspectRatio);
//
//    void Update();
//
//    [[nodiscard]] inline glm::mat4 View() const { return m_ViewMatrix; }
//
//    [[nodiscard]] inline glm::mat4 Proj() const { return m_ProjMatrix; }
//
//    void aspectRatio(float newAspect);
//    void SetYaw(float newYaw);
//    void SetPitch(float newPitch);
//
//private:
//
//    // NOTE: framerate-independent lerp from
//	// https://mastodon.social/@acegikmo/111931613710775864
//    //template<typename Type>
//    //Type lerpCamera(const Type& a, const Type& b, float deltaTime, float duration)
//    //{
//    //    // half life (2)
//    //    const float h{ -duration / glm::log2(1 / 1000.f) };
//
//    //    return b + (a - b) * glm::exp2(-deltaTime / h);
//    //}
//
//    //----
//
//    float m_Fov{ 90 };
//
//    glm::vec3 m_Origin{};
//    glm::vec3 m_OriginTarget{};
//
//    glm::vec3 m_Forward{ 0, 0, 1 };
//    glm::vec3 m_Up{ 0, 1, 0 };
//    glm::vec3 m_Right{ 1, 0, 0 };
//
//    float m_TotalPitch{};
//    float m_TotalPitchTarget{};
//
//    float m_TotalYaw{};
//    float m_TotalYawTarget{};
//
//    glm::mat4 m_ViewMatrix{ glm::mat4(1) };
//    glm::mat4 m_ProjMatrix{ glm::mat4(1) };
//
//    float m_AspectRatio{};
//    float m_zNear{ .01f };
//    float m_zFar{ 200.f };
//
//    void UpdateViewMatrix();
//    void UpdateProjMatrix();
//    void UpdateMatrices();
//};
