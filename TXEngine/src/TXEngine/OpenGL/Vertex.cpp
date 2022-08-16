#include <TXEngine/OpenGL/Vertex.hpp>

namespace tx
{

Vertex::Vertex(float x, float y, Color color, float tex_x, float tex_y)
    : x(x)
    , y(y)
    , color(color)
    , tex_x(tex_x)
    , tex_y(tex_y)
{
}

}// namespace tx