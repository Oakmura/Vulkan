#pragma once

#ifdef _DEBUG
#define ASSERT(x) { if(!(x)) { __debugbreak(); } }
#else
#define ASSERT(x)
#endif

#ifdef _DEBUG
#define VK_ASSERT(x) { if ((x) != VK_SUCCESS) { __debugbreak(); } }
#else
#define VK_ASSERT(x)
#endif