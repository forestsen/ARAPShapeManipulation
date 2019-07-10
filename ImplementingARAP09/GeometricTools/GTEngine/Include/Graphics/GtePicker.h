// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Mathematics/GteLine.h>
#include <Graphics/GteNode.h>
#include <Graphics/GtePickRecord.h>
#include <Graphics/GteVisual.h>

namespace gte
{

class GTE_IMPEXP Picker
{
public:
    // Construction and destruction.
    ~Picker();
    Picker();

    // Set the maximum distance when the 'scene' contains point or segment
    // primitives.  Such primitives are selected when they are within the
    // specified distance of the pick line.  The default is 0.0f.
    void SetMaxDistance(float maxDistance);
    float GetMaxDistance() const;

    // The linear component is parameterized by P + t*D, where P is a point on
    // the component (the origin) and D is a unit-length direction vector.
    // Both P and D must be in world coordinates.  The interval [tmin,tmax] is
    //   line:     tmin = -fmax, tmax = fmax
    //   ray:      tmin = 0, tmax = fmax
    //   segment:  tmin = 0, tmax > 0;
    // where fmax is std::numeric_limits<float>::max().  A call to this
    // function will automatically clear the 'records' array.  If you need any
    // information from this array obtained by a previous call to Execute, you
    // must save it first.
    void operator()(std::shared_ptr<Spatial> const& scene,
        Vector4<float> const& origin, Vector4<float> const& direction,
        float tmin, float tmax);

    // The following three functions return the record satisfying the
    // constraints.  They should be called only when records.size() > 0.

    // Locate the record whose t-value is smallest in absolute value.
    PickRecord const& GetClosestToZero() const;

    // Locate the record with nonnegative t-value closest to zero.
    PickRecord const& GetClosestNonnegative() const;

    // Locate the record with nonpositive t-value closest to zero.
    PickRecord const& GetClosestNonpositive() const;

    // Access to all the records for the pick operation.
    std::vector<PickRecord> records;

private:
    // The picking occurs recursively by traversing the input scene.
    void ExecuteRecursive(std::shared_ptr<Spatial> const& object);

    void PickTriangles(std::shared_ptr<Visual> const& visual, char const* positions,
        unsigned int vstride, IndexBuffer* ibuffer, Line3<float> const& line);

    void PickSegments(std::shared_ptr<Visual> const& visual, char const* positions,
        unsigned int vstride, IndexBuffer* ibuffer, Line3<float> const& line);

    void PickPoints(std::shared_ptr<Visual> const& visual, char const* positions,
        unsigned int vstride, IndexBuffer* ibuffer, Line3<float> const& line);

    // The maximum distance from the pick line used to select point or segment
    // primitives.
    float mMaxDistance;

    // The parameters for the linear component used to pick.
    Vector4<float> mOrigin;
    Vector4<float> mDirection;
    float mTMin, mTMax;

    // The value returned if the Get* functions are called when 'records' has
    // no elements.
    static PickRecord const msInvalid;
};

}
