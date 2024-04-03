#pragma once

#include "Device.h"

namespace lve
{
class Model final
{
public:
    struct Vertex
    {
        glm::vec2 Position;
        glm::vec3 Color;

        static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
    };

    Model(Device &device, const std::vector<Vertex> &vertices);
    ~Model();
    Model(const Model &) = delete;
    Model &operator=(const Model &) = delete;

    void Bind(VkCommandBuffer commandBuffer);
    void Draw(VkCommandBuffer commandBuffer);

private:
    Device &mDevice;
    VkBuffer mVertexBuffer;
    VkDeviceMemory mVertexBufferMemory;
    uint32_t mVertexCount;
};
} // namespace lve