#pragma once

#include <SDL2/SDL.h>
#include <flex/config.hpp>
#include <flex/gl/util.hpp>
#include <functional>
#include <glad/glad.h>
#include <iostream>
#include <string>

namespace flex {
class Window {
public:
  Window(const std::string &name, int width, int height);
  ~Window();

  void run();

  int get_width() const;
  int get_height() const;

  void set_relative_mouse(bool relative);
  bool get_relative_mouse();

  void get_relative_mouse_pos(int *x, int *y);

  bool is_key_pressed(unsigned int scancode);

  void on_quit(std::function<void()> callback) { this->m_on_quit = callback; };

  void on_update(std::function<void(float delta)> callback) {
    this->m_on_update = callback;
  };

  void on_resized(std::function<void(int w, int h)> callback) {
    this->m_on_resized = callback;
  };

private:
  SDL_Window *m_window;
  bool m_should_quit = false;

  std::function<void()> m_on_quit = []() {};
  std::function<void(float)> m_on_update = [](float delta) {};
  std::function<void(int, int)> m_on_resized = [](int w, int h) {};

  float m_last_time = 0.0;
};
} // namespace flex
