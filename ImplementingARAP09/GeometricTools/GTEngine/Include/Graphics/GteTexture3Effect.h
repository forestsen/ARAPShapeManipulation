// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.2 (2018/09/07)

#pragma once

#include <Graphics/GteTexture3.h>
#include <Graphics/GteVisualEffect.h>

namespace gte
{
    class GTE_IMPEXP Texture3Effect : public VisualEffect
    {
    public:
        // Construction.
        Texture3Effect(std::shared_ptr<ProgramFactory> const& factory,
            std::shared_ptr<Texture3> const& texture, SamplerState::Filter filter,
            SamplerState::Mode mode0, SamplerState::Mode mode1,
            SamplerState::Mode mode2);

        // Member access.
        virtual void SetPVWMatrixConstant(std::shared_ptr<ConstantBuffer> const& buffer) override;

        inline std::shared_ptr<Texture3> const& GetTexture() const
        {
            return mTexture;
        }

        inline std::shared_ptr<SamplerState> const& GetSampler() const
        {
            return mSampler;
        }

    private:
        // Pixel shader parameters.
        std::shared_ptr<Texture3> mTexture;
        std::shared_ptr<SamplerState> mSampler;

        // Shader source code as strings.
        static std::string const msGLSLVSSource;
        static std::string const msGLSLPSSource;
        static std::string const msHLSLSource;
        static std::string const* msVSSource[ProgramFactory::PF_NUM_API];
        static std::string const* msPSSource[ProgramFactory::PF_NUM_API];
    };
}
