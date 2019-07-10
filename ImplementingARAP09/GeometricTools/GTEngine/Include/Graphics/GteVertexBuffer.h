// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/11/28)

#pragma once

#include <Graphics/GteBuffer.h>
#include <Graphics/GteVertexFormat.h>

namespace gte
{

class StructuredBuffer;

class GTE_IMPEXP VertexBuffer : public Buffer
{
public:
    // This constructor is for standard usage where the vertex buffer is
    // used by the rasterizer to provide vertices to the vertex shader.
    VertexBuffer(VertexFormat const& vformat, unsigned int numVertices,
        bool createStorage = true);

    // This constructor is used for vertex-id-based drawing where the vertices
    // are read from a structured buffer resource in the vertex shader.  The
    // input 'sbuffer' must be nonnull and its number of vertices is copied
    // to 'this' number of vertices.
    VertexBuffer(VertexFormat const& vformat,
        std::shared_ptr<StructuredBuffer> const& sbuffer);

    // This constructor is used for vertex-id-based drawing that does not
    // require vertices; for example, the shader itself can generate the
    // positions from the identifiers.
    VertexBuffer(unsigned int numVertices);

    // Member access.  The function StandardUsage() returns 'true' when the
    // first constructor is used or 'false' when the second constructor is
    // used.
    inline VertexFormat const& GetFormat() const;
    inline std::shared_ptr<StructuredBuffer> const& GetSBuffer() const;
    inline bool StandardUsage() const;

    // Get pointers to attribute data if it exists for the specified semantic
    // and unit.  Also, you request that the attribute be one of a list of
    // required types (OR-ed bit flags).  If you do not care about the type,
    // pass DF_UNKNOWN for the required input.  If the request fails, a null
    // pointer is returned.
    char* GetChannel(VASemantic semantic, unsigned int unit,
        std::set<DFType> const& requiredTypes);

protected:
    VertexFormat mVFormat;

    // Valid when the second constructor is used.
    std::shared_ptr<StructuredBuffer> mSBuffer;
};


inline VertexFormat const& VertexBuffer::GetFormat() const
{
    return mVFormat;
}

inline bool VertexBuffer::StandardUsage() const
{
    return mVFormat.GetNumAttributes() != 0 && mSBuffer == nullptr;
}

inline std::shared_ptr<StructuredBuffer> const& VertexBuffer::GetSBuffer() const
{
    return mSBuffer;
}

}
