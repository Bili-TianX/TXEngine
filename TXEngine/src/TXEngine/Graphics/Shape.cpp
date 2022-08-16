#include <TXEngine/Graphics/Shape.hpp>

namespace tx
{

Shape::Shape(float x, float y, Color color, Texture* texture)
    : m_x(x)
    , m_y(y)
    , m_color(color)
{
    m_vertexBuffer = new VertexBuffer();
    m_indexBuffer  = new IndexBuffer();
    m_texture = texture;
}

Shape::~Shape()
{
    delete m_vertexBuffer;
    delete m_indexBuffer;
}

void Shape::setPosition(float x, float y)
{
    this->m_x = x;
    this->m_y = y;

    updateVertices();
}

void Shape::setColor(const Color& color)
{
    Shape::m_color = color;
    updateVertices();
}

}// namespace tx