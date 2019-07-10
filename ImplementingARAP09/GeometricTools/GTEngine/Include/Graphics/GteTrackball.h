// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2019/03/18)

#pragma once

#include <Graphics/GteTrackObject.h>

namespace gte
{
    class GTE_IMPEXP Trackball : public TrackObject
    {
    public:
        // Construction and destruction.  The trackball is the largest circle
        // centered in the rectangle of dimensions xSize-by-ySize.  The
        // rectangle is assumed to be defined in right-handed coordinates, so
        // y-values in SetInitialPoint and SetFinalPoint are reflected to
        // (ySize - 1 - y).
        Trackball();
        Trackball(int xSize, int ySize, std::shared_ptr<Camera> const& camera);
        virtual ~Trackball()
        {
        }

        // Reset the trackball rotation to the identity.
        void Reset();

    protected:
        virtual void OnSetInitialPoint() override;
        virtual void OnSetFinalPoint() override;

        Matrix4x4<float> mInitialOrientation;
    };
}
