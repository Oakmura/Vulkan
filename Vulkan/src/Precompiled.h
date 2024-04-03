#pragma once

#include <algorithm>
#include <array>

#include <chrono>
#include <cstdlib>
#include <fstream>

#include <optional>
#include <iostream>
#include <limits>
#include <memory>

#include <set>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
// #define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "Core/Logger.h"
#include "Utils/BasicUtils.h"