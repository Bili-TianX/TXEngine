#include <iostream>

#include <glad/glad.h>

#include <TXEngine/OpenGL/GLUtil.hpp>

namespace tx
{

bool GlLogCall(const char* function, const char* file, int line)
{
    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "[OpenGL Error] " << function << " (at " << file << ":" << line << ")" << std::endl;
        return false;
    }

    return true;
}

}// namespace tx