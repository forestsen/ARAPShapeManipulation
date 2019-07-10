// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteDepthStencilState.h>
#include <Graphics/DX11/GteDX11DrawingState.h>

namespace gte
{

class GTE_IMPEXP DX11DepthStencilState : public DX11DrawingState
{
public:
    // Construction.
    DX11DepthStencilState(ID3D11Device* device, DepthStencilState const* depthStencilState);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline DepthStencilState* GetDepthStencilState();
    inline ID3D11DepthStencilState* GetDXDepthStencilState();

    // Enable the depth-stencil state.
    void Enable(ID3D11DeviceContext* context);

private:
    // Conversions from GTEngine values to DX11 values.
    static D3D11_DEPTH_WRITE_MASK const msWriteMask[];
    static D3D11_COMPARISON_FUNC const msComparison[];
    static D3D11_STENCIL_OP const msOperation[];
};

inline DepthStencilState* DX11DepthStencilState::GetDepthStencilState()
{
    return static_cast<DepthStencilState*>(mGTObject);
}

inline ID3D11DepthStencilState* DX11DepthStencilState::GetDXDepthStencilState()
{
    return static_cast<ID3D11DepthStencilState*>(mDXObject);
}

}
