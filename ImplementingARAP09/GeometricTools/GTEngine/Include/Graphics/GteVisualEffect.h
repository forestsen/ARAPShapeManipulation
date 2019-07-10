// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2018/09/07)

#pragma once

#include <Mathematics/GteMatrix4x4.h>
#include <Graphics/GteProgramFactory.h>

namespace gte
{
    class GTE_IMPEXP VisualEffect
    {
    public:
        // Construction and destruction.
        virtual ~VisualEffect();
        VisualEffect(std::shared_ptr<VisualProgram> const& program);

        // Member access.
        inline std::shared_ptr<VisualProgram> const& GetProgram() const
        {
            return mProgram;
        }

        inline std::shared_ptr<VertexShader> const& GetVertexShader() const
        {
            return mProgram->GetVShader();
        }

        inline std::shared_ptr<PixelShader> const& GetPixelShader() const
        {
            return mProgram->GetPShader();
        }

        inline std::shared_ptr<GeometryShader> const& GetGeometryShader() const
        {
            return mProgram->GetGShader();
        }

        // For convenience, provide a projection-view-world constant buffer
        // that an effect can use if so desired.
        virtual void SetPVWMatrixConstant(std::shared_ptr<ConstantBuffer> const& buffer);

        inline std::shared_ptr<ConstantBuffer> const& GetPVWMatrixConstant() const
        {
            return mPVWMatrixConstant;
        }

        inline void SetPVWMatrix(Matrix4x4<float> const& pvwMatrix)
        {
            *mPVWMatrixConstant->Get<Matrix4x4<float>>() = pvwMatrix;
        }

        inline Matrix4x4<float> const& GetPVWMatrix() const
        {
            return *mPVWMatrixConstant->Get<Matrix4x4<float>>();
        }

    protected:
        // For derived classes to defer construction because they want to
        // create programs via a factory.
        VisualEffect();

        std::shared_ptr<VisualProgram> mProgram;
        BufferUpdater mBufferUpdater;
        TextureUpdater mTextureUpdater;
        TextureArrayUpdater mTextureArrayUpdater;

        // The constant buffer that stores the 4x4 projection-view-world
        // transformation for the Visual object to which this effect is
        // attached.
        std::shared_ptr<ConstantBuffer> mPVWMatrixConstant;
    };
}
