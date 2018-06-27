#include "window.hpp"
#include "event_handler.hpp"
#include "gl/gl.hpp"
#include "imgui.hpp"
#include "input/input.hpp"

using namespace flex;

Window::Window(const char *title, u32 width, u32 height) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    flex::log(L_ERROR, L_WINDOW, "SDL_Init Error: '%s'", SDL_GetError());
    std::exit(1);
  }

  this->m_window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       (i32)width, (i32)height, SDL_WINDOW_OPENGL);

  if (this->m_window == NULL) {
    flex::log(L_ERROR, L_WINDOW, "Could not create SDL window: '%s'",
              SDL_GetError());
    SDL_Quit();
    std::exit(1);
  }

  flex::log(L_DEBUG, L_WINDOW, "Window created successfully");

  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
  //                     SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
  // SDL_GL_CONTEXT_PROFILE_ES);
  // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  i32 major;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
  i32 minor;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &minor);

  flex::log(L_DEBUG, L_GL, "Using OpenGL version %d.%d", major, minor);

  m_context = SDL_GL_CreateContext(m_window);
  if (m_context == NULL) {
    flex::log(L_ERROR, L_GL, "Failed to initialize OpenGL context");
    std::exit(1);
  }

  flex::log(L_DEBUG, L_GL, "GL context initialized successfully");

  GL_CALL(glEnable(GL_DEPTH_TEST));
  GL_CALL(glViewport(0, 0, width, height));

  // Enable vsync
  SDL_GL_SetSwapInterval(1);

  // Init ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui_ImplSdlGL3_Init(m_window);
  ImGui::StyleColorsDark();
}

Window::~Window() {
  ImGui_ImplSdlGL3_Shutdown();
  ImGui::DestroyContext();
  SDL_GL_DeleteContext(m_context);
  SDL_DestroyWindow(this->m_window);
  SDL_Quit();
}

void Window::update(EventHandler &event_handler) {
  SDL_Event e;
  gl::clear_color(0.2f, 0.3f, 0.3f, 1.0f);
  gl::clear_buffers();

  while (SDL_PollEvent(&e)) {
    ImGui_ImplSdlGL3_ProcessEvent(&e);

    switch (e.type) {
    case SDL_QUIT:
      this->m_should_quit = true;
      break;
    case SDL_KEYUP:
      event_handler.key_up(e.key.keysym.sym, e.key.repeat);
      break;
    case SDL_KEYDOWN:
      event_handler.key_down(e.key.keysym.sym, e.key.repeat);
      break;
    case SDL_MOUSEBUTTONDOWN:
      event_handler.button_down(e.button.button, e.button.x, e.button.y);
      break;
    case SDL_MOUSEBUTTONUP:
      event_handler.button_up(e.button.button, e.button.x, e.button.y);
      break;
    case SDL_MOUSEWHEEL: {
      i32 x = e.wheel.x;
      i32 y = e.wheel.y;
      if (e.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
        x *= -1;
        y *= -1;
      }
      event_handler.mouse_wheel(x, y);
    } break;
    case SDL_WINDOWEVENT:
      switch (e.window.event) {
      case SDL_WINDOWEVENT_RESIZED:
        GL_CALL(glViewport(0, 0, e.window.data1, e.window.data2));
        event_handler.resized((u32)e.window.data1, (u32)e.window.data2);
        break;
      }
      break;
    }
  }

  ImGui_ImplSdlGL3_NewFrame(m_window);

  f32 now = (f32)SDL_GetTicks() / 1000.0;

  event_handler.update(now - m_last_time);

  ImGui::Render();
  ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());

  m_last_time = now;

  SDL_GL_SwapWindow(m_window);
}

void Window::run(EventHandler &event_handler) {
  event_handler.load();

  while (!should_quit()) {
    update(event_handler);
  }

  event_handler.quit();

  flex::log(L_DEBUG, L_WINDOW, "Quitting...");
}

bool Window::should_quit() const { return m_should_quit; }

u32 Window::get_width() const {
  i32 width;
  SDL_GetWindowSize(m_window, &width, NULL);
  return (u32)width;
}

u32 Window::get_height() const {
  i32 height;
  SDL_GetWindowSize(m_window, NULL, &height);
  return (u32)height;
}

void Window::set_relative_mouse(bool relative) {
  SDL_SetRelativeMouseMode(relative ? SDL_TRUE : SDL_FALSE);
}

bool Window::get_relative_mouse() { return SDL_GetRelativeMouseMode(); }

void Window::get_relative_mouse_pos(i32 *x, i32 *y) {
  SDL_GetRelativeMouseState(x, y);
}

bool Window::is_key_pressed(u32 scancode) {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  return state[scancode] ? true : false;
}
