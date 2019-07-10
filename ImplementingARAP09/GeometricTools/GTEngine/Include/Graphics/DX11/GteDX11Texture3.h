// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTexture3.h>
#include <Graphics/DX11/GteDX11TextureSingle.h>

namespace gte
{

class GTE_IMPEXP DX11Texture3 : public DX11TextureSingle
{
public:
    // Construction.
    DX11Texture3(ID3D11Device* device, Texture3 const* texture);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline Texture3* GetTexture() const;
    inline ID3D11Texture3D* GetDXTexture() const;

private:
    // Support for construction.
    void CreateStaging(ID3D11Device* device, D3D11_TEXTURE3D_DESC const& tx);
    void CreateSRView(ID3D11Device* device, D3D11_TEXTURE3D_DESC const& tx);
    void CreateUAView(ID3D11Device* device, D3D11_TEXTURE3D_DESC const& tx);
};

inline Texture3* DX11Texture3::GetTexture() const
{
    return static_cast<Texture3*>(mGTObject);
}

inline ID3D11Texture3D* DX11Texture3::GetDXTexture() const
{
    return static_cast<ID3D11Texture3D*>(mDXObject);
}

}
