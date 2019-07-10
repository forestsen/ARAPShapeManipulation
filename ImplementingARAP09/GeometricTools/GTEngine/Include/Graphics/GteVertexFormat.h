// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2017/06/29)

#pragma once

#include <Graphics/GteDataFormat.h>

namespace gte
{

// Enumerations for DX11.
enum GTE_IMPEXP VASemantic
{
    VA_NO_SEMANTIC,
    VA_POSITION,
    VA_BLENDWEIGHT,
    VA_BLENDINDICES,
    VA_NORMAL,
    VA_PSIZE,
    VA_TEXCOORD,
    VA_TANGENT,
    VA_BINORMAL,
    VA_TESSFACTOR,
    VA_POSITIONT,
    VA_COLOR,
    VA_FOG,
    VA_DEPTH,
    VA_SAMPLE,
    VA_NUM_SEMANTICS
};

enum GTE_IMPEXP VAConstant
{
    // TODO:  Modify to the numbers for Shader Model 5 (DX11).

    // The maximum number of attributes for a vertex format.
    VA_MAX_ATTRIBUTES = 16,

    // The maximum number of texture coordinate units.
    VA_MAX_TCOORD_UNITS = 8,

    // The maximum number of color units.
    VA_MAX_COLOR_UNITS = 2
};

class GTE_IMPEXP VertexFormat
{
public:
    // Construction.
    VertexFormat();

    // Support for reusing a VertexFormat object within a scope.  This
    // call resets the object to the state produced by the default
    // constructor call.
    void Reset();

    // Create a packed vertex format, where all attributes are contiguous in
    // memory.  The order of the attributes is determined by the order of
    // Bind calls.
    bool Bind(VASemantic semantic, DFType type, unsigned int unit);

    // Member access.  GetAttribute returns 'true' when the input i is
    // such that 0 <= i < GetNumAttributes(), in which case the returned
    // semantic, type, unit, and offset are valid.
    unsigned int GetVertexSize() const;
    int GetNumAttributes() const;
    bool GetAttribute(int i, VASemantic& semantic, DFType& type,
        unsigned int& unit, unsigned int& offset) const;

    // Determine whether a semantic/unit exists.  If so, return the
    // index i that can be used to obtain more information about the
    // attribute by the functions after this.  If not, return -1.
    int GetIndex(VASemantic semantic, unsigned int unit) const;
    DFType GetType(int i) const;
    unsigned int GetOffset(int i) const;

private:
    class GTE_IMPEXP Attribute
    {
    public:
        Attribute();
        VASemantic semantic;
        DFType type;
        unsigned int unit;
        unsigned int offset;
    };

    int mNumAttributes;
    unsigned int mVertexSize;
    Attribute mAttributes[VA_MAX_ATTRIBUTES];
};

}
