#include <TXEngine/Event/MouseMoveEvent.hpp>

namespace tx
{

MouseMoveEvent::MouseMoveEvent(float x, float y)
    : EventBase(EventType::MouseMoved)
    , m_x(x)
    , m_y(y)
{
}

Vector2f MouseMoveEvent::getPosition()
{
    return {m_x, m_y};
}

}// namespace tx