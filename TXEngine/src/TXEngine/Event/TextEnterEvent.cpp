#include <TXEngine/Event/TextEnterEvent.hpp>

namespace tx
{

TextEnterEvent::TextEnterEvent(wchar_t unicode)
    : EventBase(EventType::TextEntered)
    , m_unicode(unicode)
{
}

wchar_t TextEnterEvent::getUnicode()
{
    return m_unicode;
}

}// namespace tx