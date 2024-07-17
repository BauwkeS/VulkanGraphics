#include "InputSys.h"

void InputSys::Update()
{
    for (auto&& keyVal : s_Keys)
    {
        if (keyVal == 0)
        {
            continue;
        }

        keyVal++;
    }

    for (auto&& buttonVal : s_Button)
    {
        if (buttonVal == 0)
        {
            continue;
        }

        buttonVal++;
    }

    s_MouseDelta = {};

}

void InputSys::OnKeyDown(int key)
{
    s_Keys[key] = 1;
}

void InputSys::OnKeyUp(int key)
{
    s_Keys[key] = 0;
}

void InputSys::OnButtonDown(int button)
{
    s_Button[button] = 1;
}

void InputSys::OnButtonUp(int button)
{
    s_Button[button] = 0;
}

void InputSys::OnMouseMove(const glm::vec2& newPos)
{
    static glm::vec2 sLastMousePos{ newPos };
    static bool sFirstMouse{ true };

    if (sFirstMouse)
    {
        sLastMousePos = newPos;
        sFirstMouse = false;
        return;
    }

    s_MouseDelta += newPos - sLastMousePos;
    sLastMousePos = newPos;
}
