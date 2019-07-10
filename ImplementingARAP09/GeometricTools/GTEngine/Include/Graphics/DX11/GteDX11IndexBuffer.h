// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteIndexBuffer.h>
#include <Graphics/DX11/GteDX11Buffer.h>

namespace gte
{

class GTE_IMPEXP DX11IndexBuffer : public DX11Buffer
{
public:
    // Construction.
    DX11IndexBuffer(ID3D11Device* device, IndexBuffer const* vbuffer);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline IndexBuffer* GetIndexBuffer() const;

    // Drawing support.
    void Enable(ID3D11DeviceContext* context);
    void Disable(ID3D11DeviceContext* context);

private:
    DXGI_FORMAT mFormat;
};

inline IndexBuffer* DX11IndexBuffer::GetIndexBuffer() const
{
    return static_cast<IndexBuffer*>(mGTObject);
}

}
