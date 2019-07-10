// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteRasterizerState.h>
#include <Graphics/DX11/GteDX11DrawingState.h>

namespace gte
{

class GTE_IMPEXP DX11RasterizerState : public DX11DrawingState
{
public:
    // Construction.
    DX11RasterizerState(ID3D11Device* device, RasterizerState const* rasterizerState);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline RasterizerState* GetRasterizerState();
    inline ID3D11RasterizerState* GetDXRasterizerState();

    // Enable the rasterizer state.
    void Enable(ID3D11DeviceContext* context);

private:
    // Conversions from GTEngine values to DX11 values.
    static D3D11_FILL_MODE const msFillMode[];
    static D3D11_CULL_MODE const msCullMode[];
};

inline RasterizerState* DX11RasterizerState::GetRasterizerState()
{
    return static_cast<RasterizerState*>(mGTObject);
}

inline ID3D11RasterizerState* DX11RasterizerState::GetDXRasterizerState()
{
    return static_cast<ID3D11RasterizerState*>(mDXObject);
}

}
