#pragma once

#include "logging.hpp"
#include "types.hpp"
#include <soloud.h>
#include <soloud_wav.h>
#include <string>

namespace flex {
typedef SoLoud::handle AudioHandle;

class AudioSystem;

class Audio {
  friend class AudioSystem;

private:
  SoLoud::Wav m_wav;

public:
  Audio(const std::string &path);
  ~Audio();
};

class AudioSystem {
private:
  SoLoud::Soloud m_soloud;

public:
  AudioSystem();
  ~AudioSystem();

  AudioHandle play(Audio &audio, f32 volume = 1.0f, f32 pan = 0.0f,
                   i32 paused = 0, i32 bus = 0);

  void stop(AudioHandle &h);
  void stop_audio(Audio &audio);
  void stop_all();
};

} // namespace flex
