// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteDrawingState.h>

namespace gte
{

class GTE_IMPEXP RasterizerState : public DrawingState
{
public:
    enum GTE_IMPEXP FillMode
    {
        FILL_SOLID,
        FILL_WIREFRAME
    };

    enum GTE_IMPEXP CullMode
    {
        CULL_NONE,
        CULL_FRONT,
        CULL_BACK
    };

    // Construction.
    RasterizerState();

    // Member access.  The members are intended to be write-once before
    // you create an associated graphics state.
    FillMode fillMode;              // default: FILL_SOLID
    CullMode cullMode;              // default: CULL_BACK
    bool frontCCW;                  // default: true
    int depthBias;                  // default: 0
    float depthBiasClamp;           // default: 0
    float slopeScaledDepthBias;     // default: 0
    bool enableDepthClip;           // default: true
    bool enableScissor;             // default: false
    bool enableMultisample;         // default: false
    bool enableAntialiasedLine;     // default: false
};

}
