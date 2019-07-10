// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTextureRT.h>
#include <Graphics/GL4/GteGL4Texture2.h>

namespace gte
{

class GTE_IMPEXP GL4TextureRT : public GL4Texture2
{
public:
    // Construction.
    GL4TextureRT(TextureRT const* texture);
    static std::shared_ptr<GEObject> Create(void* unused, GraphicsObject const* object);

    // Member access.
    inline TextureRT* GetTexture() const;

    // Returns true of mipmaps need to be generated.
    virtual bool CanAutoGenerateMipmaps() const override;
};

inline TextureRT* GL4TextureRT::GetTexture() const
{
    return static_cast<TextureRT*>(mGTObject);
}

}
