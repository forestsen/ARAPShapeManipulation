// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteLightingEffect.h>
#include <Graphics/GteTexture2.h>

namespace gte
{

class GTE_IMPEXP DirectionalLightTextureEffect : public LightingEffect
{
public:
    // Construction.
    DirectionalLightTextureEffect(std::shared_ptr<ProgramFactory> const& factory,
        BufferUpdater const& updater, std::shared_ptr<Material> const& material,
        std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraGeometry> const& geometry,
        std::shared_ptr<Texture2> const& texture, SamplerState::Filter filter,
        SamplerState::Mode mode0, SamplerState::Mode mode1);

    // Member access.
    inline std::shared_ptr<Texture2> const& GetTexture() const;
    inline std::shared_ptr<SamplerState> const& GetSampler() const;

    // After you set or modify 'material', 'light', or 'geometry', call the update
    // to inform any listener that the corresponding constant buffer has changed.
    virtual void UpdateMaterialConstant();
    virtual void UpdateLightingConstant();
    virtual void UpdateGeometryConstant();

private:
    struct InternalMaterial
    {
        Vector4<float> emissive;
        Vector4<float> ambient;
        Vector4<float> diffuse;
        Vector4<float> specular;
    };

    struct InternalLighting
    {
        Vector4<float> ambient;
        Vector4<float> diffuse;
        Vector4<float> specular;
        Vector4<float> attenuation;
    };

    struct InternalGeometry
    {
        Vector4<float> lightModelDirection;
        Vector4<float> cameraModelPosition;
    };

    std::shared_ptr<Texture2> mTexture;
    std::shared_ptr<SamplerState> mSampler;

    // Shader source code as strings.
    static std::string const msGLSLVSSource;
    static std::string const msGLSLPSSource;
    static std::string const msHLSLSource;
    static std::string const* msVSSource[ProgramFactory::PF_NUM_API];
    static std::string const* msPSSource[ProgramFactory::PF_NUM_API];
};

inline std::shared_ptr<Texture2> const& DirectionalLightTextureEffect::GetTexture() const
{
    return mTexture;
}

inline std::shared_ptr<SamplerState> const& DirectionalLightTextureEffect::GetSampler() const
{
    return mSampler;
}

}
