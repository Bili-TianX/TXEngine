#include <math.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <TXEngine/OpenGL/Vertex.hpp>
#include <TXEngine/Graphics/CircleShape.hpp>

namespace tx
{

CircleShape::CircleShape(float x, float y, float radius)
    : Shape(x, y)
    , m_radius(radius)
{
    CircleShape::updateVertices();
}

void CircleShape::draw(Shader* shader)
{
    m_vertexBuffer->setupDraw();
    m_indexBuffer->bind();
    if (m_texture != nullptr) {
        m_texture->bind();
    }

    glDrawElements(GL_TRIANGLE_FAN, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

    m_texture->unbind();
    m_indexBuffer->unbind();
    m_vertexBuffer->finishDraw();
}

void CircleShape::updateVertices()
{
    const static double M_PI = 3.14159265358979323846;
    const static int POINT_COUNT    = 48;
    const static int VERTICES_COUNT = POINT_COUNT + 1;

    Vertex vertices[VERTICES_COUNT];

    for (int i = 0; i < POINT_COUNT; i++) {
        double angle = (i * 1.0 / POINT_COUNT) * 2 * M_PI;

        if (m_texture != nullptr) {
            double c = cos(angle);
            double s = sin(angle);
            double x = c * m_radius;
            double y = s * m_radius;

            vertices[i] = {static_cast<float>(m_x + x), static_cast<float>(m_y + y), m_color,
                           static_cast<float>(c / 2 + 0.5), static_cast<float>(-s / 2 + 0.5)};
        }
        else {
            double x    = cos(angle) * m_radius;
            double y    = sin(angle) * m_radius;
            vertices[i] = {static_cast<float>(m_x + x), static_cast<float>(m_y + y), m_color};
        }
    }
    if (m_texture != nullptr) {
        vertices[POINT_COUNT] = {m_x, m_y, m_color, 0.5, 0.5};
    }
    else {
        vertices[POINT_COUNT] = {m_x, m_y, m_color};
    }

    int indies[VERTICES_COUNT + 1]{};
    indies[0] = POINT_COUNT;
    for (int i = 1; i < VERTICES_COUNT; i++) {
        indies[i] = i - 1;
    }
    indies[VERTICES_COUNT] = 0;

    m_vertexBuffer->attachData(vertices, VERTICES_COUNT);
    m_indexBuffer->attachData(indies, VERTICES_COUNT + 1);
}

void CircleShape::setTexture(Texture* texture)
{
    TextureTarget::setTexture(texture);
    updateVertices();
}

void CircleShape::setRadius(float radius)
{
    m_radius = radius;
    updateVertices();
}

}// namespace tx
