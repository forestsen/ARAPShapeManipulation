// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteConstantBuffer.h>
#include <Graphics/DX11/GteDX11Buffer.h>

namespace gte
{

class GTE_IMPEXP DX11ConstantBuffer : public DX11Buffer
{
public:
    // Construction.
    DX11ConstantBuffer(ID3D11Device* device, ConstantBuffer const* cbuffer);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline ConstantBuffer* GetConstantBuffer() const;
};

inline ConstantBuffer* DX11ConstantBuffer::GetConstantBuffer() const
{
    return static_cast<ConstantBuffer*>(mGTObject);
}

}
