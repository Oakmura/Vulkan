#pragma once

#include "Model.h"

namespace lve
{

struct Transform2dComponent
{
    glm::vec2 Translation{}; // (position offset)
    glm::vec2 Scale{1.f, 1.f};
    float Rotation;

    glm::mat2 mat2()
    {
        const float s = glm::sin(Rotation);
        const float c = glm::cos(Rotation);
        glm::mat2 rotMatrix{{c, s}, {-s, c}};
        glm::mat2 scaleMat{{Scale.x, .0f}, {.0f, Scale.y}};

        return rotMatrix * scaleMat;
    }
};

class GameObject final
{
    using id_t = unsigned int;

public:
    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) = delete;
    GameObject(GameObject &&) = default;
    GameObject &operator=(GameObject &&) = default;

    static GameObject CreateGameObject()
    {
        static id_t currentId = 0;
        return GameObject{currentId++};
    }

    inline id_t GetId() { return id; }

    std::shared_ptr<Model> mModel{};
    glm::vec3 mColor{};
    Transform2dComponent mTransform2d{};

private:
    GameObject(id_t objId) : id{objId} {}

    id_t id;
};

} // namespace lve