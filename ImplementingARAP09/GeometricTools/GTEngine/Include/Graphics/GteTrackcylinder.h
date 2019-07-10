// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.15.1 (2019/03/18)

#pragma once

#include <Graphics/GteTrackObject.h>

namespace gte
{
    class GTE_IMPEXP Trackcylinder : public TrackObject
    {
    public:
        // Construction.  The window rectangle is assumed to be defined in
        // right-handed coordinates, so if you use a window client rectangle
        // for the trackball and this rectangle is in left-handed coordinates,
        // you must reflect the y-values in SetInitialPoint and SetFinalPoint
        // by (ySize - 1 - y).  A root node is used to represent the
        // trackcylinder/ orientation.  Objects may be attached and detached
        // as desired.
        Trackcylinder();
        Trackcylinder(int xSize, int ySize, std::shared_ptr<Camera> const& camera);
        virtual ~Trackcylinder()
        {
        }

        // Reset the trackcylinder rotation to the identity.
        void Reset();

    protected:
        virtual void OnSetInitialPoint() override;
        virtual void OnSetFinalPoint() override;

        // The window rectangle is mXSize-by-mYSize.  Let the initial point
        // be (x0,y0) and the final point be (x1,y1).  Let dx = x1 - x0 and
        // dy = y1 - y0.  If dx >= dy, then the yaw angle in [-pi,pi] is
        // modified according to yaw = pi*dx/xSize.  If dy > dx, then the
        // pitch angle in [-pi/2,pi/2] is modified according to
        // pitch = -pi*dy/ySize but is clamped to [-pi/2,pi/2].

        // Rotations about the z-axis.
        float mInitialYaw, mYaw;

        // Rotations about the y-axis.
        float mInitialPitch, mPitch;
    };
}
