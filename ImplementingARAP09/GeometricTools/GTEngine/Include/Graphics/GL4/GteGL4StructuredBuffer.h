// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteStructuredBuffer.h>
#include <Graphics/GL4/GteGL4Buffer.h>

namespace gte
{

class GTE_IMPEXP GL4StructuredBuffer : public GL4Buffer
{
public:
    // Construction.
    GL4StructuredBuffer(StructuredBuffer const* cbuffer);
    static std::shared_ptr<GEObject> Create(void* unused, GraphicsObject const* object);

    // Member access.
    inline StructuredBuffer* GetStructuredBuffer() const;

    // Bind the structured buffer data to the specified shader
    // storage buffer unit.
    void AttachToUnit(GLint shaderStorageBufferUnit);

    // Copy the counter value to/from another buffer.
    bool CopyCounterValueToBuffer(GL4Buffer* targetBuffer, GLint offset);
    bool CopyCounterValueFromBuffer(GL4Buffer* sourceBuffer, GLint offset);

    // The number of active elements is read from GPU and stored in the
    // StructuredBuffer object  (of type CT_APPEND_CONSUME or CT_COUNTER).
    // The result can be accessed from this object via its member function
    // GetNumActiveElements().
    bool GetNumActiveElements();

    // The number of active elements is written to GPU from the StructuredBuffer
    // object (of type CT_APPEND_CONSUME or CT_COUNTER).  The number of active
    // elements can be changed in the StructuredBuffer object via its member
    // function SetNumActiveElements.
    bool SetNumActiveElements();

    // Override needed to handle case of a counter attached so that
    // counter value can be updated first to know how many elements
    // to copy back from GPU.
    virtual bool CopyGpuToCpu() override;

protected:
    // Must be called by constructor.
    virtual void Initialize() override;

private:
    GLint mCounterOffset;
};

inline StructuredBuffer* GL4StructuredBuffer::GetStructuredBuffer() const
{
    return static_cast<StructuredBuffer*>(mGTObject);
}

}
