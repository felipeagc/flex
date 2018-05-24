#include "app.hpp"

using namespace flex;

App::App(Engine &engine) { m_engine = &engine; }

Window *App::get_window() { return m_engine->get_window(); };

AudioSystem *App::get_audio() { return m_engine->get_audio(); };
