// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteRawBuffer.h>
#include <Graphics/DX11/GteDX11Buffer.h>

namespace gte
{

class GTE_IMPEXP DX11RawBuffer : public DX11Buffer
{
public:
    // Construction and destruction.
    virtual ~DX11RawBuffer();
    DX11RawBuffer(ID3D11Device* device, RawBuffer const* rbuffer);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

    // Member access.
    inline RawBuffer* GetRawBuffer() const;
    inline ID3D11ShaderResourceView* GetSRView() const;
    inline ID3D11UnorderedAccessView* GetUAView() const;

    // Support for the DX11 debug layer; see comments in the file
    // GteDX11GraphicsObject.h about usage.
    virtual void SetName(std::string const& name);

private:
    // Support for construction.
    void CreateSRView(ID3D11Device* device);
    void CreateUAView(ID3D11Device* device);

    ID3D11ShaderResourceView* mSRView;
    ID3D11UnorderedAccessView* mUAView;
};

inline RawBuffer* DX11RawBuffer::GetRawBuffer() const
{
    return static_cast<RawBuffer*>(mGTObject);
}

inline ID3D11ShaderResourceView* DX11RawBuffer::GetSRView() const
{
    return mSRView;
}

inline ID3D11UnorderedAccessView* DX11RawBuffer::GetUAView() const
{
    return mUAView;
}

}
