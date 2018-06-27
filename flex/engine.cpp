#include "engine.hpp"

using namespace flex;

Engine::Engine(const char* title, u32 width, u32 height)
    : m_window(title, width, height) {}

Engine::~Engine() {}

Window &Engine::get_window() { return m_window; };

AudioSystem &Engine::get_audio() { return m_audio; }
