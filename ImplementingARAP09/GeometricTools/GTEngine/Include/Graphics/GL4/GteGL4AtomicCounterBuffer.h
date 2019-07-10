// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteRawBuffer.h>
#include <Graphics/GL4/GteGL4Buffer.h>

namespace gte
{

class GTE_IMPEXP GL4AtomicCounterBuffer : public GL4Buffer
{
public:
    // Construction.
    GL4AtomicCounterBuffer(RawBuffer const* cbuffer);
    static std::shared_ptr<GEObject> Create(void* unused, GraphicsObject const* object);

    // Member access.
    inline RawBuffer* GetRawBuffer() const;

    // Bind the raw buffer data to the specified atomic counter buffer unit.
    void AttachToUnit(GLint atomicCounterBufferUnit);
};


inline RawBuffer* GL4AtomicCounterBuffer::GetRawBuffer() const
{
    return static_cast<RawBuffer*>(mGTObject);
}

}
