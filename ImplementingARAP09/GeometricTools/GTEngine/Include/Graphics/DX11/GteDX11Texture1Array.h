// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTexture1Array.h>
#include <Graphics/DX11/GteDX11TextureArray.h>

namespace gte
{

class GTE_IMPEXP DX11Texture1Array : public DX11TextureArray
{
public:
    // Construction.
    DX11Texture1Array(ID3D11Device* device, Texture1Array const* textureArray);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline Texture1Array* GetTextureArray() const;
    inline ID3D11Texture1D* GetDXTextureArray() const;

private:
    // Support for construction.
    void CreateStaging(ID3D11Device* device, D3D11_TEXTURE1D_DESC const& tx);
    void CreateSRView(ID3D11Device* device, D3D11_TEXTURE1D_DESC const& tx);
    void CreateUAView(ID3D11Device* device, D3D11_TEXTURE1D_DESC const& tx);
};

inline Texture1Array* DX11Texture1Array::GetTextureArray() const
{
    return static_cast<Texture1Array*>(mGTObject);
}

inline ID3D11Texture1D* DX11Texture1Array::GetDXTextureArray() const
{
    return static_cast<ID3D11Texture1D*>(mDXObject);
}

}
