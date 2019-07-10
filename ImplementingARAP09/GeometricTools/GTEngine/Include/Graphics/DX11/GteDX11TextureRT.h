// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTextureRT.h>
#include <Graphics/DX11/GteDX11Texture2.h>

namespace gte
{

class GTE_IMPEXP DX11TextureRT : public DX11Texture2
{
public:
    // Construction and destruction.
    virtual ~DX11TextureRT();
    DX11TextureRT(ID3D11Device* device, TextureRT const* texture);
    DX11TextureRT(ID3D11Device* device, DX11TextureRT const* dxSharedTexture);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline ID3D11RenderTargetView* GetRTView() const;

    // Support for the DX11 debug layer; see comments in the file
    // GteDX11GraphicsObject.h about usage.
    virtual void SetName(std::string const& name);

private:
    // Support for construction.
    void CreateRTView(ID3D11Device* device, D3D11_TEXTURE2D_DESC const& tx);

    ID3D11RenderTargetView* mRTView;
};

inline ID3D11RenderTargetView* DX11TextureRT::GetRTView() const
{
    return mRTView;
}

}
