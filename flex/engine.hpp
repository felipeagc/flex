#pragma once

#include "audio.hpp"
#include "window.hpp"
#include "types.hpp"

namespace flex {
class Window;

class Engine {
private:
  Window m_window;
  AudioSystem m_audio;

public:
  Engine(const char* title, u32 width = 800, u32 height = 600);
  ~Engine();

  Window &get_window();
  AudioSystem &get_audio();
};
} // namespace flex
