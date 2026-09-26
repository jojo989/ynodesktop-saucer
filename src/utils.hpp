#pragma once

#include <filesystem>
#include <string_view>

std::filesystem::path getDataDir(std::string_view appName);