#pragma once

#include "RigidBody.h"
#include "colliders/Primitive.h"
#include "IDrawable.h"

struct GameObject
{
    RigidBody* rb;
    Primitive* collider;
    IDrawable* drawable;

    GameObject(RigidBody* rb, Primitive* collider, IDrawable* drawable)
        : rb(rb), collider(collider), drawable(drawable)
    { }
};