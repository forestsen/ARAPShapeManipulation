// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <GTEngineDEF.h>
#include <string>
#include <vector>

namespace gte
{

// Support for generation of lookup tables for constant buffers and texture
// buffers.  Given the name of a member of a buffer, get the offset into the
// buffer memory where the member lives.  The layout is specific to the
// shading language (HLSL, GLSL).
struct GTE_IMPEXP MemberLayout
{
    std::string name;
    unsigned int offset;
    unsigned int numElements;
};

typedef std::vector<MemberLayout> BufferLayout;

}
