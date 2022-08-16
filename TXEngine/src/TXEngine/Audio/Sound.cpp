#include <vector>

#include <AL/alut.h>

#include <TXEngine/Audio/AlUtil.hpp>
#include <TXEngine/Audio/Sound.hpp>

namespace tx
{

Sound::Sound()
{
    Sound::generateBuffer();
}

void Sound::loadFromFile(const std::string& filename)
{
    ALenum format;
    ALsizei size;
    ALfloat frequency;

    alCall(m_data = alutLoadMemoryFromFile(filename.c_str(), &format, &size, &frequency));
    if (m_data == nullptr) {
        throw std::runtime_error("Unable to load sound file");
    }
    alCall(alBufferData(m_buffer, format, m_data, size, frequency));

    alCall(alGenSources(1, &m_source));
    alCall(alSourcef(m_source, AL_GAIN, 1));
    alCall(alSourcef(m_source, AL_PITCH, 1));
    alCall(alSource3f(m_source, AL_POSITION, 0, 0, 0));
    alCall(alSourcei(m_source, AL_BUFFER, m_buffer));
}

void Sound::bind()
{
}

void Sound::generateBuffer()
{
    alCall(alGenBuffers(1, &m_buffer))
}

void Sound::play()
{
    if (m_data == nullptr) {
        throw std::runtime_error("sound data is null!");
    }

    alCall(alSourcePlay(m_source));
}

Sound::~Sound()
{
    alCall(alDeleteSources(1, &m_source));
    alCall(alDeleteBuffers(1, &m_buffer));
}

void Sound::unbind()
{
}

}// namespace tx