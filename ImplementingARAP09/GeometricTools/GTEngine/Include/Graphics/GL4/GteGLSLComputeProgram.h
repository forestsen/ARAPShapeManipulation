// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteComputeProgram.h>
#include <Graphics/GL4/GteGLSLReflection.h>

namespace gte
{

class GTE_IMPEXP GLSLComputeProgram : public ComputeProgram
{
public:
    // Construction and destruction.
    virtual ~GLSLComputeProgram();
    GLSLComputeProgram(GLuint programHandle, GLuint cshaderHandle);

    // Member access.  GLEngine needs the program handle for enabling and
    // disabling the program.  TODO: Do we need the GetCShaderHandle
    // function?
    inline GLuint GetProgramHandle() const;
    inline GLuint GetCShaderHandle() const;
    inline GLSLReflection const& GetReflector() const;

private:
    GLuint mProgramHandle, mCShaderHandle;
    GLSLReflection mReflector;
};

inline GLuint GLSLComputeProgram::GetProgramHandle() const
{
    return mProgramHandle;
}

inline GLuint GLSLComputeProgram::GetCShaderHandle() const
{
    return mCShaderHandle;
}

inline GLSLReflection const& GLSLComputeProgram::GetReflector() const
{
    return mReflector;
}

}
