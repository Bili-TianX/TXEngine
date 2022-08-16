#include <TXEngine/Event/KeyPressEvent.hpp>

namespace tx
{

static inline Key of(short key)
{
    return static_cast<Key>(key);
}

Key KeyPressEvent::getKey() const
{
    return m_key;
}

KeyPressEvent::KeyPressEvent(short key)
    : KeyPressEvent(of(key))
{
}

KeyPressEvent::KeyPressEvent(Key key)
    : EventBase(EventType::KeyPressed)
    , m_key(key)
{
}

}// namespace tx