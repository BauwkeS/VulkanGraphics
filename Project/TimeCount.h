#pragma once
class TimeCount
{
public:
    static void Update();

    static inline float Delta() { return s_Delta; }

private:
    static inline float s_Delta{};

    static constexpr float s_MaxDelta{ 1.f / 30.f };
};
