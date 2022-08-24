#include "CollisionComponent.h"
#include "Engine.h"

namespace Bear
{
    void CollisionComponent::Initialize()
    {
        auto component = m_owner->GetComponent<RBPhysicsComponent>();
        if (component)
        {
            g_physicsSystem.SetCollisionBox(component->m_body, data, m_owner);
        }
    }

    void CollisionComponent::Update()
    {

    }

    bool CollisionComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CollisionComponent::Read(const rapidjson::Value& value)
    {
        Vector2 size;
        float density = 1;
        float friction = 1;
        float restitution = 0.3f;
        bool is_trigger = false;

        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.is_trigger);

        return true;
    }

    void CollisionComponent::OnCollisionEnter(Actor* other)
    {
        if(m_enterFunction) m_enterFunction(other);
    }

    void CollisionComponent::OnCollisionExit(Actor* other)
    {
        if(m_exitFunction) m_exitFunction(other);
    }
}