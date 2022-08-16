#include <stdexcept>

#include <stb_image.h>
#include <glad/glad.h>

#include <TXEngine/Graphics/Texture.hpp>
#include <TXEngine/OpenGL/GLUtil.hpp>

namespace tx
{

Texture::Texture()
{
    Texture::generateBuffer();
}

void Texture::loadFromFile(const std::string& filename)
{
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    auto data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if (data != nullptr) {
        loadFromMemory(data, width, height);
        stbi_image_free(data);
    }
    else {
        throw new std::runtime_error("Unable to load texture");
    }
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_buffer);
}

void Texture::generateBuffer()
{
    glGenTextures(1, &m_buffer);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadFromMemory(const void* data, int width, int height)
{
    bind();

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    glCall(glGenerateMipmap(GL_TEXTURE_2D));

    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::loadCharTexture(const void* data, int width, int height)
{
    bind();
    glCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data));
    glCall(glGenerateMipmap(GL_TEXTURE_2D));

    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

}// namespace tx