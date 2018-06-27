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
  virtual void update(f32 delta){};
  virtual void quit(){};

  virtual void resized(u32 w, u32 h){};

  virtual void key_up(input::Key key, bool repeat){};
  virtual void key_down(input::Key key, bool repeat){};

  virtual void button_up(input::MouseButton button, i32 x, i32 y){};
  virtual void button_down(input::MouseButton button, i32 x, i32 y){};

  virtual void mouse_wheel(i32 x, i32 y){};
protected:
  Engine &engine;
  Window &window;
  AudioSystem &audio;
};
} // namespace flex
