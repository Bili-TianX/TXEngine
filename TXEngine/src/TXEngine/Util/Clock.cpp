#include <GLFW/glfw3.h>

#include <TXEngine/Util/Clock.hpp>

namespace tx
{

Clock::Clock()
{
    m_start = glfwGetTime();
}

float Clock::restart()
{
    auto now    = glfwGetTime();
    auto result = now - m_start;
    m_start     = now;
    return result;
}

float Clock::getElapsedTime()
{
    return glfwGetTime() - m_start;
}

}// namespace tx