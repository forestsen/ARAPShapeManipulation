// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/09/12)

#pragma once

#include <Graphics/DX11/GteHLSLByteAddressBuffer.h>
#include <Graphics/DX11/GteHLSLConstantBuffer.h>
#include <Graphics/DX11/GteHLSLParameter.h>
#include <Graphics/DX11/GteHLSLResourceBindInfo.h>
#include <Graphics/DX11/GteHLSLSamplerState.h>
#include <Graphics/DX11/GteHLSLStructuredBuffer.h>
#include <Graphics/DX11/GteHLSLTexture.h>
#include <Graphics/DX11/GteHLSLTextureArray.h>
#include <Graphics/DX11/GteHLSLTextureBuffer.h>
#include <fstream>

namespace gte
{

class GTE_IMPEXP HLSLShader
{
public:
    struct Description
    {
        struct InstructionCount
        {
            unsigned int numInstructions;
            unsigned int numTemporaryRegisters;
            unsigned int numTemporaryArrays;
            unsigned int numDefines;
            unsigned int numDeclarations;
            unsigned int numTextureNormal;
            unsigned int numTextureLoad;
            unsigned int numTextureComparison;
            unsigned int numTextureBias;
            unsigned int numTextureGradient;
            unsigned int numFloatArithmetic;
            unsigned int numSIntArithmetic;
            unsigned int numUIntArithmetic;
            unsigned int numStaticFlowControl;
            unsigned int numDynamicFlowControl;
            unsigned int numMacro;
            unsigned int numArray;
        };


        struct GSParameters
        {
            unsigned int numCutInstructions;
            unsigned int numEmitInstructions;
            D3D_PRIMITIVE inputPrimitive;
            D3D_PRIMITIVE_TOPOLOGY outputTopology;
            unsigned int maxOutputVertices;
        };

        struct TSParameters
        {
            unsigned int numPatchConstants;
            unsigned int numGSInstances;
            unsigned int numControlPoints;
            D3D_PRIMITIVE inputPrimitive;
            D3D_TESSELLATOR_OUTPUT_PRIMITIVE outputPrimitive;
            D3D_TESSELLATOR_PARTITIONING partitioning;
            D3D_TESSELLATOR_DOMAIN domain;
        };

        struct CSParameters
        {
            unsigned int numBarrierInstructions;
            unsigned int numInterlockedInstructions;
            unsigned int numTextureStoreInstructions;
        };

        std::string creator;
        D3D_SHADER_VERSION_TYPE shaderType;
        unsigned int majorVersion;
        unsigned int minorVersion;
        unsigned int flags;
        unsigned int numConstantBuffers;
        unsigned int numBoundResources;
        unsigned int numInputParameters;
        unsigned int numOutputParameters;
        InstructionCount instructions;
        GSParameters gs;
        TSParameters ts;
        CSParameters cs;
    };

    // Construction.
    HLSLShader();

    // Test whether the shader was constructed properly.  The function tests
    // solely whether the name, entry, and target are nonempty strings and
    // that the compiled code array is nonempty; this is the common case when
    // HLSLShaderFactory is used to create the shader.
    bool IsValid() const;

    // Deferred construction for shader reflection.  These functions are
    // intended to be write-once.
    void SetDescription(D3D_SHADER_DESC const& desc);
    void SetName(std::string const& name);
    void SetEntry(std::string const& entry);
    void SetTarget(std::string const& target);
    void InsertInput(HLSLParameter const& parameter);
    void InsertOutput(HLSLParameter const& parameter);
    void Insert(HLSLConstantBuffer const& cbuffer);
    void Insert(HLSLTextureBuffer const& tbuffer);
    void Insert(HLSLStructuredBuffer const& sbuffer);
    void Insert(HLSLByteAddressBuffer const& rbuffer);
    void Insert(HLSLTexture const& texture);
    void Insert(HLSLTextureArray const& textureArray);
    void Insert(HLSLSamplerState const& samplerState);
    void Insert(HLSLResourceBindInfo const& rbinfo);
    void SetCompiledCode(size_t numBytes, void const* buffer);

    // Member access.
    Description const& GetDescription() const;
    std::string const& GetName() const;
    std::string const& GetEntry() const;
    std::string const& GetTarget() const;
    int GetShaderTypeIndex() const;
    std::vector<HLSLParameter> const& GetInputs() const;
    std::vector<HLSLParameter> const& GetOutputs() const;
    std::vector<HLSLConstantBuffer> const& GetCBuffers() const;
    std::vector<HLSLTextureBuffer> const& GetTBuffers() const;
    std::vector<HLSLStructuredBuffer> const& GetSBuffers() const;
    std::vector<HLSLByteAddressBuffer> const& GetRBuffers() const;
    std::vector<HLSLTexture> const& GetTextures() const;
    std::vector<HLSLTextureArray> const& GetTextureArrays() const;
    std::vector<HLSLSamplerState> const& GetSamplerStates() const;
    std::vector<HLSLResourceBindInfo> const& GetResourceBindInfos() const;
    std::vector<unsigned char> const& GetCompiledCode() const;

    // Compute shaders only.
    void SetNumThreads(unsigned int numXThreads, unsigned int numYThreads,
        unsigned int numZThreads);
    unsigned int GetNumXThreads() const;
    unsigned int GetNumYThreads() const;
    unsigned int GetNumZThreads() const;

    // Print to a text file for human readability.
    void Print(std::ofstream& output) const;

private:
    Description mDesc;
    std::string mName;
    std::string mEntry;
    std::string mTarget;
    std::vector<HLSLParameter> mInputs;
    std::vector<HLSLParameter> mOutputs;
    std::vector<HLSLConstantBuffer> mCBuffers;
    std::vector<HLSLTextureBuffer> mTBuffers;
    std::vector<HLSLStructuredBuffer> mSBuffers;
    std::vector<HLSLByteAddressBuffer> mRBuffers;
    std::vector<HLSLTexture> mTextures;
    std::vector<HLSLTextureArray> mTextureArrays;
    std::vector<HLSLSamplerState> mSamplerStates;
    std::vector<HLSLResourceBindInfo> mRBInfos;
    std::vector<unsigned char> mCompiledCode;
    unsigned int mNumXThreads;
    unsigned int mNumYThreads;
    unsigned int mNumZThreads;

    // Support for Print.
    static std::string const msShaderType[];
    static std::string const msCompileFlags[];
    static std::string const msPrimitive[];
    static std::string const msPrimitiveTopology[];
    static std::string const msOutputPrimitive[];
    static std::string const msPartitioning[];
    static std::string const msDomain[];
};

}
