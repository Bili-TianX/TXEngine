#include <TXEngine/Event/ResizeEvent.hpp>

namespace tx
{

ResizeEvent::ResizeEvent(int width, int height)
    : EventBase(EventType::Resized)
    , m_width(width)
    , m_height(height)
{
}

int ResizeEvent::getWidth() const
{
    return m_width;
}

int ResizeEvent::getHeight() const
{
    return m_height;
}

}// namespace tx
