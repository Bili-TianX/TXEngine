#include <glad/glad.h>

#include <TXEngine/OpenGL/GLUtil.hpp>
#include <TXEngine/OpenGL/VertexArrayBuffer.hpp>

namespace tx
{

VertexArrayBuffer::VertexArrayBuffer()
{
    VertexArrayBuffer::generateBuffer();
}

void VertexArrayBuffer::bind()
{
    glCall(glBindVertexArray(m_buffer));
}

void VertexArrayBuffer::generateBuffer()
{
    glCall(glGenVertexArrays(1, &m_buffer));
}

void VertexArrayBuffer::unbind()
{
    glCall(glBindVertexArray(0));
}

}// namespace tx