// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteBlendState.h>
#include <Graphics/GL4/GteGL4DrawingState.h>

namespace gte
{

class GTE_IMPEXP GL4BlendState : public GL4DrawingState
{
public:
    // Construction.
    GL4BlendState(BlendState const* blendState);
    static std::shared_ptr<GEObject> Create(void* unused, GraphicsObject const* object);

    // Member access.
    inline BlendState* GetBlendState();

    // Enable the blend state.
    void Enable();

private:
    struct Target
    {
        GLboolean enable;
        GLenum srcColor;
        GLenum dstColor;
        GLenum opColor;
        GLenum srcAlpha;
        GLenum dstAlpha;
        GLenum opAlpha;
        GLboolean rMask;
        GLboolean gMask;
        GLboolean bMask;
        GLboolean aMask;
    };

    bool mEnableAlphaToCoverage;
    bool mEnableIndependentBlend;
    Target mTarget[BlendState::NUM_TARGETS];
    Vector4<float> mBlendColor;
    unsigned int mSampleMask;

    // Conversions from GTEngine values to GL4 values.
    static GLenum const msMode[];
    static GLenum const msOperation[];
};

inline BlendState* GL4BlendState::GetBlendState()
{
    return static_cast<BlendState*>(mGTObject);
}

}
