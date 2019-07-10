// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteDrawingState.h>
#include <Graphics/GL4/GteGL4GraphicsObject.h>

namespace gte
{

class GTE_IMPEXP GL4DrawingState : public GL4GraphicsObject
{
protected:
    // Abstract base class.
    GL4DrawingState(DrawingState const* gtState);
};

}
