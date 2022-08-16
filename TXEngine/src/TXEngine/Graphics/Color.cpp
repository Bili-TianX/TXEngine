#include <TXEngine/Graphics/Color.hpp>

namespace tx
{

const Color Color::Black = Color(0, 0, 0);
const Color Color::White = Color();

Color::Color(Color::Uint8 r, Color::Uint8 g, Color::Uint8 b, Color::Uint8 a)
    : r(r)
    , g(g)
    , b(b)
    , a(a)
{
}

Vector4f Color::normalize() const
{
    return {(float) r / 255, (float) g / 255, (float) b / 255, (float) a / 255};
}

}// namespace tx
