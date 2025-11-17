#pragma once

#include <vector>
#include <utility>
#include <glm/glm.hpp>

using glm::fvec3;
using glm::fvec4;
using std::pair;
using std::vector;

/// @brief Pair of vector of vertices and vector of colors.
using Shape = pair<vector<fvec3>, vector<fvec4>>;