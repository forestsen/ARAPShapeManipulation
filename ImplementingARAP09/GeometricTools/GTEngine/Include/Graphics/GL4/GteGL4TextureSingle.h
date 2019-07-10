// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTextureSingle.h>
#include <Graphics/GL4/GteGL4Texture.h>
#include <LowLevel/GteLogger.h>

namespace gte
{

class GTE_IMPEXP GL4TextureSingle : public GL4Texture
{
public:
    // Abstract base class, a shim to distinguish between single textures and
    // texture arrays.
    virtual ~GL4TextureSingle();

    // Member access.
    inline TextureSingle* GetTexture() const;

    virtual bool Update() override;
    virtual bool CopyCpuToGpu() override;
    virtual bool CopyGpuToCpu() override;

    bool Update(unsigned int level);
    bool CopyCpuToGpu(unsigned int level);
    bool CopyGpuToCpu(unsigned int level);
    void CopyGpuToGpu(GL4TextureSingle* texture, unsigned int level)
    {
        (void)texture;
        (void)level;
        LogError("Not yet implemented.");
    }

    // Returns true if mipmaps need to be generated.
    virtual bool CanAutoGenerateMipmaps() const = 0;

    // Generates mipmaps from level 0 -- only if CanAutoGenerateMipmaps() returns true.
    virtual bool GenerateMipmaps();

protected:
    // No public construction.  Derived classes use this constructor.
    GL4TextureSingle(TextureSingle const* gtTexture, GLenum target, GLenum targetBinding);

    // Only call from derived class constructor after texture storage has been allocated.
    void Initialize();

    // Called by Update and CopyCpuToGpu.
    bool DoCopyCpuToGpu(unsigned int level);

    // Should be called in constructor when CopyType is any value bu COPY_NONE.
    void CreateStaging();

    // This is called to copy the data from the CPU buffer to the GPU
    // for the specified level.  If a pixel unpack buffer is being used
    // then data needs to be passed as 0 which is used as an offset.
    virtual void LoadTextureLevel(unsigned int level, void const* data) = 0;

private:
    // Data associated with each mip level
    GLuint mLevelPixelUnpackBuffer[Texture::MAX_MIPMAP_LEVELS];
    GLuint mLevelPixelPackBuffer[Texture::MAX_MIPMAP_LEVELS];
};

inline TextureSingle* GL4TextureSingle::GetTexture() const
{
    return static_cast<TextureSingle*>(mGTObject);
}

}
