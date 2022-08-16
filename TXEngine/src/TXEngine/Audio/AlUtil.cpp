#include <iostream>

#include <AL/al.h>

#include <TXEngine/Audio/AlUtil.hpp>

namespace tx
{

bool AlLogCall(const char* function, const char* file, int line)
{
    ALenum error;
    if ((error = alGetError()) != AL_NO_ERROR) {
        std::cout << "[OpenAL Error] (" << error << "): " << function << " (at " << file << ":" << line << ")"
                  << std::endl;
        return false;
    }
    return true;
}

}// namespace tx