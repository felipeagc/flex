#pragma once

#include <SDL2/SDL.h>
#include <stack>

namespace flex {
class EventHandler;

class Window {
private:
  SDL_Window *m_window;
  SDL_GLContext m_context;
  bool m_should_quit = false;

  float m_last_time = 0.0;

  void update(EventHandler &event_handler);

public:
  Window(const char* title, unsigned int width, unsigned int height);
  ~Window();

  void run(EventHandler &event_handler);
  bool should_quit() const;

  unsigned int get_width() const;
  unsigned int get_height() const;

  void set_relative_mouse(bool relative);
  bool get_relative_mouse();

  void get_relative_mouse_pos(int *x, int *y);

  bool is_key_pressed(unsigned int scancode);
};
} // namespace flex
