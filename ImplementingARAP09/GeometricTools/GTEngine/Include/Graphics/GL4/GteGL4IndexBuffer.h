// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteIndexBuffer.h>
#include <Graphics/GL4/GteGL4Buffer.h>

namespace gte
{

class GTE_IMPEXP GL4IndexBuffer : public GL4Buffer
{
public:
    // Construction.
    GL4IndexBuffer(IndexBuffer const* ibuffer);
    static std::shared_ptr<GEObject> Create(void* unused, GraphicsObject const* object);

    // Member access.
    inline IndexBuffer* GetIndexBuffer() const;

    // Support for drawing geometric primitives.
    void Enable();
    void Disable();
};

inline IndexBuffer* GL4IndexBuffer::GetIndexBuffer() const
{
    return static_cast<IndexBuffer*>(mGTObject);
}

}
