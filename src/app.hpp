#pragma once

#include <saucer/smartview.hpp>

coco::stray start(saucer::application* app);
void installUserScriptCompatibility(saucer::smartview&);
void loadUserScripts(saucer::smartview&);

void configureWindow(std::shared_ptr<saucer::window> window) {
  window->set_title("Yume Nikki Online Project");
  window->set_size({ .w = 1052, .h = 798 });
  window->set_background({ .r = 0, .g = 0, .b = 0, .a = 255 });
  window->set_decorations(saucer::window::decoration::none);
}