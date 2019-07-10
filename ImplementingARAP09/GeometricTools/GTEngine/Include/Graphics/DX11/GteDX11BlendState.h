// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteBlendState.h>
#include <Graphics/DX11/GteDX11DrawingState.h>

namespace gte
{

class GTE_IMPEXP DX11BlendState : public DX11DrawingState
{
public:
    // Construction.
    DX11BlendState(ID3D11Device* device, BlendState const* blendState);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline BlendState* GetBlendState();
    inline ID3D11BlendState* GetDXBlendState();

    // Enable the blend state.
    void Enable(ID3D11DeviceContext* context);

private:
    // Conversions from GTEngine values to DX11 values.
    static D3D11_BLEND const msMode[];
    static D3D11_BLEND_OP const msOperation[];
};

inline BlendState* DX11BlendState::GetBlendState()
{
    return static_cast<BlendState*>(mGTObject);
}

inline ID3D11BlendState* DX11BlendState::GetDXBlendState()
{
    return static_cast<ID3D11BlendState*>(mDXObject);
}

}
