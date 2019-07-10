// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteBuffer.h>

namespace gte
{

class GTE_IMPEXP RawBuffer : public Buffer
{
public:
    // Construction.  The element size is always 4 bytes.
    RawBuffer(unsigned int numElements, bool createStorage = true);

public:
    // For use by the Shader class for storing reflection information.
    static int const shaderDataLookup = 3;
};

}
