#pragma once

#include "SceneCamera.h"
#include "Miriya/Core/UUID.h"
#include "Miriya/Renderer/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "box2d/id.h"

namespace Miriya {

struct IDComponent
{
    UUID ID;

    IDComponent()                   = default;
    IDComponent(const IDComponent&) = default;
    IDComponent(const UUID& uuid)
        : ID(uuid)
    {}
};

struct TagComponent
{
    std::string Tag;

    TagComponent()                    = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag)
        : Tag(tag)
    {}
};

struct TransformComponent
{
    glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Rotation    = {0.0f, 0.0f, 0.0f};
    glm::vec3 Scale       = {1.0f, 1.0f, 1.0f};

    TransformComponent()                          = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& translation)
        : Translation(translation)
    {}

    glm::mat4 GetTransform() const
    {
        glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

        return glm::translate(glm::mat4(1.0f), Translation) * rotation *
               glm::scale(glm::mat4(1.0f), Scale);
    }
};

struct SpriteRendererComponent
{
    glm::vec4      Color{1.0f, 1.0f, 1.0f, 1.0f};
    Ref<Texture2D> Texture;
    float          TilingFactor = 1.0f;

    SpriteRendererComponent()                               = default;
    SpriteRendererComponent(const SpriteRendererComponent&) = default;
    SpriteRendererComponent(const glm::vec4& color)
        : Color(color)
    {}
};

struct CircleRendererComponent
{
    glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
    float     Thickness = 1.0f;
    float     Fade      = 0.005f;

    CircleRendererComponent()                               = default;
    CircleRendererComponent(const CircleRendererComponent&) = default;
};

struct CameraComponent
{
    SceneCamera Camera;
    bool        Primary          = true;   // TODO: think about moving to Scene
    bool        FixedAspectRatio = false;

    CameraComponent()                       = default;
    CameraComponent(const CameraComponent&) = default;
};

// Forward declaration
class ScriptableEntity;
struct NativeScriptComponent;
void DestroyNativeScript(NativeScriptComponent* nsc);

struct NativeScriptComponent
{
    ScriptableEntity* Instance = nullptr;

    ScriptableEntity* (*InstantiateScript)();
    void (*DestroyScript)(NativeScriptComponent*);

    template<typename T> void Bind()
    {
        InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
        DestroyScript     = DestroyNativeScript;
    }
};

// Physics

struct Rigidbody2DComponent
{
    enum class BodyType
    {
        Static = 0,
        Dynamic,
        Kinematic
    };
    BodyType Type          = BodyType::Static;
    bool     FixedRotation = false;

    // Storage for runtime
    b2BodyId RuntimeBody = b2_nullBodyId;

    Rigidbody2DComponent()                            = default;
    Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
};

struct BoxCollider2DComponent
{
    glm::vec2 Offset = {0.0f, 0.0f};
    glm::vec2 Size   = {0.5f, 0.5f};

    // TODO(Yan): move into physics material in the future maybe
    float Density              = 1.0f;
    float Friction             = 0.5f;
    float Restitution          = 0.0f;
    float RestitutionThreshold = 0.5f;

    // Storage for runtime
    // void* RuntimeFixture = nullptr;
    b2ShapeId RuntimeFixture = b2_nullShapeId;

    BoxCollider2DComponent()                              = default;
    BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
};

}   // namespace Miriya