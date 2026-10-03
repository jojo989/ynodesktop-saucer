#pragma once

#include <filesystem>
#include <string_view>
#include <optional>

std::filesystem::path getDataDir(std::string_view appName);
std::optional<std::string> parseGameName(std::string_view url);
std::string urlEncode(std::string_view s);