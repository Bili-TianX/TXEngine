#include <TXEngine/Event/KeyReleaseEvent.hpp>

namespace tx
{

KeyReleaseEvent::KeyReleaseEvent(short key)
    : KeyReleaseEvent(ofKey(key))
{
}


KeyReleaseEvent::KeyReleaseEvent(Key key)
    : EventBase(EventType::KeyReleased)
    , m_key(key)
{
}

Key KeyReleaseEvent::getKey()
{
    return m_key;
}

}// namespace tx