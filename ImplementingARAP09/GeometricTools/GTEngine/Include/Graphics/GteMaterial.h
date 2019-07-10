// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Mathematics/GteVector4.h>

namespace gte
{

class GTE_IMPEXP Material
{
public:
    // Construction.
    Material();

    // (r,g,b,*): default (0,0,0,1)
    Vector4<float> emissive;

    // (r,g,b,*): default (0,0,0,1)
    Vector4<float> ambient;

    // (r,g,b,a): default (0,0,0,1)
    Vector4<float> diffuse;

    // (r,g,b,specularPower): default (0,0,0,1)
    Vector4<float> specular;
};

}
