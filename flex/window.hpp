#pragma once

#include <SDL2/SDL.h>
#include "types.hpp"

namespace flex {
class EventHandler;

class Window {
private:
  SDL_Window *m_window;
  SDL_GLContext m_context;
  bool m_should_quit = false;

  f32 m_last_time = 0.0;

  void update(EventHandler &event_handler);

public:
  Window(const char* title, u32 width, u32 height);
  ~Window();

  void run(EventHandler &event_handler);
  bool should_quit() const;

  u32 get_width() const;
  u32 get_height() const;

  void set_relative_mouse(bool relative);
  bool get_relative_mouse();

  void get_relative_mouse_pos(i32 *x, i32 *y);

  bool is_key_pressed(u32 scancode);
};
} // namespace flex
