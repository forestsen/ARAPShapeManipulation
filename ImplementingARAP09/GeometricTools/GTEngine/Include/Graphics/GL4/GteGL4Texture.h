// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTexture.h>
#include <Graphics/GL4/GteGL4Resource.h>

namespace gte
{

class GTE_IMPEXP GL4Texture : public GL4Resource
{
protected:
    // Abstract base class.
    GL4Texture(Texture const* texture, GLenum target, GLenum targetBinding);

public:
    // Member access.
    inline Texture* GetTexture() const;
    inline GLenum GetTarget() const;
    inline GLenum GetTargetBinding() const;

    // Get the GL4 internal format for the specified Texture data format.
    inline static GLuint GetInternalFormat(DFType dataFormat);

protected:
    GLenum mTarget;
    GLenum mTargetBinding;

    // Properties of overall texture.
    GLint mNumLevels;
    GLuint mInternalFormat;
    GLuint mExternalFormat;
    GLuint mExternalType;

    // Mapping from DFType to GL4 specific types
    static GLuint const msGLTextureInternalFormat[DF_NUM_FORMATS];
    static GLuint const msGLTextureExternalFormat[DF_NUM_FORMATS];
    static GLuint const msGLTextureExternalType[DF_NUM_CHANNEL_TYPES];
};

inline GLuint GL4Texture::GetInternalFormat(DFType dataFormat)
{
    return msGLTextureInternalFormat[dataFormat];
}

inline Texture* GL4Texture::GetTexture() const
{
    return static_cast<Texture*>(mGTObject);
}

inline GLenum GL4Texture::GetTarget() const
{
    return mTarget;
}

inline GLenum GL4Texture::GetTargetBinding() const
{
    return mTargetBinding;
}

}
