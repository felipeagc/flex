#pragma once

#include "engine.hpp"
#include "input/input.hpp"

namespace flex {
class EventHandler {
public:
  EventHandler(Engine &engine)
      : engine(engine), window(engine.get_window()),
        audio(engine.get_audio()){};
  virtual ~EventHandler(){};

  virtual void load(){};
  virtual void update(float delta){};
  virtual void quit(){};

  virtual void resized(unsigned int w, unsigned int h){};

  virtual void key_up(input::Key key, bool repeat){};
  virtual void key_down(input::Key key, bool repeat){};

  virtual void button_up(input::MouseButton button, int x, int y){};
  virtual void button_down(input::MouseButton button, int x, int y){};

  virtual void mouse_wheel(int x, int y){};
protected:
  Engine &engine;
  Window &window;
  AudioSystem &audio;
};
} // namespace flex
