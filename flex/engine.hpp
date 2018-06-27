#pragma once

#include "audio.hpp"
#include "window.hpp"

namespace flex {
class Window;

class Engine {
private:
  Window m_window;
  AudioSystem m_audio;

public:
  Engine(const char* title, int width = 800, int height = 600);
  ~Engine();

  Window &get_window();
  AudioSystem &get_audio();
};
} // namespace flex
