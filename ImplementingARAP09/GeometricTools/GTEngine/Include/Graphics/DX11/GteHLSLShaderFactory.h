// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/09/12)

#pragma once

#include <Graphics/GteProgramDefines.h>
#include <Graphics/DX11/GteHLSLShader.h>

namespace gte
{

class GTE_IMPEXP HLSLShaderFactory
{
public:
    // Create a shader from an HLSL program in a file.
    static HLSLShader CreateFromFile(
        std::string const& filename,
        std::string const& entry,
        std::string const& target,
        ProgramDefines const& defines,
        unsigned int compileFlags);

    // Create a shader from an HLSL represented as a string.
    static HLSLShader CreateFromString(
        std::string const& name,
        std::string const& source,
        std::string const& entry,
        std::string const& target,
        ProgramDefines const& defines,
        unsigned int compileFlags);

    // Create a shader from an HLSL bytecode blob.
    static HLSLShader CreateFromBytecode(
        std::string const& name,
        std::string const& entry,
        std::string const& target,
        size_t numBytes,
        unsigned char const* bytecode);

private:
    // Common code for CreateFromFile and CreateFromString.
    static HLSLShader CompileAndReflect(
        std::string const& name,
        std::string const& source,
        std::string const& entry,
        std::string const& target,
        ProgramDefines const& defines,
        unsigned int compileFlags);

    // Wrapper for the D3DCompile call.
    static ID3DBlob* CompileShader(
        std::string const& name,
        std::string const& source,
        std::string const& entry,
        std::string const& target,
        unsigned int compileFlags,
        ProgramDefines const& defines);

    // Support for shader reflection to obtain information about the HLSL
    // program.
    static bool ReflectShader(
        std::string const& name,
        std::string const& entry,
        std::string const& target,
        ID3DBlob* compiledCode,
        HLSLShader& shader);

    static bool GetDescription(ID3DShaderReflection* reflector,  HLSLShader& shader);
    static bool GetInputs(ID3DShaderReflection* reflector,  HLSLShader& shader);
    static bool GetOutputs(ID3DShaderReflection* reflector, HLSLShader& shader);
    static bool GetCBuffers(ID3DShaderReflection* reflector, HLSLShader& shader);
    static bool GetBoundResources(ID3DShaderReflection* reflector, HLSLShader& shader);

    static bool GetVariables(ID3DShaderReflectionConstantBuffer* cbuffer,
        unsigned int numVariables,  std::vector<HLSLBaseBuffer::Member>& members);

    static bool GetTypes(ID3DShaderReflectionType* rtype,
        unsigned int numMembers, HLSLShaderType& stype);

    static bool IsTextureArray(D3D_SRV_DIMENSION dim);

    // Support for logging warnings and errors to a file.
    static void WriteLog(std::string const& message);
};

}
