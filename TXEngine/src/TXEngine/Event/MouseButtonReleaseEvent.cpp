#include <TXEngine/Event/MouseButtonReleaseEvent.hpp>

namespace tx
{

MouseButtonReleaseEvent::MouseButtonReleaseEvent(short button)
    : MouseButtonReleaseEvent(ofMouseButton(button))
{
}

MouseButtonReleaseEvent::MouseButtonReleaseEvent(MouseButton button)
    : EventBase(EventType::MouseButtonReleased)
    , m_button(button)
{
}

MouseButton MouseButtonReleaseEvent::getButton()
{
    return m_button;
}

}// namespace tx