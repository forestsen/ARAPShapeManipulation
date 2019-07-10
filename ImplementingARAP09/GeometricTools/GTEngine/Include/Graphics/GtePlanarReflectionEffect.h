// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Mathematics/GteMatrix4x4.h>
#include <Graphics/GteGraphicsEngine.h>
#include <Graphics/GtePVWUpdater.h>
#include <Graphics/GteVisual.h>

namespace gte
{

class GTE_IMPEXP PlanarReflectionEffect
{
public:
    // Construction.  The number of planes supported depends on the number of
    // stencil bits (256 for an 8-bit stencil buffer).  The planes must be opaque.
    PlanarReflectionEffect(std::vector<std::shared_ptr<Visual>> const& planes,
        std::vector<float> const& reflectances);

    virtual void Draw(std::shared_ptr<GraphicsEngine> const& engine,
        VisibleSet const& visibleSet, PVWUpdater& pvwMatrices);

    // Member access.  GetPlane(i) returns (origin,normal).
    inline int GetNumPlanes() const;
    std::pair<Vector4<float>, Vector4<float>> GetPlane(int i) const;
    std::shared_ptr<Visual> GetPlaneVisual(int i) const;
    void SetReflectance(int i, float reflectance);
    float GetReflectance(int i) const;

protected:
    std::vector<std::shared_ptr<Visual>> mPlanes;
    std::vector<float> mReflectances;
    std::vector<Vector4<float>> mPlaneOrigins, mPlaneNormals;
    std::shared_ptr<BlendState> mNoColorWrites, mReflectanceBlend;
    std::shared_ptr<RasterizerState> mCullReverse;
    std::shared_ptr<DepthStencilState> mDSPass0, mDSPass1, mDSPass2;
};


inline int PlanarReflectionEffect::GetNumPlanes()const
{
    return static_cast<int>(mPlanes.size());
}

}
