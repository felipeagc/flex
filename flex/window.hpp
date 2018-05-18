#pragma once

#include <SDL2/SDL.h>
#include <flex/config.hpp>
#include <flex/gl/util.hpp>
#include <flex/keyboard/keyboard.hpp>
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

  void on_key_up(std::function<void(keyboard::Key key, bool repeat)> callback) {
    this->m_on_key_up = callback;
  };

  void
  on_key_down(std::function<void(keyboard::Key key, bool repeat)> callback) {
    this->m_on_key_down = callback;
  };

private:
  SDL_Window *m_window;
  bool m_should_quit = false;

  std::function<void()> m_on_quit = []() {};
  std::function<void(float)> m_on_update = [](float delta) {};
  std::function<void(int, int)> m_on_resized = [](int w, int h) {};
  std::function<void(keyboard::Key key, bool repeat)> m_on_key_up =
      [](keyboard::Key key, bool repeat) {};
  std::function<void(keyboard::Key key, bool repeat)> m_on_key_down =
      [](keyboard::Key key, bool repeat) {};

  float m_last_time = 0.0;
};
} // namespace flex
