#include "engine.hpp"

using namespace flex;

Engine::Engine(const std::string &title, int width, int height)
    : m_window(title, width, height) {}

Engine::~Engine() {}

Window &Engine::get_window() { return m_window; };

AudioSystem &Engine::get_audio() { return m_audio; }

GraphicsSystem &Engine::get_graphics() { return m_graphics; }
