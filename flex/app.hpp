#pragma once

#include "keyboard/keyboard.hpp"
#include "window.hpp"
#include <memory>

namespace flex {
class Window;

class App {
  friend class Window;

public:
  App(Window &window) { m_window = &window; }

  virtual ~App(){};

  virtual void load(){};
  virtual void update(float delta){};
  virtual void quit(){};

  virtual void resized(int w, int h){};
  virtual void key_up(keyboard::Key key, bool repeat){};
  virtual void key_down(keyboard::Key key, bool repeat){};

protected:
  Window *get_window() { return m_window; };

private:
  Window *m_window;
};
} // namespace flex
