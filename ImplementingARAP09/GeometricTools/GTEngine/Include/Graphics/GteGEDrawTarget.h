// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteDrawTarget.h>

namespace gte
{

class GTE_IMPEXP GEDrawTarget
{
public:
    // Abstract base class.
    virtual ~GEDrawTarget();
protected:
    GEDrawTarget(DrawTarget const* gtTarget);

public:
    // Member access.
    inline DrawTarget* GetDrawTarget() const;

protected:
    DrawTarget* mTarget;
};

inline DrawTarget* GEDrawTarget::GetDrawTarget() const
{
    return mTarget;
}

}
