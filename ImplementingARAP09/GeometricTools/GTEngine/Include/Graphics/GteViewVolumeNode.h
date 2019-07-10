// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteViewVolume.h>
#include <Graphics/GteNode.h>
#include <functional>

namespace gte
{

class GTE_IMPEXP ViewVolumeNode : public Node
{
public:
    // Construction.  The node's world translation is used as the view volume's
    // location.  The node's world rotation matrix is used for the view volume's
    // coordinate axes.  Column 0 of the world rotation matrix is the view volume's
    // direction vector, column 1 of the world rotation matrix is the view volume's
    // up vector, and column 2 of the world rotation matrix is the view volume's
    // right vector.
    //
    // On construction, the node's local transformation is set to the view volume's
    // coordinate system.
    //   local translation       = view volume location
    //   local rotation column 0 = view volume direction
    //   local rotation column 1 = view volume up
    //   local rotation column 2 = view volume right
    ViewVolumeNode(std::shared_ptr<ViewVolume> const& viewVolume = nullptr);

    // When you set the view volume, the node's local transformation is set to the
    // view volumes's current current coordinate system.  The node's world
    // transformation is computed, and the view volume's coordinate system is set
    // to use the node's world transformation.
    void SetViewVolume(std::shared_ptr<ViewVolume> const& viewVolume);
    inline std::shared_ptr<ViewVolume> const& GetViewVolume() const;

    // Additional semantics may be applied after UpdateWorldData updates the
    // view volume.
    inline void SetOnUpdate(std::function<void(ViewVolumeNode*)> const& onUpdate);
    inline std::function<void(ViewVolumeNode*)> const& GetOnUpdate() const;

protected:
    // Geometric updates.
    virtual void UpdateWorldData(double applicationTime);

    std::shared_ptr<ViewVolume> mViewVolume;
    std::function<void(ViewVolumeNode*)> mOnUpdate;
};

inline std::shared_ptr<ViewVolume> const& ViewVolumeNode::GetViewVolume() const
{
    return mViewVolume;
}

inline void ViewVolumeNode::SetOnUpdate(std::function<void(ViewVolumeNode*)> const& onUpdate)
{
    mOnUpdate = onUpdate;
}

inline std::function<void(ViewVolumeNode*)> const& ViewVolumeNode::GetOnUpdate() const
{
    return mOnUpdate;
}

}
