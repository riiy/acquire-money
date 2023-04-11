#pragma once

#include <filesystem>

namespace fs = std::filesystem;
inline std::string get_stem(const fs::path& p) { return p.stem().string(); }
int daily_data();
int tick_data();
