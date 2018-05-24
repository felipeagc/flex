#include "window.hpp"

using namespace flex;

Window::Window(const std::string &title, int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    flex::log(L_ERROR, L_WINDOW,
              "SDL_Init Error: " + std::string(SDL_GetError()));
    std::exit(1);
  }

  this->m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, width, height,
                                    SDL_WINDOW_OPENGL);

  if (this->m_window == NULL) {
    flex::log(L_ERROR, L_WINDOW,
              "Could not create SDL window: " + std::string(SDL_GetError()));
    SDL_Quit();
    std::exit(1);
  }

  flex::log(L_DEBUG, L_WINDOW, "Window created successfully");

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetSwapInterval(0);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  auto context = SDL_GL_CreateContext(m_window);
  if (context == NULL) {
    flex::log(L_ERROR, L_GL, "Failed to initialize OpenGL context");
    std::exit(1);
  }

  flex::log(L_DEBUG, L_GL, "GL context initialized successfully");

  GL_CALL(glEnable(GL_DEPTH_TEST));
  GL_CALL(glViewport(0, 0, width, height));
}

Window::~Window() {
  SDL_DestroyWindow(this->m_window);
  SDL_Quit();
}

void Window::update(App &app) {
  SDL_Event e;
  GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
  GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      this->m_should_quit = true;
      break;
    case SDL_KEYUP:
      app.key_up(e.key.keysym.sym, e.key.repeat);
      break;
    case SDL_KEYDOWN:
      app.key_down(e.key.keysym.sym, e.key.repeat);
      break;
    case SDL_WINDOWEVENT:
      switch (e.window.event) {
      case SDL_WINDOWEVENT_RESIZED:
        GL_CALL(glViewport(0, 0, e.window.data1, e.window.data2));
        app.resized(e.window.data1, e.window.data2);
        break;
      }
      break;
    }
  }

  float now = (float)SDL_GetTicks() / 1000.0;

  app.update(now - m_last_time);

  m_last_time = now;

  SDL_GL_SwapWindow(m_window);
}

void Window::run(App &app) {
  app.load();

  while (!should_quit()) {
    update(app);
  }

  app.quit();

  flex::log(L_DEBUG, L_WINDOW, "Quitting...");
}

bool Window::should_quit() const { return m_should_quit; }

int Window::get_width() const {
  int width;
  SDL_GetWindowSize(m_window, &width, NULL);
  return width;
}

int Window::get_height() const {
  int height;
  SDL_GetWindowSize(m_window, NULL, &height);
  return height;
}

void Window::set_relative_mouse(bool relative) {
  SDL_SetRelativeMouseMode(relative ? SDL_TRUE : SDL_FALSE);
}

bool Window::get_relative_mouse() { return SDL_GetRelativeMouseMode(); }

void Window::get_relative_mouse_pos(int *x, int *y) {
  SDL_GetRelativeMouseState(x, y);
}

bool Window::is_key_pressed(unsigned int scancode) {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  return state[scancode] ? true : false;
}
