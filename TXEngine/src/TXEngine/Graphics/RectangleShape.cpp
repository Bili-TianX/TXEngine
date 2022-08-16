#include <glad/glad.h>

#include <TXEngine/Graphics/RectangleShape.hpp>
#include <TXEngine/OpenGL/GLUtil.hpp>

namespace tx
{

RectangleShape::RectangleShape(float x, float y, float width, float height, Color color, Texture* texture)
    : Shape(x, y, color, texture)
    , m_width(width)
    , m_height(height)
{
    RectangleShape::updateVertices();
}

void RectangleShape::updateVertices()
{
    std::vector<Vertex> vertices;
    if (m_flipH) {
        if (m_flipV) {
            vertices = {{m_x, m_y, m_color, 1, 0},
                        {m_x, m_y + m_height, m_color, 1, 1},
                        {m_x + m_width, m_y + m_height, m_color, 0, 1},
                        {m_x + m_width, m_y, m_color, 0, 0}};
        }
        else {
            vertices = {{m_x, m_y, m_color, 1, 1},
                        {m_x, m_y + m_height, m_color, 1, 0},
                        {m_x + m_width, m_y + m_height, m_color, 0, 0},
                        {m_x + m_width, m_y, m_color, 0, 1}};
        }
    }
    else {
        if (m_flipV) {
            vertices = {{m_x, m_y, m_color, 0, 1},
                        {m_x, m_y + m_height, m_color, 0, 0},
                        {m_x + m_width, m_y + m_height, m_color, 1, 0},
                        {m_x + m_width, m_y, m_color, 1, 1}};
        }
        else {
            vertices = {{m_x, m_y, m_color, 0, 0},
                        {m_x, m_y + m_height, m_color, 0, 1},
                        {m_x + m_width, m_y + m_height, m_color, 1, 1},
                        {m_x + m_width, m_y, m_color, 1, 0}};
        }
    }

    if (m_texture == nullptr) {
        for (const auto& item : vertices) {
            item.tex_x = -1;
            item.tex_y = -1;
        }
    }

    int indices[] = {0, 1, 2, 0, 3, 2};

    m_vertexBuffer->attachData(vertices.data(), 4);
    m_indexBuffer->attachData(indices, 6);
}

void RectangleShape::draw(Shader* shader)
{
    if (m_texture != nullptr) {
        m_texture->bind();
    }

    m_vertexBuffer->setupDraw();
    m_indexBuffer->bind();

    glCall(glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr));

    if (m_texture != nullptr) {
        m_texture->unbind();
    }
    m_indexBuffer->unbind();
    m_vertexBuffer->unbind();
}

void RectangleShape::setSize(float width, float height)
{
    this->m_width  = width;
    this->m_height = height;

    updateVertices();
}

void RectangleShape::setTexture(Texture* texture)
{
    TextureTarget::setTexture(texture);

    updateVertices();
}

void RectangleShape::setFlip(bool flipV, bool flipH)
{
    m_flipV = flipV;
    m_flipH = flipH;

    updateVertices();
}

}// namespace tx
