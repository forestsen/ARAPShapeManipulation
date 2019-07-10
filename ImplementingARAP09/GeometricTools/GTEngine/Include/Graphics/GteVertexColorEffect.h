// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.2 (2018/09/07)

#pragma once

#include <Graphics/GteVisualEffect.h>

namespace gte
{
    class GTE_IMPEXP VertexColorEffect : public VisualEffect
    {
    public:
        // Construction.
        VertexColorEffect(std::shared_ptr<ProgramFactory> const& factory);

        // Member access.
        virtual void SetPVWMatrixConstant(std::shared_ptr<ConstantBuffer> const& buffer) override;

    private:
        // Shader source code as strings.
        static std::string const msGLSLVSSource;
        static std::string const msGLSLPSSource;
        static std::string const msHLSLSource;
        static std::string const* msVSSource[ProgramFactory::PF_NUM_API];
        static std::string const* msPSSource[ProgramFactory::PF_NUM_API];
    };
}
