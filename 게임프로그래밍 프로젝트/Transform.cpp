#include "pch.h"
#include "Transform.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM), x(0), y(0), m_parent(0)
{
}

Transform::~Transform()
{
}

Vector2 Transform::GetWorldPosition()
{
    vector<shared_ptr<Transform>> hierarchy;
    
    hierarchy.push_back(shared_from_this());
    
    while (hierarchy.back()->FlagParent())
    {
        hierarchy.push_back(hierarchy.back()->GetParent());
    }

    Vector2 returnPos = { 0, 0 };
    for (int i = 0; i < hierarchy.size(); i++)
    {
        returnPos = returnPos + hierarchy[i]->GetLocalPosition();
    }

    return returnPos;
}

void Transform::SetLocalPosition(Vector2 value)
{
    x = value.x;
    y = value.y;
}

void Transform::SetWorldPosition(Vector2 value)
{
    Vector2 parentPos = GetWorldPosition() - GetLocalPosition();
    parentPos = parentPos * -1;

    x = parentPos.x + value.x;
    y = parentPos.y + value.y;
}
