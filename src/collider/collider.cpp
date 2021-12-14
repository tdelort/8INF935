#include "Collider.h"

Matrix3x4 *Collider::getOffset() const
{
    return m_offset;
}

Rigidbody* Collider::getRigidbody() const
{
    return rigidbody;
}