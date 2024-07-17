#pragma once

#include <GLFW/glfw3.h>

#include <array>
#include <glm/glm.hpp>


class Input
{
    friend class VulkanBase;

public:
    static inline int GetKey(int key) { return s_Keys[key]; }

    static inline bool KeyDown(int key) { return GetKey(key) == 1; }

    static inline bool KeyHeld(int key) { return GetKey(key) >= 1; }

    static inline int GetButton(int button) { return s_Button[button]; }

    static inline bool ButtonDown(int button) { return GetButton(button) == 1; }

    static inline bool ButtonHeld(int button) { return GetButton(button) >= 1; }

    static inline glm::vec2 MouseData() { return s_MouseDelta; }

private:
    static inline std::array<int, GLFW_KEY_LAST> s_Keys{};
    static inline std::array<int, GLFW_MOUSE_BUTTON_LAST> s_Button{};
    static inline glm::vec2 s_MouseDelta{};

    static void Update();

    static void OnKeyDown(int key);
    static void OnKeyUp(int key);

    static void OnButtonDown(int button);
    static void OnButtonUp(int button);
    static void OnMouseMove(const glm::vec2& newPos);
};
