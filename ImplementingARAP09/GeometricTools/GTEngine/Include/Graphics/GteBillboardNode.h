// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteNode.h>

namespace gte
{

class GTE_IMPEXP BillboardNode : public Node
{
public:
    // The model space of the billboard has an up vector of (0,1,0) that is
    // chosen to be the billboard's axis of rotation.

    // Construction.
    BillboardNode(std::shared_ptr<Camera> const& camera);

    // The camera to which the billboard is aligned.
    inline void AlignTo(std::shared_ptr<Camera> const& camera);

protected:
    // Support for the geometric update.
    virtual void UpdateWorldData(double applicationTime);

    std::shared_ptr<Camera> mCamera;
};


inline void BillboardNode::AlignTo(std::shared_ptr<Camera> const& camera)
{
    mCamera = camera;
}


}
