// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteGEDrawTarget.h>
#include <Graphics/DX11/GteDX11TextureDS.h>
#include <Graphics/DX11/GteDX11TextureRT.h>

namespace gte
{

class GTE_IMPEXP DX11DrawTarget : public GEDrawTarget
{
public:
    // Construction.
    DX11DrawTarget(DrawTarget const* target,
        std::vector<DX11TextureRT*>& rtTextures, DX11TextureDS* dsTexture);
    static std::shared_ptr<GEDrawTarget> Create(DrawTarget const* target,
        std::vector<GEObject*>& rtTextures, GEObject* dsTexture);

    // Member access.
    inline DX11TextureRT* GetRTTexture(unsigned int i) const;
    inline DX11TextureDS* GetDSTexture() const;

    // Used in the Renderer::Draw function.
    void Enable(ID3D11DeviceContext* context);
    void Disable(ID3D11DeviceContext* context);

private:
    std::vector<DX11TextureRT*> mRTTextures;
    DX11TextureDS* mDSTexture;

    // Convenient storage for enable/disable of targets.
    std::vector<ID3D11RenderTargetView*> mRTViews;
    ID3D11DepthStencilView* mDSView;

    // Temporary storage during enable/disable of targets.
    D3D11_VIEWPORT mSaveViewport;
    std::vector<ID3D11RenderTargetView*> mSaveRTViews;
    ID3D11DepthStencilView* mSaveDSView;
};

inline DX11TextureRT* DX11DrawTarget::GetRTTexture(unsigned int i) const
{
    return mRTTextures[i];
}

inline DX11TextureDS* DX11DrawTarget::GetDSTexture() const
{
    return mDSTexture;
}

}
