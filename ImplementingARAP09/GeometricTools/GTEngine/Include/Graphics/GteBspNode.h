// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteNode.h>
#include <Mathematics/GteHyperplane.h>

// Binary Separating Plane (BSP) nodes.  The "positive" side of a plane is the
// half-space to which the plane normal points.  The "negative" side of a
// a plane is the complementary half-space.

namespace gte
{

class GTE_IMPEXP BspNode : public Node
{
public:
    // Construction.  The base class Node has three children and is not
    // allowed to grow.  The first and last children (indices 0 and 2) are the
    // positive and negative children of the binary tree.  The positive child
    // corresponds to the positive side of the separating plane.  The negative
    // child corresponds to the negative side of the separating plane.  The
    // middle child slot is where additional geometry may be attached such as
    // the triangles that are coplanar with the separating plane.
    BspNode();
    BspNode(Plane3<float> const& modelPlane);

    // These methods should be used instead of the attach/detach methods in
    // the Node base class.
    inline std::shared_ptr<Spatial> AttachPositiveChild(
        std::shared_ptr<Spatial> const& child);

    inline std::shared_ptr<Spatial> AttachCoplanarChild(
        std::shared_ptr<Spatial> const& child);

    inline std::shared_ptr<Spatial> AttachNegativeChild(
        std::shared_ptr<Spatial> const& child);

    inline std::shared_ptr<Spatial> DetachPositiveChild();
    inline std::shared_ptr<Spatial> DetachCoplanarChild();
    inline std::shared_ptr<Spatial> DetachNegativeChild();
    inline std::shared_ptr<Spatial> GetPositiveChild();
    inline std::shared_ptr<Spatial> GetCoplanarChild();
    inline std::shared_ptr<Spatial> GetNegativeChild();

    // Member access.
    void SetModelPlane(Plane3<float> const& plane);
    Plane3<float> GetModelPlane() const;
    Plane3<float> GetWorldPlane() const;

    // Determine the portion of the scene that contains the point.
    Spatial* GetContainingNode(Vector4<float> const& point);

protected:
    // Support for conversions from planes to 4-tuples.
    void NormalizePlane(Vector4<float>& plane);
    void SetWorldPlane(Plane3<float> const& plane);

    // Support for the geometric update.
    virtual void UpdateWorldData(double applicationTime);

    // Support for hierarchical culling.
    virtual void GetVisibleSet(Culler& culler,
        std::shared_ptr<Camera> const& camera, bool noCull);

    // Determine whether the point is fully on one side of the world plane.
    // The function returns +1 if the point is on the positive side of the
    // plane, -1 if the point is on the negative side of the plane, or 0 if
    // the point is on the plane.
    int WhichSide(Vector4<float> const& point) const;

    // Determine whether the view frustum is fully on one side of the world
    // plane.  The function returns +1 if the view frustum is fully on the
    // positive side of the plane, -1 if the view frustum is fully on the
    // negative side of the plane, or 0 if the view frustum straddles the
    // plane.  The world camera coordinate system is used for the test.
    int WhichSide(std::shared_ptr<Camera> const& camera) const;

    Vector4<float> mModelPlane, mWorldPlane;
};


inline std::shared_ptr<Spatial> BspNode::AttachPositiveChild(
    std::shared_ptr<Spatial> const& child)
{
    return SetChild(0, child);
}

inline std::shared_ptr<Spatial> BspNode::AttachCoplanarChild(
    std::shared_ptr<Spatial> const& child)
{
    return SetChild(1, child);
}

inline std::shared_ptr<Spatial> BspNode::AttachNegativeChild(
    std::shared_ptr<Spatial> const& child)
{
    return SetChild(2, child);
}

inline std::shared_ptr<Spatial> BspNode::DetachPositiveChild()
{
    return DetachChildAt(0);
}

inline std::shared_ptr<Spatial> BspNode::DetachCoplanarChild()
{
    return DetachChildAt(1);
}

inline std::shared_ptr<Spatial> BspNode::DetachNegativeChild()
{
    return DetachChildAt(2);
}

inline std::shared_ptr<Spatial> BspNode::GetPositiveChild()
{
    return GetChild(0);
}

inline std::shared_ptr<Spatial> BspNode::GetCoplanarChild()
{
    return GetChild(1);
}

inline std::shared_ptr<Spatial> BspNode::GetNegativeChild()
{
    return GetChild(2);
}


}
