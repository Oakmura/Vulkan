#pragma once

#ifdef _DEBUG
#define ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ASSERT(x, ...)
#endif

#ifdef _DEBUG
#define VK_ASSERT(x, ...) { if ((x) != VK_SUCCESS) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define VK_ASSERT(x, ...) x
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(ARR[0]))
#endif

namespace lve
{
    class BasicUtils final
    {
    public:
        static std::vector<char> ReadFile(const char *filename);
    };
}