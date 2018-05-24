#pragma once

#include "engine.hpp"
#include "keyboard/keyboard.hpp"
#include <memory>

namespace flex {
class Window;
class Engine;

class App {

public:
  App(Engine &engine);

  virtual ~App(){};

  virtual void load(){};
  virtual void update(float delta){};
  virtual void quit(){};

  virtual void resized(int w, int h){};
  virtual void key_up(keyboard::Key key, bool repeat){};
  virtual void key_down(keyboard::Key key, bool repeat){};

protected:
  Window *get_window();
  AudioSystem *get_audio();

private:
  Engine *m_engine;
};
} // namespace flex
