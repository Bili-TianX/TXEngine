#include <TXEngine/Event/MouseButtonPressEvent.hpp>

namespace tx
{

MouseButtonPressEvent::MouseButtonPressEvent(short button)
    : MouseButtonPressEvent(ofMouseButton(button))
{

}

MouseButtonPressEvent::MouseButtonPressEvent(MouseButton button)
    : EventBase(EventType::MouseButtonPressed)
    , m_button(button)
{
}

MouseButton MouseButtonPressEvent::getButton()
{
    return m_button;
}

}// namespace tx