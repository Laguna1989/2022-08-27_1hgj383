﻿#include "sound.hpp"
#include <stdexcept>

jt::Sound::Sound(std::string const& fileName)
    : m_buffer { fileName }
    , m_sound { m_buffer }
    , m_fileName { fileName }
{
}

void jt::Sound::update()
{
    m_sound.update();
    m_sound.setVolume(m_blend * m_volume);
}

bool jt::Sound::isPlaying() const { return m_sound.isPlaying(); }

void jt::Sound::play() { m_sound.play(); }
void jt::Sound::stop() { m_sound.stop(); }
void jt::Sound::pause() { m_sound.pause(); }

float jt::Sound::getVolume() const { return m_volume; }
void jt::Sound::setVolume(float newVolume) { m_volume = newVolume; }

void jt::Sound::setLoop(bool doLoop) { m_sound.setIsLooping(doLoop); }
bool jt::Sound::getLoop(void) { return m_sound.getIsLooping(); }

float jt::Sound::getDuration() const { return m_sound.getLengthInSeconds(); }

float jt::Sound::getPosition() const { return m_sound.getCurrentOffsetInSeconds(); }
void jt::Sound::setBlend(float blend)
{
    if (blend < 0.0f || blend > 1.0f) {
        throw std::invalid_argument { "Blend has to be between [0, 1]." };
    }
    m_blend = 1.0f - blend;
}
float jt::Sound::getBlend() const { return 1.0f - m_blend; }

void jt::Sound::setPitch(float pitch)
{
    if (pitch <= 0.0f) {
        throw std::invalid_argument { "Pitch has to be greater than 0." };
    }
    m_sound.setPitch(pitch);
}
float jt::Sound::getPitch() const { return m_sound.getPitch(); }

int jt::Sound::getSampleRate() const { return m_buffer.getSampleRate(); }
