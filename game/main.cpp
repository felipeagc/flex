#include "canvas_scene.hpp"
#include "instancing_scene.hpp"
#include "mesh_scene.hpp"
#include "sprite_scene.hpp"
#include <flex/flex.hpp>
#include <flex/imgui.hpp>

namespace game {
class MyApp : public flex::EventHandler {
private:
  InstancingScene instancing_scene{engine};
  SpriteScene sprite_scene{engine};
  MeshScene mesh_scene{engine};
  CanvasScene canvas_scene{engine};

  EventHandler *current_scene = &instancing_scene;

public:
  // Inherit constructor
  using flex::EventHandler::EventHandler;

  void load() {}

  void quit() { flex::log("Quit"); }

  void set_scene(flex::EventHandler *scene) {
    current_scene = scene;
    current_scene->load();
  }

  void update(float delta) {
    current_scene->update(delta);

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Scene")) {
        if (ImGui::MenuItem("Instancing")) {
          set_scene(&instancing_scene);
        }
        if (ImGui::MenuItem("Sprites")) {
          set_scene(&sprite_scene);
        }
        if (ImGui::MenuItem("Mesh")) {
          set_scene(&mesh_scene);
        }
        if (ImGui::MenuItem("Canvas")) {
          set_scene(&canvas_scene);
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    {
      ImGui::Begin("Hello");
      ImGui::Text("FPS: %f", 1.0 / delta);
      ImGui::End();
    }
  }

  void key_down(flex::input::Key key, bool repeat) {
    if (key == FLEX_KEY_ESCAPE) {
      window.set_relative_mouse(!window.get_relative_mouse());
    }
  }

  void mouse_wheel(int x, int y) { current_scene->mouse_wheel(x, y); }

  void resized(unsigned int w, unsigned int h) { current_scene->resized(w, h); }
};
} // namespace game

int main() {
  flex::Engine engine{"Half-Life 3", 800, 600};
  game::MyApp app{engine};

  engine.get_window().run(app);

  return 0;
}
