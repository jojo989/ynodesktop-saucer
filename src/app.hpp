#pragma once

#include <memory>
#include <saucer/smartview.hpp>

coco::stray start(saucer::application* app);
void installUserScriptCompatibility(saucer::smartview&);
void loadUserScripts(saucer::smartview&);

void configureWindow(std::shared_ptr<saucer::window> window);
saucer::smartview setupWebView(std::shared_ptr<saucer::window> window, std::filesystem::path storagePath, bool hardwareAccel = true);