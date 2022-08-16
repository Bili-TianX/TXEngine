#include <glad/glad.h>

#include <TXEngine/OpenGL/VertexBuffer.hpp>
#include <TXEngine/OpenGL/GLUtil.hpp>

namespace tx
{

VertexBuffer::VertexBuffer()
{
    VertexBuffer::generateBuffer();
    m_vertexArrayBuffer = new VertexArrayBuffer();
}

VertexBuffer::~VertexBuffer()
{
    delete m_vertexArrayBuffer;
}

void VertexBuffer::bind()
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_buffer));
}

void VertexBuffer::generateBuffer()
{
    glCall(glGenBuffers(1, &m_buffer));
}

void VertexBuffer::attachData(float* data, int length)
{
    const static auto float_bytes = sizeof(float);
    bind();
    m_vertexArrayBuffer->bind();

    glCall(glBufferData(GL_ARRAY_BUFFER, length * float_bytes, data, GL_STATIC_DRAW));

    // 坐标
    glCall(glVertexAttribPointer(0, 2, GL_FLOAT, false, float_bytes * 8, reinterpret_cast<const void*>(0)));
    glCall(glEnableVertexAttribArray(0));
    // 颜色 RGBA
    glCall(glVertexAttribPointer(1, 4, GL_FLOAT, false, float_bytes * 8,
                                 reinterpret_cast<const void*>(2 * float_bytes)));
    glCall(glEnableVertexAttribArray(1));
    // 纹理
    glCall(glVertexAttribPointer(2, 2, GL_FLOAT, false, float_bytes * 8,
                                 reinterpret_cast<const void*>(6 * float_bytes)));
    glCall(glEnableVertexAttribArray(2));
}

void VertexBuffer::attachData(Vertex vertices[], int length)
{
    auto data_length = length * 8;
    auto data        = new float[data_length];

    int index = 0;
    for (int i = 0; i < length; ++i) {
        const auto& vertex = vertices[i];
        auto [r, g, b, a]  = vertex.color.normalize();

        data[index++] = vertex.x;
        data[index++] = vertex.y;
        data[index++] = r;
        data[index++] = g;
        data[index++] = b;
        data[index++] = a;
        data[index++] = vertex.tex_x;
        data[index++] = vertex.tex_y;
    }

    attachData(data, data_length);
    delete[] data;
}

void VertexBuffer::setupDraw()
{
    m_vertexArrayBuffer->bind();
}

void VertexBuffer::unbind()
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::finishDraw()
{
    m_vertexArrayBuffer->unbind();
}

}// namespace tx