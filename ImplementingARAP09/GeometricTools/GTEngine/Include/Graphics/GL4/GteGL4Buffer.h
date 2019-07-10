// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteBuffer.h>
#include <Graphics/GL4/GteGL4Resource.h>

namespace gte
{

class GTE_IMPEXP GL4Buffer : public GL4Resource
{
protected:
    // Abstract base class.
    virtual ~GL4Buffer();
    GL4Buffer(Buffer const* buffer, GLenum type);

    // Must be called by constructor.
    virtual void Initialize();

public:
    // Member access.
    inline Buffer* GetBuffer() const;
    inline GLenum GetType() const;
    inline GLenum GetUsage() const;

    // TODO: TENTATIVE INTERFACE (modify as needed).  Do we really need
    // these to be virtual?  Revisit the DX11 code and investigate why the
    // choice was made there.
    virtual bool Update();
    virtual bool CopyCpuToGpu();
    virtual bool CopyGpuToCpu();

protected:
    GLenum mType;
    GLenum mUsage;
};

inline Buffer* GL4Buffer::GetBuffer() const
{
    return static_cast<Buffer*>(mGTObject);
}

inline GLenum GL4Buffer::GetType() const
{
    return mType;
}

inline GLenum GL4Buffer::GetUsage() const
{
    return mUsage;
}

}
