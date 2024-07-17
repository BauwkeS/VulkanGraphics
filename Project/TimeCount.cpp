#include "TimeCount.h"

#include <algorithm>
#include <chrono>

void TimeCount::Update()
{
    static auto prevTime{std::chrono::high_resolution_clock::now() };
    auto now = std::chrono::high_resolution_clock::now();
    s_Delta = std::min(s_MaxDelta, std::chrono::duration<float>(now - prevTime).count());

    prevTime = now;
}
