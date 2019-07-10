// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteLightingEffect.h>

namespace gte
{

class GTE_IMPEXP AmbientLightEffect : public LightingEffect
{
public:
    // Construction.
    AmbientLightEffect(std::shared_ptr<ProgramFactory> const& factory,
        BufferUpdater const& updater, std::shared_ptr<Material> const& material,
        std::shared_ptr<Lighting> const& lighting);

    // After you set or modify 'material' or 'lighting', call the update to
    // inform any listener that the corresponding constant buffer has changed.
    virtual void UpdateMaterialConstant();
    virtual void UpdateLightingConstant();

private:
    struct InternalMaterial
    {
        Vector4<float> emissive;
        Vector4<float> ambient;
    };

    struct InternalLighting
    {
        Vector4<float> ambient;
        Vector4<float> attenuation;
    };

    // Shader source code as strings.
    static std::string const msGLSLVSSource;
    static std::string const msGLSLPSSource;
    static std::string const msHLSLSource;
    static std::string const* msVSSource[ProgramFactory::PF_NUM_API];
    static std::string const* msPSSource[ProgramFactory::PF_NUM_API];
};

}
