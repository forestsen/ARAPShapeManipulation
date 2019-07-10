// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteGEDrawTarget.h>
#include <Graphics/GL4/GteGL4TextureDS.h>
#include <Graphics/GL4/GteGL4TextureRT.h>

namespace gte
{

class GTE_IMPEXP GL4DrawTarget : public GEDrawTarget
{
public:
    // Construction and destruction.
    virtual ~GL4DrawTarget();
    GL4DrawTarget(DrawTarget const* target,
        std::vector<GL4TextureRT*>& rtTextures, GL4TextureDS* dsTexture);
    static std::shared_ptr<GEDrawTarget> Create(DrawTarget const* target,
        std::vector<GEObject*>& rtTextures, GEObject* dsTexture);

    // Member access.
    inline GL4TextureRT* GetRTTexture(unsigned int i) const;
    inline GL4TextureDS* GetDSTexture() const;

    // Used in the Renderer::Draw function.
    void Enable();
    void Disable();

private:
    std::vector<GL4TextureRT*> mRTTextures;
    GL4TextureDS* mDSTexture;

    GLuint mFrameBuffer;

    // Temporary storage during enable/disable of targets.
    GLint mSaveViewportX;
    GLint mSaveViewportY;
    GLsizei mSaveViewportWidth;
    GLsizei mSaveViewportHeight;
    GLdouble mSaveViewportNear;
    GLdouble mSaveViewportFar;
};

inline GL4TextureRT* GL4DrawTarget::GetRTTexture(unsigned int i) const
{
    return mRTTextures[i];
}

inline GL4TextureDS* GL4DrawTarget::GetDSTexture() const
{
    return mDSTexture;
}

}
