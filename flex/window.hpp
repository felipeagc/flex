#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <flex/config.hpp>

namespace flex {
class Window {
public:
  Window(const std::string &name, int width, int height);
  ~Window();

  void run();

  void on_quit(std::function<void()> callback) {
    this->m_on_quit = callback;
  };

  void on_update(std::function<void(float delta)> callback) {
    this->m_update = callback;
  };

private:
  SDL_Window *m_window;
  bool m_should_quit = false;

  std::function<void()> m_on_quit;
  std::function<void(float)> m_update;

  float m_last_time = 0.0;
};
} // namespace flex
