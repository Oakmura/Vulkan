#include "Precompiled.h"

#include "Model.h"

namespace lve
{

Model::Model(Device& device, const std::vector<Vertex>& vertices) 
    : mDevice(device) 
{
    mVertexCount = static_cast<uint32_t>(vertices.size());
    ASSERT(mVertexCount >= 3, "Vertex count must be at least 3");

    VkDeviceSize bufferSize = sizeof(vertices[0]) * mVertexCount;
    mDevice.CreateBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         mVertexBuffer, mVertexBufferMemory);

    void *data;
    vkMapMemory(mDevice.Get(), mVertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize)); // vertexBufferMemory <- vertices
    vkUnmapMemory(mDevice.Get(), mVertexBufferMemory);
}

Model::~Model()
{
    vkDestroyBuffer(mDevice.Get(), mVertexBuffer, nullptr);
    vkFreeMemory(mDevice.Get(), mVertexBufferMemory, nullptr);
}

void Model::Bind(VkCommandBuffer commandBuffer)
{
    VkBuffer buffers[] = { mVertexBuffer };
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

void Model::Draw(VkCommandBuffer commandBuffer) 
{ 
    vkCmdDraw(commandBuffer, mVertexCount, 1, 0, 0); 
}

std::vector<VkVertexInputBindingDescription> Model::Vertex::GetBindingDescriptions()
{
    std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
    bindingDescriptions[0].binding = 0;
    bindingDescriptions[0].stride = sizeof(Vertex);
    bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescriptions;
}

std::vector<VkVertexInputAttributeDescription> Model::Vertex::GetAttributeDescriptions()
{
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, Position);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, Color);

    return attributeDescriptions;
}

} // namespace lve
