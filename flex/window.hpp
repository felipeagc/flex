#pragma once

#include <SDL2/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl_gl3.h>
#include <string>

namespace flex {
class App;

class Window {
private:
  SDL_Window *m_window;
  SDL_GLContext m_context;
  bool m_should_quit = false;

  float m_last_time = 0.0;

  void update(App &app);

public:
  Window(const std::string &title, int width, int height);
  ~Window();

  void run(App &app);
  bool should_quit() const;

  int get_width() const;
  int get_height() const;

  void set_relative_mouse(bool relative);
  bool get_relative_mouse();

  void get_relative_mouse_pos(int *x, int *y);

  bool is_key_pressed(unsigned int scancode);
};
} // namespace flex
