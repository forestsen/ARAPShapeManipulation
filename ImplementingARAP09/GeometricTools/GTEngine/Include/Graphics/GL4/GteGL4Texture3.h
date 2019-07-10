// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTexture3.h>
#include <Graphics/GL4/GteGL4TextureSingle.h>

namespace gte
{

class GTE_IMPEXP GL4Texture3 : public GL4TextureSingle
{
public:
    // Construction and destruction.
    virtual ~GL4Texture3();
    GL4Texture3(Texture3 const* texture);
    static std::shared_ptr<GEObject> Create(void* unused, GraphicsObject const* object);

    // Member access.
    inline Texture3* GetTexture() const;

    // Returns true if mipmaps need to be generated.
    virtual bool CanAutoGenerateMipmaps() const override;

protected:
    virtual void LoadTextureLevel(unsigned int level, void const* data) override;
};

inline Texture3* GL4Texture3::GetTexture() const
{
    return static_cast<Texture3*>(mGTObject);
}

}
