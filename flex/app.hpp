#pragma once

#include "engine.hpp"
#include "input/input.hpp"
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

  virtual void key_up(input::Key key, bool repeat){};
  virtual void key_down(input::Key key, bool repeat){};

  virtual void button_up(input::MouseButton button, int x, int y){};
  virtual void button_down(input::MouseButton button, int x, int y){};

protected:
  Engine &engine;
  Window &window;
  AudioSystem &audio;
  GraphicsSystem &graphics;
};
} // namespace flex
