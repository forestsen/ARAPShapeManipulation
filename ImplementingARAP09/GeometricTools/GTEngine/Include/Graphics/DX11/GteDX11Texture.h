// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTexture.h>
#include <Graphics/DX11/GteDX11Resource.h>

namespace gte
{

class GTE_IMPEXP DX11Texture : public DX11Resource
{
public:
    // Abstract base class.
    virtual ~DX11Texture();
protected:
    // No public construction.  Derived classes use this constructor.
    DX11Texture(Texture const* gtTexture);

public:
    // Member access.
    inline Texture* GetTexture() const;
    inline ID3D11ShaderResourceView* GetSRView() const;
    inline ID3D11UnorderedAccessView* GetUAView() const;

    // Copy of data between CPU and GPU.
    virtual bool Update(ID3D11DeviceContext* context, unsigned int sri) override;
    virtual bool Update(ID3D11DeviceContext* context) override;
    virtual bool CopyCpuToGpu(ID3D11DeviceContext* context, unsigned int sri) override;
    virtual bool CopyCpuToGpu(ID3D11DeviceContext* context) override;
    virtual bool CopyGpuToCpu(ID3D11DeviceContext* context, unsigned int sri) override;
    virtual bool CopyGpuToCpu(ID3D11DeviceContext* context) override;
    virtual void CopyGpuToGpu(ID3D11DeviceContext* context,
        ID3D11Resource* target, unsigned int sri) override;
    virtual void CopyGpuToGpu(ID3D11DeviceContext* context,
        ID3D11Resource* target) override;

    // Support for the DX11 debug layer; see comments in the file
    // GteDX11GraphicsObject.h about usage.
    virtual void SetName(std::string const& name) override;

protected:
    // Support for copy of row-pitched and slice-pitched (noncontiguous)
    // texture memory.
    static void CopyPitched2(unsigned int numRows, unsigned int srcRowPitch,
        void const* srcData, unsigned int trgRowPitch, void* trgData);

    static void CopyPitched3(unsigned int numRows, unsigned int numSlices,
        unsigned int srcRowPitch, unsigned int srcSlicePitch,
        void const* srcData, unsigned int trgRowPitch,
        unsigned int trgSlicePitch, void* trgData);

    ID3D11ShaderResourceView* mSRView;
    ID3D11UnorderedAccessView* mUAView;
};

inline Texture* DX11Texture::GetTexture() const
{
    return static_cast<Texture*>(mGTObject);
}

inline ID3D11ShaderResourceView* DX11Texture::GetSRView() const
{
    return mSRView;
}

inline ID3D11UnorderedAccessView* DX11Texture::GetUAView() const
{
    return mUAView;
}

}
