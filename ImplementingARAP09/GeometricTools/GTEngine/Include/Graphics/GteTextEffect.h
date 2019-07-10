// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Mathematics/GteVector4.h>
#include <Graphics/GteConstantBuffer.h>
#include <Graphics/GteProgramFactory.h>
#include <Graphics/GteSamplerState.h>
#include <Graphics/GteTexture2.h>
#include <Graphics/GteVisualEffect.h>

namespace gte
{

class GTE_IMPEXP TextEffect : public VisualEffect
{
public:
    // Construction.
    TextEffect(std::shared_ptr<ProgramFactory> const& factory,
        std::shared_ptr<Texture2> const& texture);

    // Support for typesetting.
    std::shared_ptr<ConstantBuffer> const& GetTranslate() const;
    std::shared_ptr<ConstantBuffer> const& GetColor() const;
    void SetTranslate(float x, float y);
    void SetColor(Vector4<float> const& color);

private:
    std::shared_ptr<ConstantBuffer> mTranslate;
    std::shared_ptr<ConstantBuffer> mColor;
    std::shared_ptr<SamplerState> mSamplerState;

    // Shader source code as strings.
    static std::string const msGLSLVSSource;
    static std::string const msGLSLPSSource;
    static std::string const msHLSLSource;
    static std::string const* msVSSource[ProgramFactory::PF_NUM_API];
    static std::string const* msPSSource[ProgramFactory::PF_NUM_API];
};

}
