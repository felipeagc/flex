#include "app.hpp"

using namespace flex;

App::App(Engine &engine)
    : engine(engine), window(engine.get_window()), audio(engine.get_audio()),
      graphics(engine.get_graphics()) {}
