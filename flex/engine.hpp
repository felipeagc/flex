#pragma once

#include "audio.hpp"
#include "graphics.hpp"
#include "window.hpp"
#include <memory>

namespace flex {
class Window;

class Engine {
private:
  Window m_window;
  AudioSystem m_audio;
  GraphicsSystem m_graphics;

public:
  Engine(const std::string &title, int width = 800, int height = 600);
  ~Engine();

  Window &get_window();
  AudioSystem &get_audio();
  GraphicsSystem &get_graphics();
};
} // namespace flex
