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

class GTE_IMPEXP HLSLShaderType
{
public:
    struct Description
    {
        D3D_SHADER_VARIABLE_CLASS varClass;
        D3D_SHADER_VARIABLE_TYPE varType;
        unsigned int numRows;
        unsigned int numColumns;
        unsigned int numElements;
        unsigned int numChildren;
        unsigned int offset;
        std::string typeName;
    };

    // Construction.
    HLSLShaderType();

    // Deferred construction for shader reflection.  These functions are
    // intended to be write-once.
    void SetDescription(D3D_SHADER_TYPE_DESC const& desc);
    void SetName(std::string const& name);

    // This is non-const and is intended to be used as part of the Set*
    // write-once system.  HLSLShaderFactory::{GetVariables,GetTypes} are
    // the clients and they ensure that i is a valid index.
    HLSLShaderType& GetChild(unsigned int i);

    // For use in construction of lookup tables for name-offset pairs.
    HLSLShaderType const& GetChild(unsigned int i) const;

    // Member access.
    std::string const& GetName() const;
    D3D_SHADER_VARIABLE_CLASS GetClass() const;
    D3D_SHADER_VARIABLE_TYPE GetType() const;
    unsigned int GetNumRows() const;
    unsigned int GetNumColumns() const;
    unsigned int GetNumElements() const;
    unsigned int GetNumChildren() const;
    unsigned int GetOffset() const;
    std::string const& GetTypeName() const;
    std::vector<HLSLShaderType> const& GetChildren() const;

    // Print to a text file for human readability.
    void Print(std::ofstream& output, int indent) const;

private:
    Description mDesc;
    std::string mName;
    std::vector<HLSLShaderType> mChildren;

    // Support for Print.
    static std::string const msVarClass[];
    static std::string const msVarType[];
};

}
