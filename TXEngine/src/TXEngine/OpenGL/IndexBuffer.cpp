#include <glad/glad.h>

#include <TXEngine/OpenGL/GLUtil.hpp>
#include <TXEngine/OpenGL/IndexBuffer.hpp>

namespace tx
{

IndexBuffer::IndexBuffer()
{
    IndexBuffer::generateBuffer();
}

void IndexBuffer::bind()
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer));
}

void IndexBuffer::generateBuffer()
{
    glCall(glGenBuffers(1, &m_buffer));
}

void IndexBuffer::attachData(int* indices, int length)
{
    const static auto uint_bytes = sizeof(unsigned int);
    bind();
    m_count = length;
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * uint_bytes, indices, GL_STATIC_DRAW));
    unbind();
}

int IndexBuffer::getCount() const
{
    return m_count;
}

void IndexBuffer::unbind()
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

}// namespace tx