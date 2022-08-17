#include <TXEngine/Event/KeyPressEvent.hpp>

namespace tx
{

Key KeyPressEvent::getKey() const
{
    return m_key;
}

KeyPressEvent::KeyPressEvent(short key)
    : KeyPressEvent(ofKey(key))
{
}

KeyPressEvent::KeyPressEvent(Key key)
    : EventBase(EventType::KeyPressed)
    , m_key(key)
{
}

}// namespace tx