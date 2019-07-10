// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

// <windows.h> is referenced by the DX11 headers.  Turn off the min and max
// macros to avoid conflicts with std::min and std::max.
#define NOMINMAX
#include <D3D11.h>
#include <D3Dcompiler.h>
#include <DXGI.h>
#include <LowLevel/GteLogger.h>

// Required libraries for linking DX11.0 with GTE:
//   d3d11.lib          (for DX11.0 core)
//   d3dcompiler.lib    (for D3DCompile and D3DReflect)
//   dxgi.lib           (for IDXGIAdapter1 and IDXGIOutput)
//   dxguid.lib         (for IID_ID3D11ShaderReflection)

// Convenient for reference counting.
namespace gte
{


template <typename T>
inline ULONG SafeRelease(T*& object)
{
    if (object)
    {
        ULONG refs = object->Release();
        object = nullptr;
        return refs;
    }
    return 0;
}

template <typename T>
inline ULONG FinalRelease(T*& object)
{
    if (object)
    {
        ULONG refs = object->Release();
        object = nullptr;
        if (refs > 0)
        {
            LogError("Reference count is not zero after release.");
            return refs;
        }
    }
    return 0;
}

class InterfaceReleaser
{
public:
    InterfaceReleaser(IUnknown* object)
        :
        mObject(object)
    {
    }

    ~InterfaceReleaser()
    {
        if (mObject)
        {
            mObject->Release();
        }
    }

private:
    IUnknown* mObject;
};

inline HRESULT SetPrivateName(ID3D11DeviceChild* object,
    std::string const& name)
{
    HRESULT hr;
    if (object && name != "")
    {
        hr = object->SetPrivateData(WKPDID_D3DDebugObjectName,
            static_cast<UINT>(name.length()), name.c_str());
    }
    else
    {
        // Callers are allowed to call this function with a null input
        // or with an empty name (for convenience).
        hr = S_OK;
    }
    return hr;
}

inline HRESULT SetPrivateName(IDXGIObject* object, std::string const& name)
{
    HRESULT hr;
    if (object && name != "")
    {
        hr = object->SetPrivateData(WKPDID_D3DDebugObjectName,
            static_cast<UINT>(name.length()), name.c_str());
    }
    else
    {
        // Callers are allowed to call this function with a null input
        // or with an empty name (for convenience).
        hr = S_OK;
    }
    return hr;
}


}

#define CHECK_HR_RETURN_NONE(msg)\
if (FAILED(hr))\
{ \
    LogError(std::string(msg) + ", hr = " + std::to_string(hr) + "."); \
}

#define CHECK_HR_RETURN_VOID(msg)\
if (FAILED(hr))\
{ \
    LogError(std::string(msg) + ", hr = " + std::to_string(hr) + "."); \
    return; \
}

#define CHECK_HR_RETURN(msg, value)\
if (FAILED(hr))\
{ \
    LogError(std::string(msg) + ", hr = " + std::to_string(hr) + "."); \
    return value; \
}

// Fake enumerations to have human-readable names that D3D11 did not provide.

// D3D11_BIND_FLAG
#define D3D11_BIND_NONE 0

// D3D11_RESOURCE_MISC_FLAG
#define D3D11_RESOURCE_MISC_NONE 0

// D3D11_BUFFER_UAV_FLAG
#define D3D11_BUFFER_UAV_FLAG_BASIC 0

// D3D11_CPU_ACCESS_FLAG
#define D3D11_CPU_ACCESS_NONE 0
#define D3D11_CPU_ACCESS_READ_WRITE (D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE)

// D3D11_QUERY_MISC_FLAG
#define D3D11_QUERY_MISC_NONE 0
