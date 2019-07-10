// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteStructuredBuffer.h>
#include <Graphics/DX11/GteDX11Buffer.h>

namespace gte
{

class GTE_IMPEXP DX11StructuredBuffer : public DX11Buffer
{
public:
    // Construction and destruction.
    virtual ~DX11StructuredBuffer();
    DX11StructuredBuffer(ID3D11Device* device, StructuredBuffer const* sbuffer);
    static std::shared_ptr<GEObject> Create(void* device, GraphicsObject const* object);

public:
    // Member access.
    inline StructuredBuffer* GetStructuredBuffer() const;
    inline ID3D11ShaderResourceView* GetSRView() const;
    inline ID3D11UnorderedAccessView* GetUAView() const;
    inline ID3D11Buffer* GetCounterStagingBuffer() const;

    // Copy of data between CPU and GPU.
    virtual bool CopyGpuToCpu(ID3D11DeviceContext* context);

    // The number of active elements is read from GPU and stored in the
    // StructuredBuffer object  (of type CT_APPEND_CONSUME or CT_COUNTER).
    // The result can be accessed from this object via its member function
    // GetNumActiveElements().
    bool GetNumActiveElements(ID3D11DeviceContext* context);

    // Support for the DX11 debug layer; see comments in the file
    // GteDX11GraphicsObject.h about usage.
    virtual void SetName(std::string const& name);

private:
    // Support for construction.
    void CreateSRView(ID3D11Device* device);
    void CreateUAView(ID3D11Device* device);
    void CreateCounterStaging(ID3D11Device* device);

    ID3D11ShaderResourceView* mSRView;
    ID3D11UnorderedAccessView* mUAView;
    ID3D11Buffer* mCounterStaging;

    // Mapping from StructuredBuffer::CounterType to D3D11_BUFFER_UAV_FLAG.
    static unsigned int const msUAVFlag[];
};

inline StructuredBuffer* DX11StructuredBuffer::GetStructuredBuffer() const
{
    return static_cast<StructuredBuffer*>(mGTObject);
}

inline ID3D11ShaderResourceView* DX11StructuredBuffer::GetSRView() const
{
    return mSRView;
}

inline ID3D11UnorderedAccessView* DX11StructuredBuffer::GetUAView() const
{
    return mUAView;
}

inline ID3D11Buffer* DX11StructuredBuffer::GetCounterStagingBuffer() const
{
    return mCounterStaging;
}

}
