#include "SphereCollider.h"

void SphereCollider::Initialize(float radius, Vector3D offset)
{
    m_radius = radius;
}

float SphereCollider::getRadius() const
{
    return m_radius;
}

void SphereCollider::setRadius(float radius)
{
    m_radius = radius;
}


