#include <TXEngine/Event/CloseEvent.hpp>

namespace tx
{

CloseEvent::CloseEvent()
    : EventBase(EventType::Closed)
{
}

}// namespace tx
