#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;
inline std::string get_stem(const fs::path& p) { return p.stem().string(); }
int daily_data(const std::string& path);
int tick_data(const std::string& path);
