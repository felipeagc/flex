#include "instancing_scene.hpp"
#include "mesh_scene.hpp"
#include "sprite_scene.hpp"
#include <flex/flex.hpp>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace game {
class MyApp : public flex::EventHandler {
private:
  InstancingScene instancing_scene{engine};
  SpriteScene sprite_scene{engine};
  MeshScene mesh_scene{engine};

  std::vector<EventHandler *> scenes = {&instancing_scene, &sprite_scene,
                                        &mesh_scene};

  int current_scene = 0;

public:
  // Inherit constructor
  using flex::EventHandler::EventHandler;

  void load() { window.set_relative_mouse(true); }

  void quit() { flex::log("Quit"); }

  void update(float delta) {
    scenes[current_scene]->update(delta);

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

    if (key == FLEX_KEY_RIGHT) {
      if (current_scene + 1 < scenes.size()) {
        current_scene++;
      }
    }

    if (key == FLEX_KEY_LEFT) {
      if (current_scene - 1 >= 0) {
        current_scene--;
      }
    }
  }
};
} // namespace game

int main() {
  flex::Engine engine{"Half-Life 3", 800, 600};
  game::MyApp app{engine};

  engine.get_window().run(app);

  return 0;
}
