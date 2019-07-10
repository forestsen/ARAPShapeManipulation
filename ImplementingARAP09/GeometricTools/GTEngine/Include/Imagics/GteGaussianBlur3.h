// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.23.0 (2019/03/12)

#pragma once

#include <Imagics/GtePdeFilter3.h>

namespace gte
{
    template <typename Real>
    class GaussianBlur3 : public PdeFilter3<Real>
    {
    public:
        GaussianBlur3(int xBound, int yBound, int zBound, Real xSpacing,
            Real ySpacing, Real zSpacing, Real const* data, bool const* mask,
            Real borderValue, typename PdeFilter<Real>::ScaleType scaleType)
            :
            PdeFilter3<Real>(xBound, yBound, zBound, xSpacing, ySpacing, zSpacing,
                data, mask, borderValue, scaleType)
        {
            mMaximumTimeStep = (Real)0.5 / (this->mInvDxDx + this->mInvDyDy + this->mInvDzDz);
        }

        virtual ~GaussianBlur3()
        {
        }

        inline Real GetMaximumTimeStep() const
        {
            return mMaximumTimeStep;
        }

    protected:
        virtual void OnUpdate(int x, int y, int z) override
        {
            this->LookUp7(x, y, z);

            Real uxx = this->mInvDxDx * (this->mUpzz - (Real)2 * this->mUzzz + this->mUmzz);
            Real uyy = this->mInvDyDy * (this->mUzpz - (Real)2 * this->mUzzz + this->mUzmz);
            Real uzz = this->mInvDzDz * (this->mUzzp - (Real)2 * this->mUzzz + this->mUzzm);

            this->mBuffer[this->mDst][z][y][x] = this->mUzzz + this->mTimeStep * (uxx + uyy + uzz);
        }

        Real mMaximumTimeStep;
    };
}
