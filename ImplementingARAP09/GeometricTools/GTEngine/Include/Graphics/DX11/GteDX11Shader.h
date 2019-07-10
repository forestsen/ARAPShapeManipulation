// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteShader.h>
#include <Graphics/DX11/GteDX11GraphicsObject.h>

namespace gte
{

// This class provides virtual functions for generic access to DX11 shader
// functions that have embedded in their names "VS", "GS", "PS", "CS",
// "DS", and "HS".  The prefix "XS" is generic, where X in {V,G,P,C,D,H}.

class GTE_IMPEXP DX11Shader : public DX11GraphicsObject
{
public:
    // Calls to ID3D11DeviceContext::XSSetShader.
    virtual void Enable(ID3D11DeviceContext* context) = 0;
    virtual void Disable(ID3D11DeviceContext* context) = 0;

    // Calls to ID3D11DeviceContext::XSSetConstantBuffers.
    virtual void EnableCBuffer(ID3D11DeviceContext* context,
        unsigned int bindPoint, ID3D11Buffer* buffer) = 0;
    virtual void DisableCBuffer(ID3D11DeviceContext* context,
        unsigned int bindPoint) = 0;

    // Calls to ID3D11DeviceContext::XSSetShaderResources.
    virtual void EnableSRView(ID3D11DeviceContext* context,
        unsigned int bindPoint, ID3D11ShaderResourceView* srView) = 0;
    virtual void DisableSRView(ID3D11DeviceContext* context,
        unsigned int bindPoint) = 0;

    // Calls to ID3D11DeviceContext::XSSetUnorderedAccessViews.
    virtual void EnableUAView(ID3D11DeviceContext* context,
        unsigned int bindPoint, ID3D11UnorderedAccessView* uaView,
        unsigned int initialCount) = 0;
    virtual void DisableUAView(ID3D11DeviceContext* context,
        unsigned int bindPoint) = 0;

    // Calls to ID3D11DeviceContext::XSSetSamplers.
    virtual void EnableSampler(ID3D11DeviceContext* context,
        unsigned int bindPoint, ID3D11SamplerState* state) = 0;
    virtual void DisableSampler(ID3D11DeviceContext* context,
        unsigned int bindPoint) = 0;

protected:
    // Abstract base class.
    DX11Shader(Shader const* shader);
};

}
