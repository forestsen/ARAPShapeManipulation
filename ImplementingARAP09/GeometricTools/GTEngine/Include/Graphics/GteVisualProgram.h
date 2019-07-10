// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteGeometryShader.h>
#include <Graphics/GteVertexShader.h>
#include <Graphics/GtePixelShader.h>

namespace gte
{

class GTE_IMPEXP VisualProgram
{
public:
    // HLSL uses the class as is.  GLSL derives from the class to store
    // the shader and program handles.
    virtual ~VisualProgram();
    VisualProgram();

    // Member access.
    inline std::shared_ptr<VertexShader> const& GetVShader() const;
    inline std::shared_ptr<PixelShader> const& GetPShader() const;
    inline std::shared_ptr<GeometryShader> const& GetGShader() const;

public:
    // INTERNAL USE ONLY.  These are used during factory creation of shaders
    // and programs.  The graphics engines need only const-access to the
    // shader objects.
    inline void SetVShader(std::shared_ptr<VertexShader> const& shader);
    inline void SetPShader(std::shared_ptr<PixelShader> const& shader);
    inline void SetGShader(std::shared_ptr<GeometryShader> const& shader);

private:
    std::shared_ptr<VertexShader> mVShader;
    std::shared_ptr<PixelShader> mPShader;
    std::shared_ptr<GeometryShader> mGShader;
};


inline std::shared_ptr<VertexShader> const& VisualProgram::GetVShader() const
{
    return mVShader;
}

inline std::shared_ptr<PixelShader> const& VisualProgram::GetPShader() const
{
    return mPShader;
}

inline std::shared_ptr<GeometryShader> const& VisualProgram::GetGShader()
    const
{
    return mGShader;
}

inline void VisualProgram::SetVShader(
    std::shared_ptr<VertexShader> const& shader)
{
    mVShader = shader;
}

inline void VisualProgram::SetPShader(
    std::shared_ptr<PixelShader> const& shader)
{
    mPShader = shader;
}

inline void VisualProgram::SetGShader(
    std::shared_ptr<GeometryShader> const& shader)
{
    mGShader = shader;
}


}
