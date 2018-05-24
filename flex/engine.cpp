#include "engine.hpp"

using namespace flex;

Engine::Engine(const std::string &title, int width, int height) {
  m_window = std::make_unique<Window>(title, width, height);
  m_audio = std::make_unique<AudioSystem>();
}

Engine::~Engine() {}

Window *Engine::get_window() { return m_window.get(); };

AudioSystem *Engine::get_audio() { return m_audio.get(); }
