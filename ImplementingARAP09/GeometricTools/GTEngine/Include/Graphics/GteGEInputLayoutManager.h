// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <GTEngineDEF.h>

namespace gte
{

class Shader;
class VertexBuffer;

class GTE_IMPEXP GEInputLayoutManager
{
public:
    // Abstract base interface.
    virtual ~GEInputLayoutManager() {}
    GEInputLayoutManager() {}

    virtual bool Unbind(VertexBuffer const* vbuffer) = 0;
    virtual bool Unbind(Shader const* vshader) = 0;
    virtual void UnbindAll() = 0;
    virtual bool HasElements() const = 0;
};

}
