// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/11/13)

#pragma once

#include <Graphics/GteTextureDS.h>
#include <Graphics/DX11/GteDX11Texture2.h>

namespace gte
{

class GTE_IMPEXP DX11TextureDS : public DX11Texture2
{
public:
    // Construction and destruction.
    virtual ~DX11TextureDS();
    DX11TextureDS(ID3D11Device* device, TextureDS const* texture);
    DX11TextureDS(ID3D11Device* device, DX11TextureDS const* dxSharedTexture);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline ID3D11DepthStencilView* GetDSView() const;

    // Support for the DX11 debug layer; see comments in the file
    // GteDX11GraphicsObject.h about usage.
    virtual void SetName(std::string const& name);

private:
    // Support for construction.
    void CreateDSView(ID3D11Device* device);
    void CreateDSSRView(ID3D11Device* device);
    DXGI_FORMAT GetDepthResourceFormat(DXGI_FORMAT depthFormat);
    DXGI_FORMAT GetDepthSRVFormat(DXGI_FORMAT depthFormat);

    ID3D11DepthStencilView* mDSView;
};

inline ID3D11DepthStencilView* DX11TextureDS::GetDSView() const
{
    return mDSView;
}

}
