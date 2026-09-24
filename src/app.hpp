#pragma once

#include <print>
#include <saucer/smartview.hpp>
#include <cstdlib>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

coco::stray start(saucer::application *app);
void installUserScriptCompatibility(saucer::smartview&);
void loadUserScripts(saucer::smartview&);
