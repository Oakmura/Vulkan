#include "Precompiled.h"

#include "Pipeline.h"

namespace lve
{
    Pipeline::Pipeline(const char* vertFilename, const char* fragFilename)
    {
        std::vector<char> vertShaderCode = readFile("Resources/Shaders/vert.spv");
        std::vector<char> fragShaderCode = readFile("Resources/Shaders/frag.spv");

        std::cout << "Vertex Shader Code Size: " << vertShaderCode.size() << '\n';
        std::cout << "Fragment Shader Code Size: " << fragShaderCode.size() << '\n';
    }

    Pipeline::~Pipeline()
    {

    }

    std::vector<char> Pipeline::readFile(const char* filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        ASSERT(file.is_open());

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        return buffer;
    }
}
