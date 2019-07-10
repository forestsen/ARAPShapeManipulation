// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/09/12)

#pragma once

#if defined(GTE_USE_DX12)
#include <Graphics/DX12/GteDX12Include.h>

#define ID3DShaderReflection ID3D12ShaderReflection
#define IID_ID3DShaderReflection IID_ID3D12ShaderReflection
#define ID3DShaderReflectionConstantBuffer ID3D12ShaderReflectionConstantBuffer
#define ID3DShaderReflectionType ID3D12ShaderReflectionType
#define ID3DShaderReflectionVariable ID3D12ShaderReflectionVariable
#define D3D_SHADER_DESC D3D12_SHADER_DESC
#define D3D_SIGNATURE_PARAMETER_DESC D3D12_SIGNATURE_PARAMETER_DESC
#define D3D_SHADER_VERSION_TYPE D3D12_SHADER_VERSION_TYPE
#define D3D_SHVER_GET_TYPE D3D12_SHVER_GET_TYPE
#define D3D_SHVER_GET_MAJOR D3D12_SHVER_GET_MAJOR
#define D3D_SHVER_GET_MINOR D3D12_SHVER_GET_MINOR
#define D3D_SHADER_BUFFER_DESC D3D12_SHADER_BUFFER_DESC
#define D3D_SHADER_INPUT_BIND_DESC D3D12_SHADER_INPUT_BIND_DESC
#define D3D_SHADER_VARIABLE_DESC D3D12_SHADER_VARIABLE_DESC
#define D3D_SHADER_TYPE_DESC D3D12_SHADER_TYPE_DESC
#else
#include <Graphics/DX11/GteDX11Include.h>

#define ID3DShaderReflection ID3D11ShaderReflection
#define IID_ID3DShaderReflection IID_ID3D11ShaderReflection
#define ID3DShaderReflectionConstantBuffer ID3D11ShaderReflectionConstantBuffer
#define ID3DShaderReflectionType ID3D11ShaderReflectionType
#define ID3DShaderReflectionVariable ID3D11ShaderReflectionVariable
#define D3D_SHADER_DESC D3D11_SHADER_DESC
#define D3D_SIGNATURE_PARAMETER_DESC D3D11_SIGNATURE_PARAMETER_DESC
#define D3D_SHADER_VERSION_TYPE D3D11_SHADER_VERSION_TYPE
#define D3D_SHVER_GET_TYPE D3D11_SHVER_GET_TYPE
#define D3D_SHVER_GET_MAJOR D3D11_SHVER_GET_MAJOR
#define D3D_SHVER_GET_MINOR D3D11_SHVER_GET_MINOR
#define D3D_SHADER_BUFFER_DESC D3D11_SHADER_BUFFER_DESC
#define D3D_SHADER_INPUT_BIND_DESC D3D11_SHADER_INPUT_BIND_DESC
#define D3D_SHADER_VARIABLE_DESC D3D11_SHADER_VARIABLE_DESC
#define D3D_SHADER_TYPE_DESC D3D11_SHADER_TYPE_DESC
#endif

#include <fstream>

namespace gte
{

class GTE_IMPEXP HLSLResource
{
public:
    // Abstract base class, destructor.
    virtual ~HLSLResource();
protected:
    // Construction.
    HLSLResource(D3D_SHADER_INPUT_BIND_DESC const& desc,
        unsigned int numBytes);
    HLSLResource(D3D_SHADER_INPUT_BIND_DESC const& desc, unsigned int index,
        unsigned int numBytes);

public:
    struct Description
    {
        std::string name;
        D3D_SHADER_INPUT_TYPE type;
        unsigned int bindPoint;
        unsigned int bindCount;
        unsigned int flags;
        D3D_RESOURCE_RETURN_TYPE returnType;
        D3D_SRV_DIMENSION dimension;
        unsigned int numSamples;
    };

    // Member access.
    std::string const& GetName() const;
    D3D_SHADER_INPUT_TYPE GetType() const;
    unsigned int GetBindPoint() const;
    unsigned int GetBindCount() const;
    unsigned int GetFlags() const;
    D3D_RESOURCE_RETURN_TYPE GetReturnType() const;
    D3D_SRV_DIMENSION GetDimension() const;
    unsigned int GetNumSamples() const;
    unsigned int GetNumBytes() const;

    // Print to a text file for human readability.
    virtual void Print(std::ofstream& output) const;

private:
    Description mDesc;
    unsigned int mNumBytes;

    // Support for Print.
    static std::string const msSIType[];
    static std::string const msReturnType[];
    static std::string const msSRVDimension[];
};

}
