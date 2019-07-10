// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteDepthStencilState.h>
#include <Graphics/GL4/GteGL4DrawingState.h>

namespace gte
{

class GTE_IMPEXP GL4DepthStencilState : public GL4DrawingState
{
public:
    // Construction.
    GL4DepthStencilState(DepthStencilState const* depthStencilState);
    static std::shared_ptr<GEObject> Create(void* unused, GraphicsObject const* object);

    // Member access.
    inline DepthStencilState* GetDepthStencilState();

    // Enable the depth-stencil state.
    void Enable();

private:
    struct Face
    {
        GLenum onFail;
        GLenum onZFail;
        GLenum onZPass;
        GLenum comparison;
    };

    GLboolean mDepthEnable;
    GLboolean mWriteMask;
    GLenum mComparison;
    GLboolean mStencilEnable;
    GLuint mStencilReadMask;
    GLuint mStencilWriteMask;
    Face mFrontFace;
    Face mBackFace;
    GLuint mReference;

    // Conversions from GTEngine values to GL4 values.
    static GLboolean const msWriteMask[];
    static GLenum const msComparison[];
    static GLenum const msOperation[];
};

inline DepthStencilState* GL4DepthStencilState::GetDepthStencilState()
{
    return static_cast<DepthStencilState*>(mGTObject);
}

}
