// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteShader.h>
#include <Graphics/GteVertexBuffer.h>
#include <Graphics/DX11/GteDX11Include.h>

namespace gte
{

class GTE_IMPEXP DX11InputLayout
{
public:
    // Construction and destruction.
    ~DX11InputLayout();
    DX11InputLayout(ID3D11Device* device, VertexBuffer const* vbuffer,
        Shader const* vshader);

    // Support for drawing geometric primitives.
    void Enable(ID3D11DeviceContext* context);
    void Disable(ID3D11DeviceContext* context);

    // Support for the DX11 debug layer; see comments in the file
    // GteDX11GraphicsObject.h about usage.
    HRESULT SetName(std::string const& name);
    inline std::string const& GetName() const;

private:
    ID3D11InputLayout* mLayout;
    int mNumElements;
    D3D11_INPUT_ELEMENT_DESC mElements[VA_MAX_ATTRIBUTES];
    std::string mName;

    // Conversions from GTEngine values to DX11 values.
    static char const* msSemantic[VA_NUM_SEMANTICS];
};

inline std::string const& DX11InputLayout::GetName() const
{
    return mName;
}

}
