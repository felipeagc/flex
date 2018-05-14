#include "window.hpp"

using namespace flex;

Window::Window(const std::string &name, int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    std::exit(1);
  }

  this->m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, width, height,
                                    SDL_WINDOW_OPENGL);

  if (this->m_window == NULL) {
    std::cout << "Could not create SDL window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(1);
  }

  auto context = SDL_GL_CreateContext(m_window);
  if (context == NULL) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    std::exit(1);
  }

  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    std::exit(1);
  }

  glViewport(0, 0, width, height);
}

Window::~Window() {
  SDL_DestroyWindow(this->m_window);
  SDL_Quit();
}

void Window::run() {
  SDL_Event e;
  while (!this->m_should_quit) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        this->m_should_quit = true;
        break;
      }
    }

    float now = (float) SDL_GetTicks() / 1000.0;

    this->m_update(now - m_last_time);

    m_last_time = now;

    SDL_GL_SwapWindow(m_window);
  }

  this->m_on_quit();
}
