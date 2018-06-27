#include "audio.hpp"

using namespace flex;

Audio::Audio(const std::string &path) {
  m_wav.load(path.c_str());
  flex::log(L_DEBUG, L_AUDIO, "Loaded audio file: '%s'", path.c_str());
}

Audio::~Audio() {}

AudioSystem::AudioSystem() {
  m_soloud.init(SoLoud::Soloud::CLIP_ROUNDOFF, SoLoud::Soloud::BACKENDS::SDL2,
                SoLoud::Soloud::AUTO, 256);
}

AudioSystem::~AudioSystem() { m_soloud.deinit(); }

AudioHandle AudioSystem::play(Audio &audio, f32 volume, f32 pan, i32 paused,
                              i32 bus) {
  return m_soloud.play(audio.m_wav, volume, pan, paused, bus);
}

void AudioSystem::stop(AudioHandle &h) { m_soloud.stop(h); }

void AudioSystem::stop_all() { m_soloud.stopAll(); }
