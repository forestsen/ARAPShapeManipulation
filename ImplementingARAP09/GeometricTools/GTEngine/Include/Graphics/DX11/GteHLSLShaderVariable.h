// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/09/12)

#pragma once

#include <Graphics/DX11/GteHLSLResource.h>
#include <fstream>
#include <vector>

namespace gte
{
class GTE_IMPEXP HLSLShaderVariable
{
public:
    struct Description
    {
        std::string name;
        unsigned int offset;
        unsigned int numBytes;
        unsigned int flags;
        unsigned int textureStart;
        unsigned int textureNumSlots;
        unsigned int samplerStart;
        unsigned int samplerNumSlots;
        std::vector<unsigned char> defaultValue;
    };

    // Construction.  Shader variables are reported for constant buffers,
    // texture buffers, and structs defined in the shaders (resource
    // binding information).
    HLSLShaderVariable();

    // Deferred construction for shader reflection.  This function is
    // intended to be write-once.
    void SetDescription(D3D_SHADER_VARIABLE_DESC const& desc);

    // Member access.
    std::string const& GetName() const;
    unsigned int GetOffset() const;
    unsigned int GetNumBytes() const;
    unsigned int GetFlags() const;
    unsigned int GetTextureStart() const;
    unsigned int GetTextureNumSlots() const;
    unsigned int GetSamplerStart() const;
    unsigned int GetSamplerNumSlots() const;
    std::vector<unsigned char> const& GetDefaultValue() const;

    // Print to a text file for human readability.
    void Print(std::ofstream& output) const;

private:
    Description mDesc;
};

}
