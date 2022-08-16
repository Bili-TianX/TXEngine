#include <TXEngine/Event/EventBase.hpp>

namespace tx
{

EventBase::EventBase(EventType type)
    : m_type(type)
{
}

EventType EventBase::getType() const
{
    return m_type;
}

}// namespace tx
