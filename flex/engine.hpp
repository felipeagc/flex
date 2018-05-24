#pragma once

#include "audio.hpp"
#include "window.hpp"
#include <memory>

namespace flex {
class Window;

class Engine {
private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<AudioSystem> m_audio;

public:
  Engine(const std::string &title, int width = 800, int height = 600);
  ~Engine();

  Window *get_window();
  AudioSystem *get_audio();
};
} // namespace flex
