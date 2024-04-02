#include "Precompiled.h"

#include "BasicUtils.h"

namespace lve
{
    std::vector<char> lve::BasicUtils::ReadFile(const char *filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        ASSERT(file.is_open(), "readFile() : Failed to open file {0}", filename);

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        return buffer;
    }
} // namespace lve